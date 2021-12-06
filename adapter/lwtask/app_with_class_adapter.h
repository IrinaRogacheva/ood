#pragma once
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

// Пространство имен приложения (доступно для модификации)
namespace app_with_class_adapter
{
	class CModernGraphicsLibAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
	{
	public:
		CModernGraphicsLibAdapter(std::ostream& strm)
			: CModernGraphicsRenderer(strm)
		{
		}
		void SetColor(uint32_t rgbColor) override
		{
			auto r = float((rgbColor >> 16) & 255);
			auto g = float((rgbColor >> 8) & 255);
			auto b = float(rgbColor & 255);

			m_color = { r, g, b, 1 };
		}
		void MoveTo(int x, int y) override
		{
			m_startPoint = { x, y };
		}
		void LineTo(int x, int y) override
		{
			DrawLine(m_startPoint, { x, y }, m_color);
			MoveTo(x, y);
		}

	private:
		modern_graphics_lib::CPoint m_startPoint = { 0, 0 };
		modern_graphics_lib::CRGBAColor m_color = { 0, 0, 0, 0 };
	};

	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xffffff);
		CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		CModernGraphicsLibAdapter adaptedRenderer(std::cout);
		shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);

		PaintPicture(painter);
	}
} // namespace app_with_class_adapter