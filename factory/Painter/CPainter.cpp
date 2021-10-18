#include "stdafx.h"
#include "CPainter.h"

CPainter::CPainter()
{
}

void CPainter::DrawPicture(const CPictureDraft& draft, ICanvas& canvas)
{
	for (const auto& shape : draft)
	{
		shape.Draw(canvas);
	}
}
