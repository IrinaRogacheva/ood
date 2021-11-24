#pragma once
#include <iostream>
#include <iomanip>

// ������������ ���� ����������� ���������� (���������� ��� ���������)
namespace graphics_lib
{
// ����� ��� ���������
class ICanvas
{
public:
	// ��������� ����� � ������� 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	// ������ "����" � ����� x, y
	virtual void MoveTo(int x, int y) = 0;
	// ������ ����� � ������� �������, ���������� ���� � ����� x,y
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// ���������� ������ ��� ���������
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		std::cout << "Color: #" << std::setw(6) << std::hex << std::setfill('0') << rgbColor << std::endl;
	}
	void MoveTo(int x, int y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int x, int y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
} // namespace graphics_lib