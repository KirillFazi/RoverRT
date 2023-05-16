""" make request to 2gis api and get routes pedestrian using api key """

import requests
import json
import os
from dotenv import load_dotenv
import time


def get_routes(start_point, end_point, api_key, type):
    """ make request to 2gis api and get routes pedestrian using api key """
    url = 'https://routing.api.2gis.com/carrouting/6.0.0/global?key=' + api_key

    # Установить значения координат точек маршрута
    point_A = {"type": "walking", "x": start_point[1], "y": start_point[0]}
    point_B = {"type": "walking", "x": end_point[1], "y": end_point[0]}

    # Сформировать массив точек маршрута
    points = [point_A, point_B]

    # Установить заголовок Content-Type
    headers = {"Content-Type": "application/json"}

    # Сформировать тело запроса в виде JSON
    data = {"points": points, "type": type}
    data_json = json.dumps(data)

    # Отправить POST-запрос
    response = requests.post(url, headers=headers, data=data_json)

    if response.status_code == 200:
        print(f'Successfully get routes from {start_point} to {end_point} using {type}')
    else:
        print('Error:', response.status_code, response.reason)

    return response.json()


def print_json(json_data):
    """ print json data """
    print(json.dumps(json_data, indent=4, sort_keys=True))


def get_points(json_data):
    """ get points from json data """
    points = []

    for route in json_data['result']['routes']:
        for point in route['geometry']['points']:
            points.append((point['x'], point['y']))

    return points


def return_points(
        start_point: tuple,
        end_point: tuple,
        type: str = 'bicycle',
        save_data: bool = False,
        file_name: str = '2gis_data.json',
        directory: str = 'data',
        print_data: bool = False) -> dict:
    """
    This function return points of route from start_point to end_point. Points gets from 2gis api.
    :param print_data: Print data to console. Default value is False
    :param directory: Directory to save data. Default value is 'data'. Used if save_data is True
    :param file_name: Name of file to save data. Default value is 'data.json'. Used if save_data is True
    :param save_data: Save data to file. Default value is False
    :param start_point: North latitude coordinates, East longitude coordinates of start point
    :param end_point: North latitude coordinates, East longitude coordinates of end point
    :param type: type of route. Default value is 'bicycle'
    :return: json data from 2gis api
    """
    load_dotenv()
    api_key = os.environ.get('API_KEY')

    routes = get_routes(start_point, end_point, api_key, type)

    if print_data:
        print_json(routes)

    if save_data:
        if file_name.endswith('.json'):
            file_name = file_name[:-5]

        n_time = time.strftime("%Y-%m-%d_%H-%M-%S", time.localtime())
        file_name = f'{file_name}_{n_time}.json'
        # get current directory and make one step back
        current_directory = os.path.dirname(os.path.abspath(__file__))

        if not os.path.exists(os.path.join(current_directory, directory)):
            os.mkdir(os.path.join(current_directory, directory))

        if os.path.exists(os.path.join(current_directory, directory, file_name)):
            print(f'Warning: file {file_name} already exists in "{directory}" directory. It will be overwritten')

        # save data to file in directory in json format
        with open(os.path.join(current_directory, directory, file_name), 'w') as file:
            print(f'Start saving data to {file_name}')
            json.dump(routes, file, indent=4, sort_keys=True)
            print(f'Successfully saved data to {file_name} in "{directory}" directory')

    return routes


if __name__ == '__main__':
    # first_point = (47.237945, 39.709843)  # dstu obshaga 10
    # second_point = (47.240705, 39.709348)  # dstu maneg
    first_point = (47.237963, 39.710609)
    second_point = (47.240702, 39.709349)
    file_name = 'narnia_to_maneg'
    directory = 'routes'
    return_points(first_point,
                  second_point,
                  save_data=True,
                  file_name=file_name,
                  directory=directory,
                  print_data=True,
                  type='pedestrian')
