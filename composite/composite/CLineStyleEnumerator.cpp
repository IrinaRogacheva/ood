#include "CLineStyleEnumerator.h"
#include <iostream>

CLineStyleEnumerator::CLineStyleEnumerator(std::vector<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
}

void CLineStyleEnumerator::EnumerateAll(Callback& callback) const
{
	for (const auto& shape : m_shapes)
	{
		callback(*shape->GetOutlineStyle());
	}
}
