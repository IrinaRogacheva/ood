#pragma once
#include "ILineStyle.h"

class CSimpleLineStyle : public ILineStyle
{
public:
	CSimpleLineStyle();
	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor()const override;
	void SetColor(const RGBAColor color) override;

	std::optional<int> GetThickness() const override;
	void SetThickness(int thickness) override;

private:
	bool m_isEnable;
	RGBAColor m_color;
	int m_thickness;
};