/*
* Header file of "Section" and "Point" classes
* 
* Point consists of two coordinates - X and Y
* 
* Section consist of two Points and has some parameters
* 
* This is Distance of section, angle by axis X, 
* angle to rotation(delta of two Section), and speed on a Section
*/
#ifndef SECTION_POINTS
#define SECTION_POINTS

class Point {

public:

	explicit Point(double x = 0, double y = 0)
		: X(new double(x)), Y(new double(y)){}

    // Setting values x,y to field's values of class
	void setValue(double x, double y);

    // Useful methods of printing values X and Y to console
	void ConsolePrintValues() const;

	// Coordinate of point
	double* X;
	double* Y;
	
};

class Section {

public:

    // Default constructor with zeros values
	Section()
		: p0(Point(0, 0)), p1(Point(0, 0)),
        tg(0), angle(0), speed(), distance(0), angleToRotation()
	{}

    // Constructor with two Point objects as arguments
	explicit Section(Point initialPoint, Point finalPoint = Point(0, 0))
		: distance(), angleToRotation(), angle(), speed(), p0(initialPoint), p1(finalPoint), tg()
	{ AngleAndDistanceComputing(initialPoint, finalPoint); }

    // Constructor with four coordinate's values
    Section (float x0, float y0, float x1 ,float y1)
    : p0(Point(x0,y0)), p1(Point(x1,y1))
    { AngleAndDistanceComputing(Point(x0,y0), Point(x1, y1)); }

    // Method calculating angle to Rotation with previous section angle
	float anglePrevSection(Section previousSection);

    // Method calculating angle to Rotation with next section angle
	float angleNextSection(Section nextSection);

    // Method for setting point values, X and Y. And setting values Distance and Angle
	void setPoints(Point init, Point fin);

    // Method setting coordinate initial point and final point
    void setCoordinates(float x0, float y0, float x1 , float y1);

    // Variables
	double distance;		// Distance from Point to Point
	double angleToRotation; // Angle of Rotation, delta angeles
	double angle;			// angle by X axis
	float speed;			// speed of movement of section

private:

//Calculating tangents, angels and distance with coordinates X and Y of two Points objects
	void AngleAndDistanceComputing(Point init, Point fin);
    static double haversine(Point init, Point fin);
	Point p0;
	Point p1;
	float tg;
};

int readingFileToString(const std::string& pathToFile, std::string strArray[]);

void parseLineToPoint(std::string str[], Point points[], int quantity = 0);

void parsingRoutePoint(Point point[], std::string str[], int const quantityPoints);


#endif // SECTION_POINTS
