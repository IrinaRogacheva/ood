#pragma once
#include <memory>
#include <vector>
#include "IShape.h"

class CSlide : public IDrawable
{
public:
	double GetWidth()const;
	double GetHeight()const;

	RGBAColor GetBackgroundColor() const;
	void SetBackgroundColor(RGBAColor color);

	size_t GetShapesCount() const;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShapeAtIndex(size_t index);

	void Draw(ICanvas& canvas) const override;
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	RGBAColor m_backgroundColor = 0xffffff;
	double m_width = 800;
	double m_height = 600;
};
