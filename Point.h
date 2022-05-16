#pragma once

class Point
{
public:
	int row;
	int column;

	Point& operator+(Point& b);
	Point& operator+=(Point& b);
	Point& operator-(Point& b);
	Point& operator-=(Point& b);
	Point& operator/(int& b);
	Point& operator/=(int& b);
	Point& operator*(int& b);
	Point& operator*=(int& b);
	bool operator==(Point p) const;	
};

