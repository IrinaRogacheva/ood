#include "CSimpleLineStyle.h"

CSimpleLineStyle::CSimpleLineStyle()
	: m_isEnable(false)
	, m_color(0)
	, m_thickness(1)
{
}

std::optional<bool> CSimpleLineStyle::IsEnabled() const
{
	return m_isEnable;
}

void CSimpleLineStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<RGBAColor> CSimpleLineStyle::GetColor() const
{
	return m_color;
}

void CSimpleLineStyle::SetColor(const RGBAColor color)
{
	m_color = color;
}

std::optional<int> CSimpleLineStyle::GetThickness() const
{
	return m_thickness;
}

void CSimpleLineStyle::SetThickness(int thickness)
{
	m_thickness = thickness;
}
