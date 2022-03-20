#pragma once
#include "CommonTypes.h"
#include "ICanvas.h"
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#undef min
#undef max
//#include <SFML/Graphics.hpp>


class CCanvas : public ICanvas
{
public:
	//CCanvas(sf::RenderWindow& window);
	void SetLineColor(const RGBAColor& color) override;
	void SetLineThickness(const int thickness) override;
	void SetFillColor(const RGBAColor& color) override;
	void DrawLine(const PointD& from, const PointD& to) override;
	void DrawEllipse(double radiusX, double radiusY, const PointD& center) override;
	void FillEllipse(double radiusX, double radiusY, const PointD& center) override;
	void DrawRegularPolygon(double radius, const PointD& center, int vertexCount) override;
	void FillRegularPolygon(double radius, const PointD& center, int vertexCount) override;

	/*
	void SetColor(const Color& color) override;
	void DrawLine(const CPoint& from, const CPoint& to) override;
	void DrawEllipse(float radiusX, float radiusY, const CPoint& center) override;
	void DrawRegularPolygon(float radius, const CPoint& center, float vertexCount) override;
	*/
private:
	//sf::Color m_color;
	//sf::RenderWindow& m_window;
	RGBAColor m_lineColor = 0x000000;
	RGBAColor m_fillColor = 0xffffff;
	int m_lineThickness = 1;
};
