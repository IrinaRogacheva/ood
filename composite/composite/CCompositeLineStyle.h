#pragma once
#include "ILineStyle.h"
#include "CLineStyleEnumerator.h"

class CCompositeLineStyle : public ILineStyle
{
public:
	CCompositeLineStyle(CLineStyleEnumerator lineStyleEnumerator);
	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor color) override;

	std::optional<int> GetThickness() const override;
	void SetThickness(int thickness) override;
private:
	CLineStyleEnumerator m_lineStyleEnumerator;
};