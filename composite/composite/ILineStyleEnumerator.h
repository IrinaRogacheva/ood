#pragma once
#include <functional>
#include "ILineStyle.h"

class ILineStyleEnumerator
{
public:
	typedef std::function<void(ILineStyle& style)> Callback;

	virtual void EnumerateAll(Callback& callback) const = 0;

	virtual ~ILineStyleEnumerator() = default;
};