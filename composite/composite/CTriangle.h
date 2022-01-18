#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(const PointD& point1, const PointD& point2, const PointD& point3);
	void Draw(ICanvas& canvas) const final;

	std::optional<RectD> GetFrame() const final;
	void SetFrame(const RectD& rect) final;

private:
	PointD UpdateVertex(const RectD& previousFrame, const RectD& newFrame, const PointD& point);

	PointD m_point1;
	PointD m_point2;
	PointD m_point3;
};
