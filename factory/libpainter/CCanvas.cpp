#include "stdafx.h"
#include "CCanvas.h"
#include <stdlib.h>

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::SetColor(Color color)
{
	if (color == Color::GREEN)
	{
		m_color = sf::Color(0, 255, 0);
	}
	else if (color == Color::RED)
	{
		m_color = sf::Color(255, 0, 0);
	}

	else if (color == Color::BLUE)
	{
		m_color = sf::Color(0, 0, 255);
	}
	else if (color == Color::YELLOW)
	{
		m_color = sf::Color(255, 179, 0);
	}
	else if (color == Color::PINK)
	{
		m_color = sf::Color(252, 15, 192);
	}
	else if (color == Color::BLACK)
	{
		m_color = sf::Color(0, 0, 0);
	}
}

void CCanvas::DrawLine(const CPoint& fromPoint, const CPoint& toPoint)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f((float)fromPoint.GetX(), (float)fromPoint.GetY());
	line[1].position = sf::Vector2f((float)toPoint.GetX(), (float)toPoint.GetY());

	line[0].color = m_color;
	line[1].color = m_color;

	m_window.draw(line);
}

void CCanvas::DrawEllipse(CPoint const& left, CPoint const& top, double width, double height)
{
	float x = abs((float)left.GetX());
	float y = abs((float)top.GetY());
	float horizontalRadius = (float)width / 2;
	float verticalRadius = (float)height / 2;

	sf::CircleShape circle;
	circle.setPosition(x, y);
	circle.setRadius(horizontalRadius);

	float xScale = horizontalRadius / verticalRadius;
	float yScale = verticalRadius / horizontalRadius;
	circle.setScale(xScale, yScale);

	circle.setOutlineThickness(std::max(xScale, yScale));
	circle.setOutlineColor(m_color);
	m_window.draw(circle);
}
