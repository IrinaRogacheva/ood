#include "CShapeFillStyle.h"

CShapeFillStyle::CShapeFillStyle()
	: m_isEnable(false)
	, m_color(0xffffff)
{
}

std::optional<bool> CShapeFillStyle::IsEnabled() const
{
	return m_isEnable;
}

void CShapeFillStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<RGBAColor> CShapeFillStyle::GetColor() const
{
	return m_color;
}

void CShapeFillStyle::SetColor(const RGBAColor color)
{
	m_color = color;
}
