#include "CRectangle.h"
#include <iostream>

CRectangle::CRectangle(const PointD& leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	if (GetFillStyle()->IsEnabled())
	{
		canvas.BeginFill(*GetFillStyle()->GetColor());
	}
	if (GetOutlineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetOutlineStyle()->GetColor());
		canvas.SetLineThickness(*GetOutlineStyle()->GetThickness());
	}
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);
	if (GetFillStyle()->IsEnabled())
	{
		canvas.EndFill();
	}
}

std::optional<RectD> CRectangle::GetFrame() const
{
	RectD frame{ m_leftTop.x, m_leftTop.y, m_width, m_height };
	return frame;
}

void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTop.x = rect.left;
	m_leftTop.y = rect.top;
	m_width = rect.width;
	m_height = rect.height;
}
