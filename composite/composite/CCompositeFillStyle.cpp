#include "CCompositeFillStyle.h"

CCompositeFillStyle::CCompositeFillStyle(CFillStyleEnumerator fillStyleEnumerator)
	: m_isEnable(false)
	, m_fillStyleEnumerator(fillStyleEnumerator)
{
}

std::optional<bool> CCompositeFillStyle::IsEnabled() const
{
	std::optional<bool> result;
	bool isFirstStyle = true;

	IFillStyleEnumerator::Callback callback = [&](IStyle& style)
	{
		if (isFirstStyle)
		{
			result = style.IsEnabled();
			isFirstStyle = false;
		}
		else if (style.IsEnabled() != result)
		{
			result = std::nullopt;
		}
	};

	m_fillStyleEnumerator.EnumerateAll(callback);
	return result;
}

void CCompositeFillStyle::Enable(bool enable)
{
	IFillStyleEnumerator::Callback callback = [&](IStyle& style)
	{
		style.Enable(enable);
	};

	m_fillStyleEnumerator.EnumerateAll(callback);
}

std::optional<RGBAColor> CCompositeFillStyle::GetColor() const
{
	std::optional<RGBAColor> result;
	bool isFirstStyle = true;

	IFillStyleEnumerator::Callback callback = [&](IStyle& style)
	{
		if (isFirstStyle)
		{
			result = style.GetColor();
			isFirstStyle = false;
		}
		else if (style.GetColor() != result)
		{
			result = std::nullopt;
		}
	};

	m_fillStyleEnumerator.EnumerateAll(callback);
	return result;
}

void CCompositeFillStyle::SetColor(const RGBAColor color)
{
	IFillStyleEnumerator::Callback callback = [&](IStyle& style)
	{
		style.SetColor(color);
	};

	m_fillStyleEnumerator.EnumerateAll(callback);
}