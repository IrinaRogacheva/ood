#include "HarmonicsListView.h"
#include <algorithm>
#include "ConvertUtils.h"

CHarmonicsListView::CHarmonicsListView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(190, 155))
{
	m_controller = std::make_unique<CHarmonicsListController>(model, *this);

	wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(0, 10), wxSize(190, 26), wxBORDER_SIMPLE);
	wxStaticText* title = new wxStaticText(panel, wxID_ANY, wxString("Harmonics"), wxPoint(3, 4));
	panel->SetBackgroundColour(*wxWHITE);

	m_harmonicsList = new wxListBox(this, wxID_ANY, wxPoint(0, 35), wxSize(190, 70));
	m_harmonicsList->Bind(wxEVT_LISTBOX, &CHarmonicsListView::OnSelect, this);

	m_addButton = new wxButton(this, wxID_ANY, "Add new", wxPoint(0, 130), wxSize(75, 20));
	m_addButton->Bind(wxEVT_BUTTON, &CHarmonicsListView::OnAddHarmonicButtonClick, this);

	m_deleteButton = new wxButton(this, wxID_ANY, "Delete selected", wxPoint(90, 130), wxSize(100, 20));
	m_deleteButton->Bind(wxEVT_BUTTON, &CHarmonicsListView::OnDeleteHarmonicButtonClick, this);

	m_addHarmonicMenu = new CAddHarmonicView(parent, model);
	
	m_addHarmonicConnection = model->DoOnHarmonicAdded([=] {
		AddHarmonic(m_controller->GetLastHarmonic());
	});
	AddHarmonic(m_controller->GetLastHarmonic());
	m_harmonicsList->SetSelection(0);

	m_changeCurrentHarmonicConnection = m_controller->GetLastHarmonic()->DoOnHarmonicChanged([=] {
		UpdateHarmonic(m_controller->GetCurrentHarmonic(), m_controller->GetCurrentIndex());
	});

	m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
		DeleteHarmonic(m_controller->GetCurrentIndex());
	});

	m_changeCurrentHarmonicIndexConnection = model->DoOnCurrentIndexChanged([=] {
		m_harmonicsList->SetSelection(m_controller->GetCurrentIndex());
		m_changeCurrentHarmonicConnection = m_controller->GetCurrentHarmonic()->DoOnHarmonicChanged([=] {
			UpdateHarmonic(m_controller->GetCurrentHarmonic(), m_controller->GetCurrentIndex());
		});
	});
}

CHarmonicsListView::~CHarmonicsListView()
{
	m_addHarmonicMenu->Destroy();
}

void CHarmonicsListView::AddHarmonic(std::shared_ptr<CHarmonic> harmonic)
{
	m_harmonicsList->AppendString(ConvertDoubleToString(harmonic->GetAmplitude()) + "*"
		+ (harmonic->GetFunctionType() == HarmonicFunctionType::SIN ? "sin" : "cos")
		+ "(" + ConvertDoubleToString(harmonic->GetFrequency()) + "*x+" + ConvertDoubleToString(harmonic->GetPhase()) + ")");
}

void CHarmonicsListView::DeleteHarmonic(size_t index)
{		
	m_harmonicsList->Delete(index);
}

void CHarmonicsListView::UpdateHarmonic(std::shared_ptr<CHarmonic> harmonic, size_t index)
{
	m_harmonicsList->SetString(index, ConvertDoubleToString(harmonic->GetAmplitude()) + "*"
		+ (harmonic->GetFunctionType() == HarmonicFunctionType::SIN ? "sin" : "cos")
		+ "(" + ConvertDoubleToString(harmonic->GetFrequency()) + "*x+" + ConvertDoubleToString(harmonic->GetPhase()) + ")");
}

void CHarmonicsListView::OnSelect(wxCommandEvent& event)
{
	m_controller->SetCurrentIndex(m_harmonicsList->GetSelection());
}

void CHarmonicsListView::OnAddHarmonicButtonClick(wxCommandEvent& event)
{
	m_addHarmonicMenu->ShowModal();
}

void CHarmonicsListView::OnDeleteHarmonicButtonClick(wxCommandEvent& event)
{
	if (m_controller->GetHarmonicsCount() > 0)
	{
		m_controller->DeleteHarmonic(m_harmonicsList->GetSelection());
	}
	else
	{
		wxMessageBox(wxT("There is no garmonics to delete"), wxT("Add harmonic at first"), wxICON_INFORMATION);
	}
}

