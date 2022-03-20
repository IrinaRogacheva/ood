#include "CGroupShape.h"
#include "CGroupOutlineStyle.h"
#include "CGroupFillStyle.h"
#include <stdexcept>

CGroupShape::CGroupShape()
{
	auto outlineStyleEnumerator = [&](std::function<void(IOutlineStyle&)> callback) {
		for (auto& shape : m_shapes)
		{
			callback(*shape->GetOutlineStyle());
		}
	};

	auto fillStyleEnumerator = [&](std::function<void(IStyle&)> callback) {
		for (auto& shape : m_shapes)
		{
			callback(*shape->GetFillStyle());
		}
	};

	m_outlineStyle = std::make_shared<CGroupOutlineStyle>(outlineStyleEnumerator);
	m_fillStyle = std::make_shared<CGroupFillStyle>(fillStyleEnumerator);
}

std::optional<RectD> CGroupShape::GetFrame() const
{
	if (GetShapesCount() == 0)
	{
		return std::nullopt;
	}

	double maxX = std::numeric_limits<double>::min();
	double minX = std::numeric_limits<double>::max();
	double maxY = std::numeric_limits<double>::min();
	double minY = std::numeric_limits<double>::max();

	RectD frame;
	bool isNotNullFramesInGroup = false;
	for (const auto& shape : m_shapes)
	{
		if (shape->GetFrame())
		{
			frame = *shape->GetFrame();
			
			maxX = std::max(maxX, frame.leftTop.x + frame.width);
			minX = std::min(minX, frame.leftTop.x);
			maxY = std::max(maxY, frame.leftTop.y + frame.height);
			minY = std::min(minY, frame.leftTop.y);
			isNotNullFramesInGroup = true;
		}
	}

	if (!isNotNullFramesInGroup)
	{
		return std::nullopt;
	}

	return RectD{ { minX, minY }, maxX - minX, maxY - minY };
}

void CGroupShape::SetFrame(const RectD& rect)
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

			left = rect.leftTop.x + (previousConcreteShapeFrame.leftTop.x - previousGroupFrame.leftTop.x) * rect.width / previousGroupFrame.width;
			top = rect.leftTop.y + (previousConcreteShapeFrame.leftTop.y - previousGroupFrame.leftTop.y) * rect.height / previousGroupFrame.height;
			width = previousConcreteShapeFrame.width * rect.width / previousGroupFrame.width;
			height = previousConcreteShapeFrame.height * rect.height / previousGroupFrame.height;

			shape->SetFrame({ left, top, width, height });
		}
	}
}

std::shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const std::shared_ptr<IOutlineStyle> CGroupShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CGroupShape::GetFillStyle()
{
	return m_fillStyle;
}

const std::shared_ptr<IStyle> CGroupShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CGroupShape::Draw(ICanvas& canvas) const
{
	for (auto const& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return std::make_shared<CGroupShape>(*this);
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return std::make_shared<CGroupShape>(*this);
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_shapes.at(index);
}

size_t CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(shape);
	}
	else if (position >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + position, shape);
	}
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	m_shapes.erase(m_shapes.begin() + index);
}
