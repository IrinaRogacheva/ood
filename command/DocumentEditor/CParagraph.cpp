#include "CParagraph.h"
#include "Commands.h"

CParagraph::CParagraph(CHistory& history, std::string const& text)
    : m_history(history)
    , m_text(text)
{
}

std::string CParagraph::GetText() const
{
    return m_text;
}

void CParagraph::SetText(const std::string& text)
{
    m_history.AddAndExecuteCommand(std::make_unique<CChangeText>(m_text, text));
}
