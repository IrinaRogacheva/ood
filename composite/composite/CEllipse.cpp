#include "CEllipse.h"

CEllipse::CEllipse(PointD leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void CEllipse::Draw(ICanvas& canvas) const
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
	canvas.DrawEllipse(m_leftTop.x, m_leftTop.y, m_width, m_height);
	if (GetFillStyle()->IsEnabled())
	{
		canvas.EndFill();
	}
}

std::optional<RectD> CEllipse::GetFrame() const
{
	RectD frame{ m_leftTop.x, m_leftTop.y, m_width, m_height };
	return frame;
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_leftTop.x = rect.left;
	m_leftTop.y = rect.top;
	m_width = rect.width;
	m_height = rect.height;
}
