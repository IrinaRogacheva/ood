#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, const CPoint& rightBottom, Color color)
	: m_leftTopPoint(leftTop)
	, m_rightBottomPoint(rightBottom)
	, CShape(color)
{
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomPoint;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint rightTopPoint(m_rightBottomPoint.GetX(), m_leftTopPoint.GetY());
	CPoint leftBottomPoint(m_leftTopPoint.GetX(), m_rightBottomPoint.GetY());

	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTopPoint, leftBottomPoint);
	canvas.DrawLine(leftBottomPoint, GetRightBottom());
	canvas.DrawLine(GetRightBottom(), rightTopPoint);
	canvas.DrawLine(rightTopPoint, m_leftTopPoint);

}