#include "stdafx.h"
#include "CRegularPolygon.h"
#define _USE_MATH_DEFINES
#include <math.h>

CRegularPolygon::CRegularPolygon(CPoint const& center, double radius, size_t vertexCount, Color color)
	: m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
	, CShape(color)
{
	double angle = 2.0 * M_PI / m_vertexCount;
	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		m_vertices.push_back(CPoint(m_center.GetX() + m_radius * sin(angle * i), m_center.GetY() + m_radius * cos(angle * i)));
	}
}

size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	
	for (size_t i = 0; i < m_vertices.size(); ++i)
	{
		canvas.DrawLine(m_vertices[i], m_vertices[(i + 1) % m_vertices.size()]);
	}
}
