#include "CShape.h"

CShape::CShape()
	: m_simpleLineStyle(std::make_shared<CSimpleLineStyle>())
	, m_simpleFillStyle(std::make_shared<CSimpleFillStyle>())
{
}

const std::shared_ptr<ILineStyle> CShape::GetOutlineStyle()
{
	return m_simpleLineStyle;
}

std::shared_ptr<const ILineStyle> CShape::GetOutlineStyle() const
{
	return m_simpleLineStyle;
}

const std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_simpleFillStyle;
}

std::shared_ptr<const IStyle> CShape::GetFillStyle() const
{
	return m_simpleFillStyle;
}

std::shared_ptr<IGroup> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroup> CShape::GetGroup() const
{
	return nullptr;
}
