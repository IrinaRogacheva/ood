#pragma once
#include <functional>
#include "IStyle.h"

class IFillStyleEnumerator
{
public:
	typedef std::function<void(IStyle& style)> Callback;

	virtual void EnumerateAll(Callback& callback) const = 0;

	virtual ~IFillStyleEnumerator() = default;
};