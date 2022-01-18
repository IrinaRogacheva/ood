#include "CFillStyleEnumerator.h"
#include <iostream>

CFillStyleEnumerator::CFillStyleEnumerator(std::vector<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CFillStyleEnumerator::EnumerateAll(Callback& callback) const
{
	for (const auto& shape : m_shapes)
	{
		callback(*shape->GetFillStyle());
	}
}
