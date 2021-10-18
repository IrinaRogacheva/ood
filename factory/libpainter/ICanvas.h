#pragma once
#include "EColor.h"
#include "CPoint.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const CPoint& from, const CPoint& to) = 0;
	virtual void DrawEllipse(CPoint const& left, CPoint const& top, double width, double height) = 0;
	virtual ~ICanvas() = default;
};