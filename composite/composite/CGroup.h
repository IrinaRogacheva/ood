#pragma once
#include "IGroup.h"
#include "CCompositeLineStyle.h"
#include "CCompositeFillStyle.h"
#include "CLineStyleEnumerator.h"
#include "CFillStyleEnumerator.h"

class CGroup : public IGroup
{
public:
	CGroup();
	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	const std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;
	void SetOutlineStyle(std::shared_ptr<ILineStyle> style) override;

	const std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;
	void SetFillStyle(std::shared_ptr<IStyle> style) override;

	void Draw(ICanvas& canvas) const override;

	std::shared_ptr<IGroup> GetGroup() override;
	std::shared_ptr<const IGroup> GetGroup() const override;

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override;
	size_t GetShapesCount() const override;
	void InsertShape(std::shared_ptr<IShape> shape, size_t index = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<ILineStyle> m_compositeLineStyle;
	std::shared_ptr<IStyle> m_compositeFillStyle;
};