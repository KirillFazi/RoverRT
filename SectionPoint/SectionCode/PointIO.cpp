#include <fstream>
#include <iostream>
#include "SectionPoint.h"
using namespace std;
/*_______________________________________________________________________________________________________________
                            Work with read and convert received data
//_______________________________________________________________________________________________________________*/

// Read data file and convert data to string array
// assign path to *.csv and array of string
int readingFileToString(const string &pathToFile, string strArray[]) {
    ifstream readingFile(pathToFile);                                   // open file
    if (!readingFile) {cerr << "Error! File not found!" << std::endl;}      // Check existing
    int numberLine = 0;
    while (std::getline(readingFile, strArray[numberLine]))       //read value and put to array of string
        numberLine++;
    readingFile.close();    //close file
    cout << "Reading and copying files has been completed!" <<endl;
    return numberLine;
}

// Parsing string format x,y to point X and Y coordinates
void parseLineToPoint(string str[], Point points[], int quantity)
{
    for(int i = 1; i!=quantity; i++) {

        size_t pos = str[i].find(',');                    // find separator ','
        string x_str = str[i].substr(0, pos);       // take substring from 0 position to ','
        *points[i - 1].X = stod(x_str);                 // convert string value to Point.X

        str[i].erase(0, pos + 1);                   // delete all before comma, and space symbol after comma
        pos = str[i].find(',');                          // find next separator ','
        string y_str = str[i].substr(0,pos);        // take substring from 0 position to ',' of new string
        *points[i - 1].Y = stod (y_str);                // convert string value to Point.Y

        cout<< "#" << i-1 <<"\tX: " << *points[i - 1].X << "\tY: " << *points[i - 1].Y << endl;
    }
    cout << "Conversion of coordinates to points has been completed!" << endl;
}

void parsingRoutePoint(Point point[],string str[],  int const quantityPoints = 0) {
    int numPoint[quantityPoints];
    for (int i = 1; i !=quantityPoints; i++) {

        size_t pos = str[i].find(',');
        string num_str = str[i].substr(0,pos);
        numPoint[i - 1] = stoi(num_str);

        if(numPoint[i-1] == -1) break;

        str[i].erase(0, pos + 1);
        pos = str[i].find(',');
        *point[i-1].X = stod(str[i].substr(0, pos));

        str[i].erase(0, pos+1);
        pos = str[i].find(',');
        *point[i-1].Y = stod(str[i].substr(0, pos));

        cout.precision(8);
        cout<<"#" << numPoint[i-1] << "\t";
         point[i - 1].ConsolePrintValues();
    }
}
int saveDataFile()
{

}