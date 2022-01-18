#pragma once
#include "ICanvas.h"
#include <optional>
#include <ostream>

class CCanvas: public ICanvas
{
public:
	CCanvas(std::ostream& imageFile);
	void SetLineColor(RGBAColor color) override;
	void SetLineThickness(int thickness) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;
	~CCanvas();
private:
	std::string ConvertColorToHex(RGBAColor color);

	std::string m_lineColor = "000000";
	int m_lineThickness = 1;
	std::optional<std::string> m_fillColor = "ffffff";
	double m_startX = 0;
	double m_startY = 0;
	std::ostream& m_imageFile;
	bool m_isPathTagOpened = false;
};