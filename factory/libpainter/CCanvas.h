#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);

	void SetColor(Color color) override;
	void DrawLine(const CPoint& fromPoint, const CPoint& toPoint) override;
	void DrawEllipse(CPoint const& left, CPoint const& top, double width, double height) override;
private:
	sf::RenderWindow& m_window;
	sf::Color m_color;
};