#pragma once
#include <functional>
#include "IStyle.h"

typedef std::function<void(std::function<void(IStyle&)>)> StyleEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(StyleEnumerator enumerator);
	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;
private:
	StyleEnumerator m_enumerator;
};