#pragma once
#include <optional>
#include "IStyle.h"

class ILineStyle: public IStyle
{
public:
	virtual std::optional<int> GetThickness() const = 0;
	virtual void SetThickness(int thickness) = 0;
	
	virtual ~ILineStyle() = default;
};