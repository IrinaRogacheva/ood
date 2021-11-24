#pragma once
#include "IParagraph.h"
#include "CHistory.h"
#include <memory>
#include <string>

class CParagraph : public IParagraph
{
public:
	std::string GetText() const;
	void SetText(const std::string& text);
	CParagraph(CHistory& history, std::string const& text);
private:
	CHistory& m_history;
	std::string m_text;
};