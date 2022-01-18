#include "CCanvas.h"
#include <boost/format.hpp>
#include <sstream>
#include <iomanip>

CCanvas::CCanvas(std::ostream& imageFile)
	: m_imageFile(imageFile)
{
	m_imageFile << "<svg version = \"1.1\" xmlns = \"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">\n";
}

CCanvas::~CCanvas()
{
	m_imageFile << "</svg>\n";
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = ConvertColorToHex(color);
}

void CCanvas::SetLineThickness(int thickness)
{
	m_lineThickness = thickness;
}

void CCanvas::BeginFill(RGBAColor color)
{
	if (m_isPathTagOpened)
	{
		m_imageFile << "\" />\n";
		m_isPathTagOpened = false;
	}
	m_fillColor = ConvertColorToHex(color);
	m_imageFile << boost::format(R"(<g fill="#%1%" >)") % *m_fillColor;
}

void CCanvas::EndFill()
{
	if (m_isPathTagOpened)
	{
		m_imageFile << "\" />\n";
		m_isPathTagOpened = false;
	}
	m_fillColor = std::nullopt;
	m_imageFile << "</g>\n";
}

void CCanvas::MoveTo(double x, double y)
{
	m_startX = x;
	m_startY = y;
	if (m_isPathTagOpened)
	{
		m_imageFile << "\" />\n";
		m_isPathTagOpened = false;
	}
}

void CCanvas::LineTo(double x, double y)
{
	if (!m_isPathTagOpened)
	{
		m_imageFile << boost::format(R"(<path stroke = "#%1%" stroke-width = "%2%px" d="M %3% %4% L %5% %6% )")
			% m_lineColor % m_lineThickness % m_startX % m_startY % x % y;
		m_isPathTagOpened = true;
	}
	else
	{
		m_imageFile << boost::format(R"(L %1% %2% )")
			% x % y;
	}
	m_startX = x;
	m_startY = y;
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	double rx = width / 2;
	double ry = height / 2;
	double cx = left + rx;
	double cy = top + ry;
	m_imageFile << boost::format(R"(<ellipse cx = "%1%" cy = "%2%" rx = "%3%" ry = "%4%" stroke = "#%5%" stroke-width = "%6%px"/>)")
		% cx % cy % rx % ry % m_lineColor % m_lineThickness
		<< std::endl;
}

std::string CCanvas::ConvertColorToHex(RGBAColor color)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(6) << std::hex << color;
	return stream.str();
}