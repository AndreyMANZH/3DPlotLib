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
public:
	double getX();
	double getY();
	double getZ();

	Point(double x, double y, double z);
	~Point(); 
};

