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
