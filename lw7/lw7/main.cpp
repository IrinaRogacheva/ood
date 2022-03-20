#include "CTriangle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "IShape.h"
#include "CommonTypes.h"
#include "CGroupShape.h"
#include "CSlide.h"
#include <fstream>
#include "CCanvas.h"
#include <iostream>

//этот кусок кода у меня был в CCanvas
#include <sstream>
#include <iomanip>

std::string ConvertColorToHex(RGBAColor color)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(6) << std::hex << color;
	return stream.str();
}
//

void ColorizeShape(std::shared_ptr<IShape>& shape, RGBAColor fillColor, RGBAColor outlineColor, std::optional<int> lineThickness = std::nullopt)
{
	auto fillStyle = shape->GetFillStyle();
	auto outlineStyle = shape->GetOutlineStyle();

	fillStyle->SetColor(fillColor);
	fillStyle->Enable(true);
	outlineStyle->SetColor(outlineColor);
	outlineStyle->Enable(true);
	if (lineThickness)
	{
		outlineStyle->SetThickness(*lineThickness);
	}
}

int main()
{
	try
	{
		std::ofstream canvasFile("canvas.svg");
		CCanvas canvas;

		std::shared_ptr<IShape> body = std::make_shared<CTriangle>(PointD{ 200, 400 }, PointD{ 300, 200 }, PointD{ 400, 400 });
		ColorizeShape(body, 0xd3d3d3, 0xa9a9a9);

		std::shared_ptr<IShape> head = std::make_shared<CTriangle>(PointD{ 210, 230 }, PointD{ 330, 110 }, PointD{ 430, 300 });
		ColorizeShape(head, 0xd3d3d3, 0xa9a9a9);

		std::shared_ptr<IShape> leftEye = std::make_shared<CEllipse>(PointD{ 310, 220 }, 4, 4);
		ColorizeShape(leftEye, 0x000000, 0x000000);

		std::shared_ptr<IShape> rightEye = std::make_shared<CEllipse>(PointD{ 330, 200 }, 4, 4);
		ColorizeShape(rightEye, 0x000000, 0x000000);

		std::shared_ptr<IShape> nose = std::make_shared<CEllipse>(PointD{ 430, 300 }, 5, 5);
		ColorizeShape(nose, 0x000000, 0x000000);

		std::shared_ptr<IShape> leftEar = std::make_shared<CEllipse>(PointD{ 192, 212 }, 50, 50);
		ColorizeShape(leftEar, 0xD3D3D3, 0xA9A9A9);

		std::shared_ptr<IShape> rightEar = std::make_shared<CEllipse>(PointD{ 312, 92 }, 50, 50);
		ColorizeShape(rightEar, 0xD3D3D3, 0xA9A9A9);

		auto mouseHead = std::make_shared<CGroupShape>();
		mouseHead->InsertShape(head);
		mouseHead->InsertShape(leftEye);
		mouseHead->InsertShape(rightEye);
		mouseHead->InsertShape(leftEar);
		mouseHead->InsertShape(rightEar);
		mouseHead->InsertShape(nose);

		auto mouse = std::make_shared<CGroupShape>();
		mouse->InsertShape(body);
		mouse->InsertShape(mouseHead);

		std::shared_ptr<IShape> cheese = std::make_shared<CRectangle>(PointD{ 450, 350 }, 70, 50);
		ColorizeShape(cheese, 0xFFFF00, 0xFFD700, 3);

		RectD frame = *mouse->GetFrame();
		std::cout << frame.leftTop.x << " " << frame.leftTop.y << " " << frame.width << " " << frame.height << std::endl;
		mouse->SetFrame({ 150, 40, 350, 300 });

		CSlide slide;
		slide.InsertShape(mouse);
		slide.InsertShape(cheese);
		slide.Draw(canvas);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}