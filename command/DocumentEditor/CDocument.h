#pragma once
#include "IDocument.h"
#include "CHistory.h"
#include <memory>

class CDocument : public IDocument
{
public:
	
	void SetTitle(const std::string& title) override;
	
	std::string GetTitle() const override;
	
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none);
	
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height, boost::optional<size_t> position = boost::none);
		
	size_t GetItemsCount() const;
	
	CConstDocumentItem GetItem(size_t index) const;
	CDocumentItem GetItem(size_t index);
	
	void DeleteItem(size_t index);
	
	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;
private:
	std::string m_title;
	std::vector<std::shared_ptr<CDocumentItem>> m_items;
	CHistory m_history;
};