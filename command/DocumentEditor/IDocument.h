#pragma once
#include <memory>
#include <string>
#include "CConstDocumentItem.h"
#include "CDocumentItem.h"
#include <boost/none.hpp>
#include <boost/optional/optional.hpp>

class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) = 0;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images 
	// ��� ������������� ��������������� ������
	virtual std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height, boost::optional<size_t> position = boost::none) = 0;

	// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount()const = 0;

	// ������ � ��������� �����������
	virtual CConstDocumentItem GetItem(size_t index)const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual std::string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const std::string& title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	//virtual void Save(const Path& path)const = 0;

	virtual ~IDocument() = default;
};