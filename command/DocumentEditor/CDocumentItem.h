#pragma once
#include "CConstDocumentItem.h"
#include <memory>

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IParagraph> const& paragraph);

	CDocumentItem(std::shared_ptr<IImage> const& image);

	std::shared_ptr<IImage> GetImage();

	std::shared_ptr<IParagraph> GetParagraph();
};