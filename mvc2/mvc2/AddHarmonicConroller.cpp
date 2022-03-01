#include "AddHarmonicController.h"

CAddHarmonicController::CAddHarmonicController(std::shared_ptr<CHarmonicsList> model, CAddHarmonicView& view)
	: m_model(model)
	, m_view(view)
{
}

void CAddHarmonicController::AddHarmonic(std::shared_ptr<CHarmonic> harmonic)
{
	m_model->AddHarmonic(harmonic);
}

