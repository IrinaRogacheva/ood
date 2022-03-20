#pragma once
#include "IStyle.h"

class CShapeFillStyle : public IStyle
{
public:
	CShapeFillStyle();

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor()const override;
	void SetColor(const RGBAColor color) override;

private:
	bool m_isEnable;
	RGBAColor m_color;
};