#include "CGroup.h"
#include <algorithm>
#include <stdexcept>

CGroup::CGroup()
{
	CLineStyleEnumerator lineStyleEnumerator(m_shapes);
	m_compositeLineStyle = std::make_shared<CCompositeLineStyle>(CLineStyleEnumerator(lineStyleEnumerator));

	CFillStyleEnumerator fillStyleEnumerator(m_shapes);
	m_compositeFillStyle = std::make_shared<CCompositeFillStyle>(CFillStyleEnumerator (fillStyleEnumerator));
}

std::optional<RectD> CGroup::GetFrame() const
{
	if (GetShapesCount() == 0)
	{
		return std::nullopt;
	}

	std::vector<double> leftCoordinates;
	std::vector<double> rightCoordinates;
	std::vector<double> topCoordinates;
	std::vector<double> bottomCoordinates;

	RectD frame;
	bool isNotNullFramesInGroup = false;
	for (const auto& shape : m_shapes)
	{
		if (shape->GetFrame())
		{
			frame = *shape->GetFrame();
			leftCoordinates.push_back(frame.left);
			rightCoordinates.push_back(frame.left + frame.width);
			topCoordinates.push_back(frame.top);
			bottomCoordinates.push_back(frame.top + frame.height);
			isNotNullFramesInGroup = true;
		}
	}

	if (!isNotNullFramesInGroup)
	{
		return std::nullopt;
	}

	double left = *std::min_element(leftCoordinates.begin(), leftCoordinates.end());
	double right = *std::min_element(topCoordinates.begin(), topCoordinates.end());
	RectD resultFrame{ left, right, *std::max_element(rightCoordinates.begin(), rightCoordinates.end()) - left, *std::max_element(bottomCoordinates.begin(), bottomCoordinates.end()) - right };
	return resultFrame;
}

void CGroup::SetFrame(const RectD& rect)
{
	if (GetShapesCount() == 0)
	{
		throw std::logic_error("Shape group is empty");
	}

	if (!GetFrame())
	{
		return;
	}
	
	RectD previousGroupFrame = *GetFrame();
	RectD previousConcreteShapeFrame;
	double left, top, width, height;
	for (const auto& shape : m_shapes)
	{
		if (shape->GetFrame())
		{
			previousConcreteShapeFrame = *shape->GetFrame();
			left = rect.left - (previousGroupFrame.left - previousConcreteShapeFrame.left) * rect.width / previousGroupFrame.width;
			top = rect.top - (previousGroupFrame.top - previousConcreteShapeFrame.top) * rect.height / previousGroupFrame.height;
			width = previousConcreteShapeFrame.width * rect.width / previousGroupFrame.width;
			height = previousConcreteShapeFrame.height * rect.height / previousGroupFrame.height;

			shape->SetFrame({ left, top, width, height });
		}
	}
}

const std::shared_ptr<ILineStyle> CGroup::GetOutlineStyle()
{
	return m_compositeLineStyle;
}

std::shared_ptr<const ILineStyle> CGroup::GetOutlineStyle() const
{
	return m_compositeLineStyle;
}

const std::shared_ptr<IStyle> CGroup::GetFillStyle()
{
	return m_compositeFillStyle;
}

std::shared_ptr<const IStyle> CGroup::GetFillStyle() const
{
	return m_compositeFillStyle;
}

void CGroup::Draw(ICanvas& canvas) const
{
	for (auto shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

std::shared_ptr<IGroup> CGroup::GetGroup()
{
	return std::make_shared<CGroup>(*this);
}

std::shared_ptr<const IGroup> CGroup::GetGroup() const
{
	return std::make_shared<CGroup>(*this);
}

std::shared_ptr<IShape> CGroup::GetShapeAtIndex(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_shapes.at(index);
}

size_t CGroup::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroup::InsertShape(std::shared_ptr<IShape> shape, size_t index)
{
	if (index == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(shape);
	}
	else if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + index, shape);
	}
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	m_shapes.erase(m_shapes.begin() + index);
}
