#include "stdafx.h"
#include "CPoint.h"
#include <string>

CPoint::CPoint(double x, double y)
	: x(x)
	, y(y)
{
}

double CPoint::GetX() const
{
	return x;
}

double CPoint::GetY() const
{
	return y;
}

bool operator==(const CPoint& point1, const CPoint point2)
{
	return point1.GetX() == point2.GetX() && point1.GetY() == point2.GetY();
}