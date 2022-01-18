#include "CEditor.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include <boost/algorithm/string.hpp>
#include <map>

using namespace std::placeholders;

CEditor::CEditor(std::istream& in, std::ostream& out)
	: m_menu(std::cin, std::cout)
	, m_document(std::make_unique<CDocument>())
	, m_in(in)
	, m_out(out)
{
	m_menu.AddItem("insertParagraph", "InsertParagraph <position>|end <text>", std::bind(&CEditor::InsertParagraph, this));
	m_menu.AddItem("insertImage", "InsertImage <position>|end <width> <height> <path>", std::bind(&CEditor::InsertImage, this));
	m_menu.AddItem("setTitle", "SetTitle <title>", std::bind(&CEditor::SetTitle, this));
	m_menu.AddItem("list", "Write title and document items", std::bind(&CEditor::List, this));
	m_menu.AddItem("replaceText", "ReplaceText <position> <text>", std::bind(&CEditor::ReplaceText, this));
	m_menu.AddItem("resizeImage", "ResizeImage <position> <width> <height>", std::bind(&CEditor::ResizeImage, this));
	m_menu.AddItem("deleteItem", "DeleteItem <position>", std::bind(&CEditor::DeleteItem, this));
	m_menu.AddItem("help", "Show available commands", std::bind(&CEditor::Help, this));
	m_menu.AddItem("undo", "Undo the action of a previously entered command", std::bind(&CEditor::Undo, this));
	m_menu.AddItem("redo", "Execute a previously canceled command", std::bind(&CEditor::Redo, this));
	m_menu.AddItem("save", "Save <path>", std::bind(&CEditor::Save, this));
	m_menu.AddItem("exit", "Exit", std::bind(&CEditor::Exit, this));
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::Exit()
{
	m_menu.Exit();
}

void CEditor::InsertParagraph()
{
	try
	{
		auto paragraphInfo = GetParagraphInfo();
		m_document->InsertParagraph(paragraphInfo.text, paragraphInfo.position);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::InsertImage()
{
	try
	{
		auto imageInfo = GetImageInfo();
		m_document->InsertImage(imageInfo.path, imageInfo.width, imageInfo.height, imageInfo.position);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::ReplaceText()
{
	auto info = GetReplaceTextInfo();

	if (info.position >= m_document->GetItemsCount())
	{
		throw std::invalid_argument("Wrong position argument");
	}

	auto item = m_document->GetItem(info.position);
	if (!item.GetParagraph())
	{
		throw std::invalid_argument("There is no paragraph in this position");
	}

	item.GetParagraph()->SetText(info.text);
}

void CEditor::ResizeImage()
{
	size_t pos;
	int width, height;
	m_in >> pos >> width >> height;
	if (m_in.fail())
	{
		throw std::invalid_argument("Invalid args");
	}

	if (pos >= m_document->GetItemsCount())
	{
		throw std::invalid_argument("Wrong position argument");
	}

	auto item = m_document->GetItem(pos);
	if (!item.GetImage())
	{
		throw std::invalid_argument("There is no image in this position");
	}

	try
	{
		item.GetImage()->Resize(width, height);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::DeleteItem()
{
	size_t pos;
	m_in >> pos;
	if (m_in.fail())
	{
		throw std::invalid_argument("Invalid position argument");
	}

	try
	{
		m_document->DeleteItem(pos);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

//закрывать теги html
void CEditor::Save()
{
	std::string path;
	getline(m_in, path);
	boost::algorithm::trim(path);

	if (path.back() != '/')
	{
		path += '/';
	}
	
	std::filesystem::create_directories(path);
	std::ofstream htmlFile(path + "index.html");

	htmlFile << "<!DOCTYPE html><html><head>" << "<title>" << EncodeSpecialCharacters(m_document->GetTitle()) << "</title><body>";

	for (auto index = 0; index < m_document->GetItemsCount(); index++)
	{
		if (m_document->GetItem(index).GetImage())
		{
			auto image = m_document->GetItem(index).GetImage();

			htmlFile << "<img src=\"" + image->GetPath().string() + "\" width=\"" + std::to_string(image->GetWidth()) + "\" height=\"" + std::to_string(image->GetHeight()) + "\" />" << std::endl;

			std::string imgDirectory = std::filesystem::path(path).string() + IMG_DIRECTORY_NAME;
			std::filesystem::create_directories(imgDirectory);

			std::filesystem::copy_file(image->GetPath(), std::filesystem::path(path).string() + image->GetPath().string(), std::filesystem::copy_options::overwrite_existing);
		}
		else
		{
			auto paragraph = m_document->GetItem(index).GetParagraph();

			htmlFile << "<p>" + EncodeSpecialCharacters(paragraph->GetText()) + "</p>" << std::endl;
		}

		htmlFile << "</body>" << "</html>";
	}
}

void CEditor::SetTitle()
{
	try
	{
		std::string title;
		getline(m_in, title);
		m_document->SetTitle(title);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << "\n";
	}
}

void CEditor::List() const
{
	std::cout << "Title: " << m_document->GetTitle() << "\n";

	for (auto i = 0; i < m_document->GetItemsCount(); i++)
	{
		std::cout << i << ". ";

		auto item = m_document->GetItem(i);
		if (item.GetParagraph())
		{
			m_out << "Paragraph: " << item.GetParagraph()->GetText() << "\n";
		}

		if (item.GetImage())
		{
			m_out << "Image: " << item.GetImage()->GetWidth() << " " << item.GetImage()->GetHeight() << " " << item.GetImage()->GetPath() << "\n";
		}
	}
}

void CEditor::Help() const
{
	m_menu.ShowInstructions();
}

void CEditor::Undo()
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		std::cout << "The undo operation is not available\n";
	}
}

void CEditor::Redo()
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		std::cout << "The redo operation is not available\n";
	}
}

CEditor::ImageInfo CEditor::GetImageInfo()
{
	std::string args;
	getline(m_in, args);

	std::istringstream in(args);
	size_t pos = GetPosition(in);

	int width, height;
	in >> width >> height;
	if (in.fail())
	{
		throw std::invalid_argument("The width and length must be numbers");
	}

	std::string path;
	getline(in, path);
	boost::algorithm::trim(path);
	return { path, width, height, pos };
}

CEditor::ParagraphInfo CEditor::GetReplaceTextInfo()
{
	std::string args;
	getline(m_in, args);

	std::istringstream in(args);
	size_t pos;
	in >> pos;
	if (in.fail())
	{
		throw std::invalid_argument("Invalid position argument");
	}

	std::string text;
	getline(in, text);
	return { pos, text };
}

CEditor::ParagraphInfo CEditor::GetParagraphInfo()
{
	std::string args;
	getline(m_in, args);

	std::istringstream in(args);
	size_t pos = GetPosition(in);

	std::string text;
	getline(in, text);
	return {pos, text};
}

size_t CEditor::GetPosition(std::istringstream& in)
{
	std::string pos;
	in >> pos;
	if (pos == "end")
	{
		return m_document->GetItemsCount();
	}
	else
	{
		try
		{
			return std::stoi(pos);
		}
		catch (...)
		{
			throw std::invalid_argument("Invalid position argument");
		}
	}
}

std::string CEditor::EncodeSpecialCharacters(std::string str) const
{
	std::map<std::string, std::string> escapeChars = {
		{ "<", "&lt;" },
		{ ">", "&gt;" },
		{ "'", "&apos;" },
		{ "&", "&amp;" },
		{ "\"", "&quot;" },
	};

	for (auto escapeChar : escapeChars)
	{
		boost::replace_all(str, escapeChar.first, escapeChar.second);
	}
	return str;
}