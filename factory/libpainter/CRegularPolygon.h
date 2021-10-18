#pragma once
#include "CShape.h"
#include "CPoint.h"
#include <vector>

class CRegularPolygon final : public CShape
{
public:
	CRegularPolygon(CPoint const& center, double radius, size_t vertexCount, Color color);
	void Draw(ICanvas& canvas) const;
	size_t GetVertexCount() const;
	CPoint GetCenter() const;
	double GetRadius() const;
private:
	CPoint m_center;
	double m_radius;
	size_t m_vertexCount;
	std::vector<CPoint> m_vertices;
};