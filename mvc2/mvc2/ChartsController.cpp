#include "ChartsController.h"

CChartsController::CChartsController(std::shared_ptr<CHarmonicsList> model, CChartsView& view)
	: m_model(model)
	, m_view(view)
{
}

std::shared_ptr<CHarmonic> CChartsController::GetCurrentHarmonic() const
{
	return m_model->GetHarmonicAtIndex(m_model->GetCurrentIndex());
}

GraphPoints CChartsController::GetGraphPoints() const
{
	return m_model->CalculateGraphPoints();
}

size_t CChartsController::GetHarmonicsCount() const
{
	return m_model->GetHarmonicsCount();
}
