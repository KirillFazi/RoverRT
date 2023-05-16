#include <iostream>
#include "SectionPoint.h"
#include <cmath>
#include <string>
/*____________________________________________________________________________________________________________
	    Methods and parameter of point class. Point includes two parameters, it's X and Y coordinates
______________________________________________________________________________________________________________*/

    // Setting values x,y to field's values of class
	void Point::setValue(double x, double y) {
		this->X = new double(x);
		this->Y = new double(y);
	}

    // Useful methods of printing values X and Y to console
	void Point::ConsolePrintValues() const {
		std::cout << "X = " << *this->X << "\tY = " << *this->Y << std::endl;
	}

	// Coordinate of point
	double* X; 
	double* Y;
/*______________________________________________________________________________________________________________
	             Methods and parameters of Section class.
        Section includes two Point object, computing distances and angles
    Rotation angle must be calculated out of the class, and last section doesn't have it
________________________________________________________________________________________________________________*/

    // Method calculating angle to Rotation with previous section angle
	float Section::anglePrevSection(Section previousSection) {
		angleToRotation = previousSection.angle - this->angle;
		return (float)angleToRotation;
	}

    // Method calculating angle to Rotation with next section angle
	float Section::angleNextSection(Section nextSection) {
		angleToRotation = nextSection.angle - this->angle;
		return (float)angleToRotation;
	}

    // Method for setting point values, X and Y. And setting values Distance and Angle
	void Section::setPoints(Point init, Point fin) {
		AngleAndDistanceComputing(init, fin);
		p0.X = init.X;
		p0.Y = init.Y;
		p1.Y = fin.Y;
		p1.X = fin.X;
	}

    // Method setting coordinate initial point and final point
    void Section::setCoordinates(float x0, float y0, float x1, float y1)  {
    *this->p0.X = x0; *this->p0.Y = y0;
    *this->p1.X = x1; *this->p1.Y = y1;
    AngleAndDistanceComputing(Point(x0,y0), Point(x1, y1));
    }

    //Calculating tangents, angels and distance with coordinates X and Y of two Points objects
	void Section::AngleAndDistanceComputing(Point init, Point fin) {
		this->tg = (*fin.Y - *init.Y) / (*fin.X - *init.X);
		angle = atan(tg) * 57.29577;
        this->distance = haversine(init, fin);
        double R = 6'356'863;


	}

    double Section::haversine(Point init, Point fin) {

        double R = 6'356'863;  // Earth's radius

        double phi1 = M_PI / 180.0 * *init.X;
        double phi2 = M_PI / 180.0 * *fin.X;
        double delta_phi = M_PI / 180.0 * (*fin.X - *init.X);
        double delta_lambda = M_PI / 180.0 * (*fin.Y - *init.Y);

        double a = sin(delta_phi / 2.0) * sin(delta_phi / 2.0) + cos(phi1) * cos(phi2) * sin(delta_lambda / 2.0) * sin(delta_lambda / 2.0);
        double c = asin(sqrt(a));

        return 2.0 * R * c;
    }
    // Public
	double distance;		// Distance from Point to Point
	double angleToRotation; // Angle of Rotation, delta angeles
	double angle;			// angle by X axis
	float speed;			// speed of movement of section
	// Private
	Point p0;				// Initial point
	Point p1;				// Final point
	float tg;				// tangents of angle