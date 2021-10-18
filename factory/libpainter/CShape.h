#pragma once
#include "EColor.h"
#include "ICanvas.h"
#include "stdafx.h"

class CShape
{
public:
	CShape(Color color)
		: m_color(color)
	{
	}
	virtual void Draw(ICanvas& canvas) const = 0;
	Color GetColor() const
	{
		return m_color;
	}
	virtual ~CShape() = default;
	
private:
	Color m_color;
};