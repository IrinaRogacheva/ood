#pragma once
#include "IStyle.h"
#include "IDrawable.h"
#include "IOutlineStyle.h"
#include <memory>

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual std::optional<RectD> GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<IOutlineStyle> GetOutlineStyle() = 0;
	virtual const std::shared_ptr<IOutlineStyle> GetOutlineStyle()const = 0;

	virtual std::shared_ptr<IStyle> GetFillStyle() = 0;
	virtual const std::shared_ptr<IStyle> GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};