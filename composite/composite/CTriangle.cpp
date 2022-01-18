#include "CTriangle.h"
#include <algorithm>
#include <iostream>

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
		canvas.BeginFill(*GetFillStyle()->GetColor());
	}
	if (GetOutlineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetOutlineStyle()->GetColor());
		canvas.SetLineThickness(*GetOutlineStyle()->GetThickness());
	}
	canvas.MoveTo(m_point1.x, m_point1.y);
	canvas.LineTo(m_point2.x, m_point2.y);
	canvas.LineTo(m_point3.x, m_point3.y);
	canvas.LineTo(m_point1.x, m_point1.y);	
	if (GetFillStyle()->IsEnabled())
	{
		canvas.EndFill();
	}
}

std::optional<RectD> CTriangle::GetFrame() const
{
	double left = std::min({m_point1.x, m_point2.x, m_point3.x});
	double top = std::min({ m_point1.y, m_point2.y, m_point3.y });
	double right = std::max({ m_point1.x, m_point2.x, m_point3.x });
	double bottom = std::max({ m_point1.y, m_point2.y, m_point3.y });

	RectD frame{ left, top, right - left, bottom - top };
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
	newPoint.x = newFrame.left + newFrame.width * (point.x - previousFrame.left) / (previousFrame.width);
	newPoint.y = newFrame.top + newFrame.height * (point.y - previousFrame.top) / (previousFrame.height);
	return newPoint;
}
