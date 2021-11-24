#pragma once
#include <memory>
#include <string>
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IImage> const& image);
	CConstDocumentItem(std::shared_ptr<IParagraph> const& paragraph);

	std::shared_ptr<const IImage> GetImage() const;

	std::shared_ptr<const IParagraph> GetParagraph() const;

	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};