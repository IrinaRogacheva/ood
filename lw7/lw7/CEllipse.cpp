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
		canvas.SetFillColor(*GetFillStyle()->GetColor());
		canvas.FillEllipse(m_leftTop.x + m_width / 2, m_leftTop.y + m_height / 2, m_leftTop);
	}
	if (GetOutlineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetOutlineStyle()->GetColor());
		canvas.SetLineThickness(*GetOutlineStyle()->GetThickness());
	}
	canvas.DrawEllipse(m_leftTop.x + m_width / 2, m_leftTop.y + m_height / 2, m_leftTop);
}

std::optional<RectD> CEllipse::GetFrame() const
{
	RectD frame{ m_leftTop, m_width, m_height };
	return frame;
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_leftTop = rect.leftTop;
	m_width = rect.width;
	m_height = rect.height;
}
