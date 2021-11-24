#pragma once
#include "IImage.h"
#include "CHistory.h"
#include <set>

class CImage : public IImage
{
public:
	CImage(CHistory& history, const Path& path, const int width, const int height);
	Path GetPath()const;
	int GetWidth()const;
	int GetHeight()const;
	void Resize(int width, int height);
private:
	std::string GenerateRandomName() const;

	CHistory& m_history;
	Path m_path;
	int m_width;
	int m_height;

	const std::set<std::string> SUPPORTED_EXTENSIONS{".jpeg", ".jpg", ".gif", ".png", ".apng", ".svg", ".bmp", ".bmp ico", ".png ico"};
	const size_t IMG_NAME_LEN = 10;
	const std::string IMG_DIRECTORY_NAME = "images/";
};