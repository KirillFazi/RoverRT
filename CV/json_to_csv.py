import json
import os


def get_path(json_data: dict, safe_path: bool = False) -> list:
    """
    Get save path from json data
    :param json_data: json data from 2gis api
    :return: list of maneuvers
    """
    path = None

    if safe_path:
        for index in range(len(json_data['result'])):
            if json_data['result'][index]['algorithm'] == 'safe':
                save_path = json_data['result'][index]['maneuvers']
                break

    else:
        path = json_data['result'][0]['maneuvers']

    return path


def get_points(maneuvers: list) -> list[tuple]:
    """
    Get points from json data
    :param maneuvers: list of maneuvers
    :return: list of points
    """
    points = []

    for maneuver in maneuvers[0]['outcoming_path']['geometry']:
        linestring_points = maneuver['selection'][11:][:-1].split(',')
        for point in linestring_points:
            points.append(tuple(list(map(float, point.split())) + [maneuver['length']]))

    return points


def save_points_csv(points: list[tuple], file_name: str = 'data.csv', directory: str = 'data') -> None:
    """
    Save points to csv file
    :param points: list of points
    :param file_name: name of file
    :param directory: directory to save file
    :return: None
    """
    if not os.path.exists(directory):
        os.makedirs(directory)

    with open(os.path.join(directory, file_name), 'w') as file:
        file.write('id,x,y,length\n')
        for index, point in enumerate(points):
            file.write(f'{index},{point[1]},{point[0]},{point[2]}\n')
        file.write('-1,-1,-1,-1\n')

    print(f'csv file saved to {os.path.join(directory, file_name)} successfully')


# file_name = 'routes/stolovay_10_to_maneg_2023-05-16_14-12-48.json'
# directory_name = 'routes'
# path_to_file = os.path.join(directory_name, file_name)

path_to_file = 'routes/stolovay_10_to_maneg_2023-05-16_14-12-48.json'
directory_name, file_name = path_to_file.split('/')

with open(path_to_file, 'r') as file:
    json_data = json.load(file)

save_path = get_path(json_data)
points = get_points(save_path)
save_points_csv(points, file_name[:-5] + '.csv', directory_name)
