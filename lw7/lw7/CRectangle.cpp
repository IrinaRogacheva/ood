#include "CRectangle.h"

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
		canvas.SetFillColor(*GetFillStyle()->GetColor());
		//canvas.FillRegularPolygon(double radius, const PointD & center, 4); (не знаю, как это делать)
	}
	if (GetOutlineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetOutlineStyle()->GetColor());
		canvas.SetLineThickness(*GetOutlineStyle()->GetThickness());
	}
	canvas.DrawLine(m_leftTop, { m_leftTop.x + m_width, m_leftTop.y });
	canvas.DrawLine({ m_leftTop.x + m_width, m_leftTop.y }, { m_leftTop.x + m_width, m_leftTop.y + m_height });
	canvas.DrawLine({ m_leftTop.x + m_width, m_leftTop.y + m_height } , { m_leftTop.x, m_leftTop.y + m_height });
	canvas.DrawLine({ m_leftTop.x, m_leftTop.y + m_height }, m_leftTop);
}

std::optional<RectD> CRectangle::GetFrame() const
{
	RectD frame{ m_leftTop, m_width, m_height };
	return frame;
}

void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTop = rect.leftTop;
	m_width = rect.width;
	m_height = rect.height;
}
