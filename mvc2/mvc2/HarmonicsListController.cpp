#include "HarmonicsListController.h"

CHarmonicsListController::CHarmonicsListController(std::shared_ptr<CHarmonicsList> model, CHarmonicsListView& view)
	: m_model(model)
	, m_view(view)
{
}

void CHarmonicsListController::DeleteHarmonic(size_t index)
{
	m_model->DeleteHarmonic(index);
}

void CHarmonicsListController::SetCurrentIndex(size_t index)
{
	m_model->SetCurrentIndex(index);
}

size_t CHarmonicsListController::GetCurrentIndex() const
{
	return m_model->GetCurrentIndex();
}

std::shared_ptr<CHarmonic> CHarmonicsListController::GetCurrentHarmonic() const
{
	return m_model->GetHarmonicAtIndex(m_model->GetCurrentIndex());
}

std::shared_ptr<CHarmonic> CHarmonicsListController::GetLastHarmonic() const
{
	return m_model->GetHarmonicAtIndex(m_model->GetHarmonicsCount() - 1);
}

size_t CHarmonicsListController::GetHarmonicsCount() const
{
	return m_model->GetHarmonicsCount();
}
