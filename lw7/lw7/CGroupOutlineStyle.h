#pragma once
#include <functional>
#include "IOutlineStyle.h"

typedef std::function<void(std::function<void(IOutlineStyle&)>)> OutlineStyleEnumerator;

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(OutlineStyleEnumerator enumerator);
	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	std::optional<int> GetThickness() const override;
	void SetThickness(int thickness) override;
private:
	OutlineStyleEnumerator m_enumerator;
};