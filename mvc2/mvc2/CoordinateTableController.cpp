#include "CoordinateTableController.h"

CCoordinateTableController::CCoordinateTableController(std::shared_ptr<CHarmonicsList> model, CCoordinateTableView& view)
	: m_model(model)
	, m_view(view)
{
}

std::shared_ptr<CHarmonic> CCoordinateTableController::GetCurrentHarmonic() const
{
	return m_model->GetHarmonicAtIndex(m_model->GetCurrentIndex());
}

GraphPoints CCoordinateTableController::GetGraphPoints() const
{
	return m_model->CalculateGraphPoints();
}

size_t CCoordinateTableController::GetHarmonicsCount() const
{
	return m_model->GetHarmonicsCount();
}
