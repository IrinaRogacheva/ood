#include "CTriangle.h"
#include <algorithm>

CTriangle::CTriangle(const PointD& point1, const PointD& point2, const PointD& point3)
	: m_point1(point1)
	, m_point2(point2)
	, m_point3(point3)
{
}

void CTriangle::Draw(ICanvas& canvas) const
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
	canvas.DrawLine(m_point1, m_point2);
	canvas.DrawLine(m_point2, m_point3);
	canvas.DrawLine(m_point3, m_point1);
}

std::optional<RectD> CTriangle::GetFrame() const
{
	PointD leftTop;
	leftTop.x = std::min({ m_point1.x, m_point2.x, m_point3.x });
	leftTop.y = std::min({ m_point1.y, m_point2.y, m_point3.y });
	double right = std::max({ m_point1.x, m_point2.x, m_point3.x });
	double bottom = std::max({ m_point1.y, m_point2.y, m_point3.y });

	RectD frame{ leftTop, right - leftTop.x, bottom - leftTop.y };
	return frame;
}

void CTriangle::SetFrame(const RectD& rect)
{
	std::optional<RectD> previousFrame = GetFrame();

	m_point1 = UpdateVertex(*previousFrame, rect, m_point1);
	m_point2 = UpdateVertex(*previousFrame, rect, m_point2);
	m_point3 = UpdateVertex(*previousFrame, rect, m_point3);
}

PointD CTriangle::UpdateVertex(const RectD& previousFrame, const RectD& newFrame, const PointD& point)
{
	PointD newPoint;
	newPoint.x = newFrame.leftTop.x + newFrame.width * (point.x - previousFrame.leftTop.x) / (previousFrame.width);
	newPoint.y = newFrame.leftTop.y + newFrame.height * (point.y - previousFrame.leftTop.y) / (previousFrame.height);
	return newPoint;
}
