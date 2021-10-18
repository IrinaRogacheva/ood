#pragma once
#include "CShape.h"
#include "CPoint.h"

class CEllipse final : public CShape
{
public:
	CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius, Color color);
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;
	CPoint GetCenter() const;
	void Draw(ICanvas& canvas) const;
private:
	double m_horizontalRadius;
	double m_verticalRadius;
	CPoint m_center;
};