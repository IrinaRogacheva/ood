#pragma once
#include "CShape.h"
#include "CPoint.h"

class CTriangle final : public CShape
{
public:
	CTriangle(CPoint const& firstVertex, CPoint const& secondVertex, CPoint const& thirdVertex, Color color);

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};