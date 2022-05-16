#include "Point.h"

Point& Point::operator+(Point& b)
{
	Point c{row, column};
	c.row += b.row;
	c.column += b.column;
	return c;
}

Point& Point::operator+=(Point& b)
{
	row += b.row;
	column += b.column;
	return *this;
}

Point& Point::operator-(Point& b)
{
	Point c{row, column};
	c.row -= b.row;
	c.column -= b.column;
	return c;
}

Point& Point::operator-=(Point& b)
{
	row -= b.row;
	column -= b.column;
	return *this;
}


Point& Point::operator/(int& b)
{
	Point c{row, column};
	c.row /= b;
	c.column /= b;
	return c;
}

Point& Point::operator/=(int& b)
{
	row /= b;
	column /= b;
	return *this;
}

Point& Point::operator*(int& b) 
{
	Point c{row, column};
	c.row *= b;
	c.column *= b;
	return c;
}

Point& Point::operator*=(int& b)
{
	row *= b;
	column *= b;
	return *this;
}

bool Point::operator==(Point p) const
{
	return row == p.row && column == p.column;
}
