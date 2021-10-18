#pragma once
#include "IShapeFactory.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CRegularPolygon.h"
#include "EColor.h"
#include <sstream>
#include <functional>
#include <map>
#include <vector>

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<CShape> CreateShape(std::string const& description);
private:
	std::unique_ptr<CShape> MakeTriangle(std::istream& args) const;
	std::unique_ptr<CShape> MakeRectangle(std::istream& args) const;
	std::unique_ptr<CShape> MakeEllipse(std::istream& args) const;
	std::unique_ptr<CShape> MakeRegularPolygon(std::istream& args) const;
private:
	Color GetColor(std::string const& color) const;
	typedef std::function<std::unique_ptr<CShape>(std::istream& args)> Handler;
	typedef std::map<std::string, Handler> ActionMap;
	const ActionMap m_actionMap;
};