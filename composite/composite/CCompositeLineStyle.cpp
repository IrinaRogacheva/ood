#include "CCompositeLineStyle.h"

CCompositeLineStyle::CCompositeLineStyle(CLineStyleEnumerator lineStyleEnumerator)
	: m_lineStyleEnumerator(lineStyleEnumerator)
{
}

std::optional<bool> CCompositeLineStyle::IsEnabled() const
{
	std::optional<bool> result;
	bool isFirstStyle = true;

	ILineStyleEnumerator::Callback callback = [&](ILineStyle& style) 
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

	m_lineStyleEnumerator.EnumerateAll(callback);
	return result;
}

void CCompositeLineStyle::Enable(bool enable)
{
	ILineStyleEnumerator::Callback callback = [&](ILineStyle& style)
	{
		style.Enable(enable);
	};

	m_lineStyleEnumerator.EnumerateAll(callback);
}

std::optional<RGBAColor> CCompositeLineStyle::GetColor() const
{
	std::optional<RGBAColor> result;
	bool isFirstStyle = true;

	ILineStyleEnumerator::Callback callback = [&](ILineStyle& style)
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

	m_lineStyleEnumerator.EnumerateAll(callback);
	return result;
}

void CCompositeLineStyle::SetColor(const RGBAColor color)
{
	ILineStyleEnumerator::Callback callback = [&](ILineStyle& style)
	{
		style.SetColor(color);
	};

	m_lineStyleEnumerator.EnumerateAll(callback);
}

std::optional<int> CCompositeLineStyle::GetThickness() const
{
	std::optional<int> result;
	bool isFirstStyle = true;

	ILineStyleEnumerator::Callback callback = [&](ILineStyle& style)
	{
		if (isFirstStyle)
		{
			result = style.GetThickness();
			isFirstStyle = false;
		}
		else if (style.GetThickness() != result)
		{
			result = std::nullopt;
		}
	};

	m_lineStyleEnumerator.EnumerateAll(callback);
	return result;
}

void CCompositeLineStyle::SetThickness(int thickness)
{
	ILineStyleEnumerator::Callback callback = [&](ILineStyle& style)
	{
		style.SetThickness(thickness);
	};

	m_lineStyleEnumerator.EnumerateAll(callback);
}
