#pragma once
#include "CMenu.h"
#include "CDocument.h"

class CEditor
{
public:
	CEditor(std::istream& in, std::ostream& out);

	void Start();
private:
	struct ParagraphInfo
	{
		size_t position;
		std::string text;
	};

	struct ImageInfo
	{
		std::string path;
		int width;
		int height;
		size_t position;
	};

	void InsertParagraph();
	void InsertImage();
	void ReplaceText();
	void ResizeImage();
	void DeleteItem();
	void Save();
	void SetTitle();

	void List() const;
	void Help() const;
	void Undo();
	void Redo();

	void Exit();

	ParagraphInfo GetParagraphInfo();
	ImageInfo GetImageInfo();
	ParagraphInfo GetReplaceTextInfo();

	size_t GetPosition(std::istringstream& in);

	std::string EncodeSpecialCharacters(std::string str) const;

	const std::string IMG_DIRECTORY_NAME = "images/";

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
	std::istream& m_in;
	std::ostream& m_out;
};