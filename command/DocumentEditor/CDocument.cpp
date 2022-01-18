#include "CDocument.h"
#include "CParagraph.h"
#include "CImage.h"
#include "Commands.h"

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(m_history, text);
	auto documentItem = std::make_shared<CDocumentItem>(paragraph);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertDocumentItem>(m_items, documentItem, position.get()));
	return paragraph;
}

std::shared_ptr<IImage> CDocument::InsertImage(const Path& path, int width, int height, boost::optional<size_t> position)
{
	auto image = std::make_shared<CImage>(m_history, path, width, height);
	auto imageItem = std::make_shared<CDocumentItem>(image);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertDocumentItem>(m_items, imageItem, position.get()));
	return image;
}

void CDocument::SetTitle(const std::string& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeText>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("Wrong position argument");
	}
	return *m_items.at(index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::invalid_argument("Wrong position argument");
	}
	return *m_items.at(index);
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteDocumentItem>(m_items, m_items.at(index), index));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}
