#include "stdafx.h"
#include "CEllipse.h"
#include <iostream>

CEllipse::CEllipse(CPoint const& center, double horizontalRadius, double verticalRadius, Color color)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
	, CShape(color)
{
}

CPoint CEllipse::GetCenter() const
{
	return m_center;
}

double CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

double CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawEllipse({ m_center.GetX() - m_horizontalRadius, m_center.GetY() }, { m_center.GetX(), m_center.GetY() - m_verticalRadius }, m_horizontalRadius * 2, m_verticalRadius * 2);
}