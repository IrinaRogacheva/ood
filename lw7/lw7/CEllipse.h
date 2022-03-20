#pragma once

#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(PointD leftTop, double width, double height);
	void Draw(ICanvas& canvas) const final;

	std::optional<RectD> GetFrame() const final;
	void SetFrame(const RectD& rect) final;

private:
	PointD m_leftTop;
	double m_width;
	double m_height;
};