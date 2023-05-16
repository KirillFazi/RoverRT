#include <iostream>			//input, output
#include <string>           //string class
#include "SectionPoint.h"	// Header file with Point and Section classes

using namespace std;

int main() {
    cout << "Enter path to file" << endl << ">> ";
    string path;
    cin >> path;

    string pointLines[100];
    int const quantity = readingFileToString(path,pointLines);
    cout << " Quantity of string: " << quantity << endl;

    Point points[quantity];
    parsingRoutePoint(points,pointLines, quantity);

    Section sections[quantity-1];
    cout.precision(8);
    double totalDist = 0;
    for (int i = 0; i != quantity - 3; i++ ) {

        sections[i].setPoints(points[i], points[i+1]);
        totalDist+= sections[i].distance;
        if (sections[i].distance == 0){
            cout << "Distance>> " << totalDist << endl;
            totalDist = 0;
        }
        else {
            cout << "#" << i << " " << sections[i].distance << endl;
        }
    }
    cout << "Distance>> " << totalDist << endl;
}