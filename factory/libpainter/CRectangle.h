#pragma once
#include "CShape.h"
#include "CPoint.h"

class CRectangle final : public CShape
{
public:
	CRectangle(const CPoint& leftTop, const CPoint& rightBottom, Color color);

	void Draw(ICanvas& canvas) const override;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
private:
	CPoint m_leftTopPoint;
	CPoint m_rightBottomPoint;
};
