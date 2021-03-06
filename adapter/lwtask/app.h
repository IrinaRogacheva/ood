#pragma once
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

// ???????????? ???? ?????????? (???????? ??? ???????????)
namespace app
{
	class CModernGraphicsLibAdapter : public graphics_lib::ICanvas
	{
	public:
		CModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
			: m_renderer(renderer)
		{
			m_renderer.BeginDraw();
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
			m_renderer.DrawLine(m_startPoint, { x, y }, m_color);
			MoveTo(x, y);
		}
		~CModernGraphicsLibAdapter()
		{
			m_renderer.EndDraw();
		}

	private:
		modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
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
		modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
		CModernGraphicsLibAdapter adaptedRenderer(renderer);
		shape_drawing_lib::CCanvasPainter painter(adaptedRenderer);

		PaintPicture(painter);
	}
} // namespace app