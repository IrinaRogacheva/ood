#include "CShapeOutlineStyle.h"

CShapeOutlineStyle::CShapeOutlineStyle()
	: m_isEnable(false)
	, m_color(0x000000)
	, m_thickness(1)
{
}

std::optional<bool> CShapeOutlineStyle::IsEnabled() const
{
	return m_isEnable;
}

void CShapeOutlineStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<RGBAColor> CShapeOutlineStyle::GetColor() const
{
	return m_color;
}

void CShapeOutlineStyle::SetColor(const RGBAColor color)
{
	m_color = color;
}

std::optional<int> CShapeOutlineStyle::GetThickness() const
{
	return m_thickness;
}

void CShapeOutlineStyle::SetThickness(int thickness)
{
	m_thickness = thickness;
}
