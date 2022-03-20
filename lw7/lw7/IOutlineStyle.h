#pragma once
#include "IStyle.h"
#include <optional>

class IOutlineStyle : public IStyle
{
public:
	virtual std::optional<int> GetThickness() const = 0;
	virtual void SetThickness(int thickness) = 0;
};
