#include "CSlide.h"
#include "CRectangle.h"
#include <stdexcept>

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundColor = color;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_shapes.at(index);
}

void CSlide::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
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

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	m_shapes.erase(m_shapes.begin() + index);
}

void CSlide::Draw(ICanvas& canvas) const
{
	CRectangle slide({ 0, 0 }, m_width, m_height);
	auto fillStyle = slide.GetFillStyle();
	fillStyle->SetColor(m_backgroundColor);
	auto outlineStyle = slide.GetOutlineStyle();
	outlineStyle->SetColor(m_backgroundColor);
	slide.Draw(canvas);

	for (auto const& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
