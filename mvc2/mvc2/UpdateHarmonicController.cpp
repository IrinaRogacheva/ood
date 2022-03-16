#include "UpdateHarmonicController.h"

CUpdateHarmonicController::CUpdateHarmonicController(std::shared_ptr<CHarmonicsList> model, CUpdateHarmonicView& view)
	: m_model(model)
	, m_view(view)
{
}

std::shared_ptr<CHarmonic> CUpdateHarmonicController::GetCurrentHarmonic()
{
	return m_model->GetHarmonicAtIndex(m_model->GetCurrentIndex());
}

size_t CUpdateHarmonicController::GetHarmonicsCount() const
{
	return m_model->GetHarmonicsCount();
}
