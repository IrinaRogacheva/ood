#pragma once
#include <stdint.h>

template <typename T>
struct Point
{
	T x;
	T y;
};

template <typename T>
struct Rect
{
	Point<T> leftTop;
	T width;
	T height;
};

typedef Point<double> PointD;
typedef Rect<double> RectD;
typedef uint32_t RGBAColor;