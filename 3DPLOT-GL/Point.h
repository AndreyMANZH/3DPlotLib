#pragma once
class Point
{

private:
	void setX(double x);
	void setY(double y);
	void setZ(double z);

	double x;
	double y;
	double z;

	double r;
	double g;
	double b;
public:
	double getX();
	double getY();
	double getZ();

	double getR();
	double getG();
	double getB();
	Point();
	Point(const Point& p);
	Point(double x, double y, double z);
	Point(double x, double y, double z, double r, double g, double b);
	~Point(); 
};

