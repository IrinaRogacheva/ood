#pragma once
#include "IOutlineStyle.h"

class CShapeOutlineStyle : public IOutlineStyle
{
public:
	CShapeOutlineStyle();

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