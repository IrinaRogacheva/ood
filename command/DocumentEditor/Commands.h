#pragma once
#include "CAbstractCommand.h"
#include "CDocument.h"
#include <iostream>

class CInsertDocumentItem : public CAbstractCommand
{
public:
	CInsertDocumentItem(std::vector<std::shared_ptr<CDocumentItem>>& items, std::shared_ptr<CDocumentItem> item, size_t position)
		: m_items(items)
		, m_item(std::move(item))
		, m_position(position)
	{
		if (position > items.size() || position < 0)
		{
			throw std::invalid_argument("Wrong position argument");
		}
	}

	CInsertDocumentItem::~CInsertDocumentItem()
	{
		if (!IsExecuted() && m_item->GetImage())
		{
			auto path = m_item->GetImage()->GetPath();
			std::filesystem::remove(path);
		}
	}
	
protected:
	void DoExecute() override
	{
		m_items.emplace(m_items.begin() + m_position, m_item);
	}

	void DoUnexecute() override
	{
		m_items.erase(m_items.begin() + m_position);
	}
private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_item;
	size_t m_position;
};

class CChangeText : public CAbstractCommand
{
public:
	CChangeText(std::string& currentText, const std::string& newText)
		: m_currentText(currentText)
		, m_newText(newText)
	{}

protected:
	void DoExecute() override
	{
		std::swap(m_currentText, m_newText);
	}

	void DoUnexecute() override
	{
		std::swap(m_currentText, m_newText);
	}
private:
	std::string& m_currentText;
	std::string m_newText;
};

class CResizeImage : public CAbstractCommand
{
public:
	CResizeImage(int& currentWidth, const int newWidth, int& currentHeight, const int newHeight)
		: m_currentWidth(currentWidth)
		, m_currentHeight(currentHeight)
	{
		if (newWidth < 1 || newWidth > 10000 || newHeight < 1 || newHeight > 10000)
		{
			throw std::invalid_argument("Wrong size argument. Width and height must be number greater than 1 and less than 10000");
		}
		m_newWidth = newWidth;
		m_newHeight = newHeight;
	}

protected:
	void DoExecute() override
	{
		std::swap(m_currentWidth, m_newWidth);
		std::swap(m_currentHeight, m_newHeight);
	}

	void DoUnexecute() override
	{
		std::swap(m_currentWidth, m_newWidth);
		std::swap(m_currentHeight, m_newHeight);
	}
private:
	int& m_currentWidth;
	int m_newWidth;
	int& m_currentHeight;
	int m_newHeight;
};

class CDeleteDocumentItem : public CAbstractCommand
{
public:
	CDeleteDocumentItem(std::vector<std::shared_ptr<CDocumentItem>>& items, std::shared_ptr<CDocumentItem> item, size_t position)
		: m_items(items)
		, m_item(item)
		, m_position(position)
	{
		if (position > items.size() || position < 0)
		{
			throw std::invalid_argument("Wrong position argument");
		}
	}

	~CDeleteDocumentItem()
	{
		if (IsExecuted() && m_item->GetImage())
		{
			auto path = m_item->GetImage()->GetPath();
			std::filesystem::remove(path);
		}
	}

protected:
	void DoExecute() override
	{
		m_items.erase(m_items.begin() + m_position);
	}

	void DoUnexecute() override
	{
		m_items.emplace(m_items.begin() + m_position, m_item);
	}
private:
	std::vector<std::shared_ptr<CDocumentItem>>& m_items;
	std::shared_ptr<CDocumentItem> m_item;
	size_t m_position;
};