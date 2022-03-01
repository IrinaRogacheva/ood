#pragma once
#include "IDrawable.h"
#include "ILineStyle.h"
#include "CommonTypes.h"
#include <memory>

class IGroup;

class IShape : public IDrawable
{
public:
	virtual std::optional<RectD> GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual const std::shared_ptr<ILineStyle> GetOutlineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetOutlineStyle() const = 0;

	virtual const std::shared_ptr<IStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroup> GetGroup() = 0;
	virtual std::shared_ptr<const IGroup> GetGroup() const = 0;

	virtual ~IShape() = default;
};