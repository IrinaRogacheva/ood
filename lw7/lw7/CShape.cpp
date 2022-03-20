#include "CShape.h"
#include "CShapeOutlineStyle.h"
#include "CShapeFillStyle.h"

CShape::CShape()
	: m_outlineStyle(std::make_shared<CShapeOutlineStyle>())
	, m_fillStyle(std::make_shared<CShapeFillStyle>())
{
}

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

const std::shared_ptr<IStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}
