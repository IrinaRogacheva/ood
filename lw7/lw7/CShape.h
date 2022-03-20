#pragma once
#include "IShape.h"
#include "IOutlineStyle.h"
#include "IGroupShape.h"
#include <vector>

class CShape : public IShape
{
public:
	CShape();

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::shared_ptr<IOutlineStyle> GetOutlineStyle()const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	const std::shared_ptr<IStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

private:
	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};