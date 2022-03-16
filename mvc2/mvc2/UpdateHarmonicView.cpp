#include "UpdateHarmonicView.h"
#include "ConvertUtils.h"

CUpdateHarmonicView::CUpdateHarmonicView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(210, 145), wxBORDER_SIMPLE)
{
    SetBackgroundColour(*wxWHITE);

    m_controller = std::make_unique<CUpdateHarmonicController>(model, *this);
    
    wxString* str = new wxString("");
    m_amplitudeLabel = new wxStaticText(this, wxID_ANY, wxString("Amplitude:"), wxPoint(10, 12));
    m_amplitude = new wxTextCtrl(this, wxID_ANY, wxString("1"), wxPoint(110, 10), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, str));
    m_amplitude->Bind(wxEVT_TEXT, &CUpdateHarmonicView::OnAmplitudeChange, this);

    m_sin = new wxRadioButton(this, wxID_ANY, wxString("Sin"), wxPoint(10, 45));
    m_cos = new wxRadioButton(this, wxID_ANY, wxString("Cos"), wxPoint(100, 45));
    m_sin->SetValue(true);
    m_sin->Bind(wxEVT_RADIOBUTTON, &CUpdateHarmonicView::OnSinChoose, this);
    m_cos->Bind(wxEVT_RADIOBUTTON, &CUpdateHarmonicView::OnCosChoose, this);

    m_frequencyLabel = new wxStaticText(this, wxID_ANY, wxString("Frequency:"), wxPoint(10, 77));
    m_frequency = new wxTextCtrl(this, wxID_ANY, wxString("1"), wxPoint(110, 75), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, str));
    m_frequency->Bind(wxEVT_TEXT, &CUpdateHarmonicView::OnFrequencyChange, this);

    m_phaseLabel = new wxStaticText(this, wxID_ANY, wxString("Phase:"), wxPoint(10, 112));
    m_phase = new wxTextCtrl(this, wxID_ANY, wxString("0"), wxPoint(110, 110), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, str));
    m_phase->Bind(wxEVT_TEXT, &CUpdateHarmonicView::OnPhaseChange, this);

    m_currentHarmonicIndexConnection = model->DoOnCurrentIndexChanged([=] {
        UpdateCurrentHarmonic();
    });

    m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
        ResetFields();
    });

    delete str;
}

void CUpdateHarmonicView::UpdateCurrentHarmonic()
{
    std::shared_ptr<CHarmonic> harmonic = m_controller->GetCurrentHarmonic();
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

void CUpdateHarmonicView::ResetFields()
{
    m_amplitude->SetValue("");
    m_frequency->SetValue("");
    m_phase->SetValue("");
    m_sin->SetValue(false);
    m_cos->SetValue(false);
}

void CUpdateHarmonicView::OnAmplitudeChange(wxCommandEvent& event)
{
    if (m_amplitude->GetValue() != "" && m_amplitude->Validate())
    {
        m_controller->GetCurrentHarmonic()->SetAmplitude(ConvertWxStringToDouble(m_amplitude->GetValue()));
    }
}

void CUpdateHarmonicView::OnSinChoose(wxCommandEvent& event)
{
    if (m_sin->GetValue())
    {
        m_controller->GetCurrentHarmonic()->SetFunctionType(HarmonicFunctionType::SIN);
    }
}

void CUpdateHarmonicView::OnCosChoose(wxCommandEvent& event)
{
    if (m_cos->GetValue())
    {
        m_controller->GetCurrentHarmonic()->SetFunctionType(HarmonicFunctionType::COS);
    }
}

void CUpdateHarmonicView::OnFrequencyChange(wxCommandEvent& event)
{
    if (m_frequency->GetValue() != "" && m_frequency->Validate())
    {
        m_controller->GetCurrentHarmonic()->SetFrequency(ConvertWxStringToDouble(m_frequency->GetValue()));
    }
}

void CUpdateHarmonicView::OnPhaseChange(wxCommandEvent& event)
{
    if (m_phase->GetValue() != "" && m_phase->Validate())
    {
        m_controller->GetCurrentHarmonic()->SetPhase(ConvertWxStringToDouble(m_phase->GetValue()));
    }
}
