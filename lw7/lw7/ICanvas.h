#pragma once
#include "CommonTypes.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void SetLineColor(const RGBAColor& color) = 0;
	virtual void SetFillColor(const RGBAColor& color) = 0;
	virtual void SetLineThickness(const int thickness) = 0;
	virtual void DrawLine(const PointD& from, const PointD& to) = 0;
	virtual void DrawEllipse(double radiusX, double radiusY, const PointD& center) = 0;
	virtual void FillEllipse(double radiusX, double radiusY, const PointD& center) = 0;
	virtual void DrawRegularPolygon(double radius, const PointD& center, int vertexCount) = 0;
	virtual void FillRegularPolygon(double radius, const PointD& center, int vertexCount) = 0;
};