#pragma once
#include "../libpainter/PictureDraft.h"
#include "../libpainter/ICanvas.h"

class CPainter
{
public:
	CPainter();
	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas);
};