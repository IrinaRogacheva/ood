#pragma once
#include "IStyle.h"
#include "CFillStyleEnumerator.h"

class CCompositeFillStyle : public IStyle
{
public:
	CCompositeFillStyle(CFillStyleEnumerator fillStyleEnumerator);

	std::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(const RGBAColor color) override;
private:
	CFillStyleEnumerator m_fillStyleEnumerator;
};