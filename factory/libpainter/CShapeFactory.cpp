#include "stdafx.h"
#include "CShapeFactory.h"
#include <iostream>

CShapeFactory::CShapeFactory()
	: m_actionMap(
		{
			{ "rectangle", bind(&CShapeFactory::MakeRectangle, this, std::placeholders::_1) },
			{ "triangle", bind(&CShapeFactory::MakeTriangle, this, std::placeholders::_1) },
			{ "ellipse", bind(&CShapeFactory::MakeEllipse, this, std::placeholders::_1) },
			{ "regular_polygon", bind(&CShapeFactory::MakeRegularPolygon, this, std::placeholders::_1) },
		})
{
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description)
{
	std::istringstream stream(description);
	std::string shape;
	stream >> shape;

	auto it = m_actionMap.find(shape);
	if (it == m_actionMap.end())
	{
		throw std::invalid_argument("Unknown shape");
	}

	return it->second(stream);
}

std::unique_ptr<CShape> CShapeFactory::MakeTriangle(std::istream& args) const
{
	double x1, y1, x2, y2, x3, y3;
	std::string color;
	args >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> color;
	if (args.fail())
	{
		throw std::invalid_argument("Incorrect input");
	}

	CPoint firstVertex = { x1, y1 };
	CPoint secondVertex = { x2, y2 };
	CPoint thirdVertex = { x3, y3 };

	return std::make_unique<CTriangle>(firstVertex, secondVertex, thirdVertex, GetColor(color));
}

std::unique_ptr<CShape> CShapeFactory::MakeRectangle(std::istream& args) const
{
	double x1, y1, x2, y2;
	std::string color;
	args >> x1 >> y1 >> x2 >> y2 >> color;
	if (args.fail())
	{
		throw std::invalid_argument("Incorrect input");
	}

	CPoint leftTop = { x1, y1 };
	CPoint rightBottom = { x2, y2 };

	return std::make_unique<CRectangle>(leftTop, rightBottom, GetColor(color));
}

std::unique_ptr<CShape> CShapeFactory::MakeEllipse(std::istream& args) const
{
	double x1, y1, horizontalRadius, verticalRadius;
	std::string color;
	args >> x1 >> y1 >> horizontalRadius >> verticalRadius >> color;
	if (args.fail())
	{
		throw std::invalid_argument("Incorrect input");
	}

	CPoint center = { x1, y1 };

	return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, GetColor(color));
}

std::unique_ptr<CShape> CShapeFactory::MakeRegularPolygon(std::istream& args) const
{
	double x1, y1, radius;
	size_t vertexCount;
	std::string color;
	args >> x1 >> y1 >> radius >> vertexCount >> color;
	if (args.fail())
	{
		throw std::invalid_argument("Incorrect input");
	}

	CPoint center = { x1, y1 };

	return std::make_unique<CRegularPolygon>(center, radius, vertexCount, GetColor(color));
}

Color CShapeFactory::GetColor(std::string const& color) const
{
	if (color == "green")
	{
		return Color::GREEN;
	}
	else if (color == "red")
	{
		return Color::RED;
	}

	else if (color == "blue")
	{
		return Color::BLUE;
	}
	else if (color == "yellow")
	{
		return Color::YELLOW;
	}
	else if (color == "pink")
	{
		return Color::PINK;
	}
	else if (color == "black")
	{
		return Color::BLACK;
	}
	else
	{
		throw std::invalid_argument("Invalid color");
	}
}