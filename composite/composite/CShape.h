#pragma once
#include "CommonTypes.h"
#include "ICanvas.h"
#include "IShape.h"
#include <vector>
#include <memory>
#include "CSimpleLineStyle.h"
#include "CSimpleFillStyle.h"

class CShape: public IShape
{
public:
	CShape();
	const std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;
	void SetOutlineStyle(std::shared_ptr<ILineStyle> style) override;

	const std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;
	void SetFillStyle(std::shared_ptr<IStyle> style) override;

	std::shared_ptr<IGroup> GetGroup() override;
	std::shared_ptr<const IGroup> GetGroup() const override;

private:
	std::vector<std::shared_ptr<CShape>> m_shapes;
	std::shared_ptr<ILineStyle> m_simpleLineStyle;
	std::shared_ptr<IStyle> m_simpleFillStyle;
};