#pragma once
#include "IGroupShape.h"
#include <vector>

class CGroupShape : public IGroupShape
{
public:
	CGroupShape();
	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::shared_ptr<IOutlineStyle> GetOutlineStyle()const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	const std::shared_ptr<IStyle> GetFillStyle()const override;

	void Draw(ICanvas& canvas) const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;
	size_t GetShapesCount() const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};