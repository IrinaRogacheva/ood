#include "CSimpleFillStyle.h"

CSimpleFillStyle::CSimpleFillStyle()
	: m_isEnable(false)
	, m_color(0xffffff)
{
}

std::optional<bool> CSimpleFillStyle::IsEnabled() const
{
	return m_isEnable;
}

void CSimpleFillStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<RGBAColor> CSimpleFillStyle::GetColor() const
{
	return m_color;
}

void CSimpleFillStyle::SetColor(const RGBAColor color)
{
	m_color = color;
}