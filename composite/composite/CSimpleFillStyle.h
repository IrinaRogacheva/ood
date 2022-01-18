#pragma once
#include "IStyle.h"

class CSimpleFillStyle : public IStyle
{
public:
	CSimpleFillStyle();
	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor()const override;
	void SetColor(const RGBAColor color) override;
private:
	bool m_isEnable;
	RGBAColor m_color;
};