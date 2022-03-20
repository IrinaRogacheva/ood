#include <iostream>
#include "CCanvas.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>

/*
CCanvas::CCanvas(sf::RenderWindow& window)
	:m_window(window)
{
}

void CCanvas::SetColor(const Color& color)
{
	switch (color)
	{
	case Color::Green:
		m_color = sf::Color::Green;
		break;
	case Color::Red:
		m_color = sf::Color::Red;
		break;
	case Color::Blue:
		m_color = sf::Color::Blue;
		break;
	case Color::Yellow:
		m_color = sf::Color::Yellow;
		break;
	case Color::Pink:
		m_color = sf::Color(255, 20, 148);
		break;
	case Color::Black:
		m_color = sf::Color::Black;
		break;
	}
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(from.x, from.y);
	line[0].color = m_color;
	line[1].position = sf::Vector2f(to.x, to.y);
	line[1].color = m_color;
	m_window.draw(line);
}

void CCanvas::DrawEllipse(float radiusX, float radiusY, const CPoint& center)
{
	sf::CircleShape circle(radiusX);
	circle.setPosition(center.x - radiusX, center.y - radiusY);
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(m_color);
	circle.scale(1, radiusY / radiusX);
	m_window.draw(circle);
}

void CCanvas::DrawRegularPolygon(float radius, const CPoint& center, float vertexCount)
{
	sf::CircleShape circle(radius, static_cast<size_t>(vertexCount));
	circle.setPosition(center.x - radius, center.y - radius);
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(m_color);
	m_window.draw(circle);
}
*/

void CCanvas::SetLineColor(const RGBAColor& color)
{
	m_lineColor = color;
	std::cout << "current line color of drawing is " << m_lineColor << std::endl;
}

void CCanvas::SetLineThickness(const int thickness)
{
	m_lineThickness = thickness;
	std::cout << "current line thickness of drawing is " << m_lineThickness << std::endl;
}

void CCanvas::SetFillColor(const RGBAColor& color)
{
	m_fillColor = color;
	std::cout << "current fill color of drawing is " << m_fillColor << std::endl;
}

void CCanvas::DrawLine(const PointD& from, const PointD& to)
{
	std::cout << "line: from " << from.x << " " << from.y << " to " << to.x << " " << to.y << " color: " << m_lineColor << std::endl;
}

void CCanvas::DrawEllipse(double radiusX, double radiusY, const PointD& center)
{
	std::cout << "ellipse: radiusX " << radiusX << " radiusY " << radiusY << " center " << center.x << " " << center.y << std::endl;
}

void CCanvas::FillEllipse(double radiusX, double radiusY, const PointD& center)
{
	std::cout << "ellipse is filled by color " << m_fillColor <<  " : radiusX " << radiusX << " radiusY " << radiusY << " center " << center.x << " " << center.y << std::endl;
}

void CCanvas::DrawRegularPolygon(double radius, const PointD& center, int vertexCount)
{
	std::cout << "regularPolygon: radius " << radius << " center " << center.x << " " << center.y << " vertexCount " << vertexCount << std::endl;
}

void CCanvas::FillRegularPolygon(double radius, const PointD& center, int vertexCount)
{
	std::cout << "regularPolygon: radius " << radius << " center " << center.x << " " << center.y << " vertexCount " << vertexCount << " color " << m_fillColor << std::endl;
}
