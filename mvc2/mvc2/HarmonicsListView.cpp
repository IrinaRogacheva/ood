#include "HarmonicsListView.h"
#include <algorithm>
#include "ConvertUtils.h"

CHarmonicsListView::CHarmonicsListView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
	: wxPanel(parent, wxID_ANY, wxPoint(15, 20), wxSize(490, 155))
	, m_model(model)
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
		AddListboxItem(m_model->GetHarmonicAtIndex(m_model->GetHarmonicsCount() - 1));
		m_harmonicsList->SetSelection(m_model->GetHarmonicsCount() - 1);
		UpdateCurrentHarmonicPanel();
		m_changeCurrentHarmonicConnection = m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->DoOnHarmonicChanged([=] {
			UpdateListboxItem(m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection()), m_harmonicsList->GetSelection());
		});
	});
	AddListboxItem(m_model->GetHarmonicAtIndex(m_model->GetHarmonicsCount() - 1));
	m_harmonicsList->SetSelection(0);

	m_changeCurrentHarmonicConnection = m_model->GetHarmonicAtIndex(m_model->GetHarmonicsCount() - 1)->DoOnHarmonicChanged([=] {
		UpdateListboxItem(m_model->GetHarmonicAtIndex(0), 0);
	});

	m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
		DeleteListboxItem(m_harmonicsList->GetSelection());
		UpdateCurrentHarmonicPanel();
	});

	wxPanel* updateHarmonicPanel = new wxPanel(this, wxID_ANY, wxPoint(260, 10), wxSize(210, 145), wxBORDER_SIMPLE);
	wxString* str = new wxString("");
	m_amplitudeLabel = new wxStaticText(updateHarmonicPanel, wxID_ANY, wxString("Amplitude:"), wxPoint(10, 12));
	m_amplitude = new wxTextCtrl(updateHarmonicPanel, wxID_ANY, wxString("1"), wxPoint(110, 10), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, str));
	m_amplitude->Bind(wxEVT_TEXT, &CHarmonicsListView::OnAmplitudeChange, this);

	m_sin = new wxRadioButton(updateHarmonicPanel, wxID_ANY, wxString("Sin"), wxPoint(10, 45));
	m_cos = new wxRadioButton(updateHarmonicPanel, wxID_ANY, wxString("Cos"), wxPoint(100, 45));
	m_sin->SetValue(true);
	m_sin->Bind(wxEVT_RADIOBUTTON, &CHarmonicsListView::OnSinChoose, this);
	m_cos->Bind(wxEVT_RADIOBUTTON, &CHarmonicsListView::OnCosChoose, this);

	m_frequencyLabel = new wxStaticText(updateHarmonicPanel, wxID_ANY, wxString("Frequency:"), wxPoint(10, 77));
	m_frequency = new wxTextCtrl(updateHarmonicPanel, wxID_ANY, wxString("1"), wxPoint(110, 75), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, str));
	m_frequency->Bind(wxEVT_TEXT, &CHarmonicsListView::OnFrequencyChange, this);

	m_phaseLabel = new wxStaticText(updateHarmonicPanel, wxID_ANY, wxString("Phase:"), wxPoint(10, 112));
	m_phase = new wxTextCtrl(updateHarmonicPanel, wxID_ANY, wxString("0"), wxPoint(110, 110), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, str));
	m_phase->Bind(wxEVT_TEXT, &CHarmonicsListView::OnPhaseChange, this);

	delete str;
}

CHarmonicsListView::~CHarmonicsListView()
{
	m_addHarmonicMenu->Destroy();
}

void CHarmonicsListView::AddListboxItem(std::shared_ptr<CHarmonic> harmonic)
{
	m_harmonicsList->AppendString(ConvertDoubleToString(harmonic->GetAmplitude()) + "*"
		+ (harmonic->GetFunctionType() == HarmonicFunctionType::SIN ? "sin" : "cos")
		+ "(" + ConvertDoubleToString(harmonic->GetFrequency()) + "*x+" + ConvertDoubleToString(harmonic->GetPhase()) + ")");
}

void CHarmonicsListView::DeleteListboxItem(size_t index)
{		
	bool isFirstItemDeleted = (m_model->GetHarmonicsCount() == 1);
	
	if(index > 0)
	{
		m_harmonicsList->SetSelection(index - 1);
	}

	m_harmonicsList->Delete(index);

	if (isFirstItemDeleted)
	{
		m_harmonicsList->SetSelection(0);
	}
}

void CHarmonicsListView::UpdateListboxItem(std::shared_ptr<CHarmonic> harmonic, size_t index)
{
	m_harmonicsList->SetString(index, ConvertDoubleToString(harmonic->GetAmplitude()) + "*"
		+ (harmonic->GetFunctionType() == HarmonicFunctionType::SIN ? "sin" : "cos")
		+ "(" + ConvertDoubleToString(harmonic->GetFrequency()) + "*x+" + ConvertDoubleToString(harmonic->GetPhase()) + ")");
}

void CHarmonicsListView::OnSelect(wxCommandEvent& event)
{
	UpdateCurrentHarmonicPanel();
	m_changeCurrentHarmonicConnection = m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->DoOnHarmonicChanged([=] {
		UpdateListboxItem(m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection()), m_harmonicsList->GetSelection());
	});
}

void CHarmonicsListView::OnAddHarmonicButtonClick(wxCommandEvent& event)
{
	m_addHarmonicMenu->ShowModal();
}

void CHarmonicsListView::OnDeleteHarmonicButtonClick(wxCommandEvent& event)
{
	if (m_model->GetHarmonicsCount() > 0)
	{
		m_controller->DeleteHarmonic(m_harmonicsList->GetSelection());
	}
	else
	{
		wxMessageBox(wxT("There is no garmonics to delete"), wxT("Add harmonic at first"), wxICON_INFORMATION);
	}
}

void CHarmonicsListView::OnAmplitudeChange(wxCommandEvent& event)
{
	if (m_amplitude->GetValue() != "" && m_amplitude->Validate())
	{
		m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->SetAmplitude(ConvertWxStringToDouble(m_amplitude->GetValue()));
	}
}

void CHarmonicsListView::OnSinChoose(wxCommandEvent& event)
{
	if (m_sin->GetValue())
	{
		m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->SetFunctionType(HarmonicFunctionType::SIN);
	}
}

void CHarmonicsListView::OnCosChoose(wxCommandEvent& event)
{
	if (m_cos->GetValue())
	{
		m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->SetFunctionType(HarmonicFunctionType::COS);
	}
}

void CHarmonicsListView::OnFrequencyChange(wxCommandEvent& event)
{
	if (m_frequency->GetValue() != "" && m_frequency->Validate())
	{
		m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->SetFrequency(ConvertWxStringToDouble(m_frequency->GetValue()));
	}
}

void CHarmonicsListView::OnPhaseChange(wxCommandEvent& event)
{
	if (m_phase->GetValue() != "" && m_phase->Validate())
	{
		m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection())->SetPhase(ConvertWxStringToDouble(m_phase->GetValue()));
	}
}

void CHarmonicsListView::UpdateCurrentHarmonicPanel()
{
	if (m_model->GetHarmonicsCount() == 0)
	{
		ResetFields();
		return;
	}
	std::shared_ptr<CHarmonic> harmonic = m_model->GetHarmonicAtIndex(m_harmonicsList->GetSelection());
	m_amplitude->SetValue(ConvertDoubleToString(harmonic->GetAmplitude()));
	m_frequency->SetValue(ConvertDoubleToString(harmonic->GetFrequency()));
	m_phase->SetValue(ConvertDoubleToString(harmonic->GetPhase()));
	if (harmonic->GetFunctionType() == HarmonicFunctionType::SIN)
	{
		m_sin->SetValue(true);
	}
	else
	{
		m_cos->SetValue(true);
	}
}

void CHarmonicsListView::ResetFields()
{
	m_amplitude->SetValue("");
	m_frequency->SetValue("");
	m_phase->SetValue("");
	m_sin->SetValue(false);
	m_cos->SetValue(false);
}

