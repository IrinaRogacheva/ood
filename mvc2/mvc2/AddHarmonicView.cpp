#include "AddHarmonicView.h"
#include "Harmonic.h"
#include "ConvertUtils.h"

CAddHarmonicView::CAddHarmonicView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
    : wxDialog(parent, wxID_ANY, "Add new harmonic", wxPoint(540, 280), wxSize(220, 255))
{
    SetBackgroundColour(*wxWHITE);
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(250, 1), wxBORDER_SIMPLE);

    m_controller = std::make_unique<CAddHarmonicController>(model, *this);

    m_amplitudeLabel = new wxStaticText(this, wxID_ANY, wxString("Amplitude:"), wxPoint(10, 12));
    m_amplitude = new wxTextCtrl(this, wxID_ANY, wxString("1"), wxPoint(110, 10), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, m_amplitudeValue));
    m_amplitude->Bind(wxEVT_TEXT, &CAddHarmonicView::UpdateEquation, this);

    m_sin = new wxRadioButton(this, wxID_ANY, wxString("Sin"), wxPoint(10, 45));
    m_cos = new wxRadioButton(this, wxID_ANY, wxString("Cos"), wxPoint(100, 45));
    m_sin->SetValue(true);
    m_sin->Bind(wxEVT_RADIOBUTTON, &CAddHarmonicView::UpdateEquation, this);
    m_cos->Bind(wxEVT_RADIOBUTTON, &CAddHarmonicView::UpdateEquation, this);

    m_frequencyLabel = new wxStaticText(this, wxID_ANY, wxString("Frequency:"), wxPoint(10, 77));
    m_frequency = new wxTextCtrl(this, wxID_ANY, wxString("1"), wxPoint(110, 75), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, m_frequencyValue));
    m_frequency->Bind(wxEVT_TEXT, &CAddHarmonicView::UpdateEquation, this);

    m_phaseLabel = new wxStaticText(this, wxID_ANY, wxString("Phase:"), wxPoint(10, 112));
    m_phase = new wxTextCtrl(this, wxID_ANY, wxString("0"), wxPoint(110, 110), wxSize(80, 20), 0, wxTextValidator(wxFILTER_NUMERIC, m_phaseValue));
    m_phase->Bind(wxEVT_TEXT, &CAddHarmonicView::UpdateEquation, this);

    m_equation = new wxStaticText(this, wxID_ANY, wxString("1*Sin(1*x+0)"), wxPoint(10, 150));

    m_okButton = new wxButton(this, wxID_ANY, "OK", wxPoint(40, 180), wxSize(70, 22));
    m_okButton->Bind(wxEVT_BUTTON, &CAddHarmonicView::OnOk, this);

    m_cancelButton = new wxButton(this, wxID_ANY, "Cancel", wxPoint(120, 180), wxSize(70, 22));
    m_cancelButton->Bind(wxEVT_BUTTON, &CAddHarmonicView::OnCancel, this);
}

CAddHarmonicView::~CAddHarmonicView()
{
    delete m_amplitudeValue;
    delete m_frequencyValue;
    delete m_phaseValue;
}

void CAddHarmonicView::UpdateEquation(wxCommandEvent& event)
{
    if (m_amplitude->GetValue() != "" && m_frequency->GetValue() != "" && m_phase->GetValue() != "" 
        && m_amplitude->Validate() && m_frequency->Validate() && m_phase->Validate())
    {
        m_equation->SetLabel(m_amplitude->GetValue() + "*" + (m_sin->GetValue() ? "Sin" : "Cos") + "(" + m_frequency->GetValue() + "*x+" + m_phase->GetValue() + ")");
    }
}

void CAddHarmonicView::ResetFields()
{
    m_amplitude->SetValue("1");
    m_frequency->SetValue("1");
    m_phase->SetValue("0");
    m_sin->SetValue(true);
}

void CAddHarmonicView::OnCancel(wxCommandEvent& event)
{
    EndModal(GetReturnCode());
    ResetFields();
}

void CAddHarmonicView::OnOk(wxCommandEvent& event)
{
    if (m_amplitude->GetValue() != "" && m_frequency->GetValue() != "" && m_phase->GetValue() != ""
        && m_amplitude->Validate() && m_frequency->Validate() && m_phase->Validate())
    {
        m_controller->AddHarmonic(std::make_shared<CHarmonic>(ConvertWxStringToDouble(m_amplitude->GetValue()),
            (m_sin->GetValue() ? HarmonicFunctionType::SIN : HarmonicFunctionType::COS),
            ConvertWxStringToDouble(m_frequency->GetValue()),
            ConvertWxStringToDouble(m_phase->GetValue()))
        );
        EndModal(GetReturnCode());
        ResetFields();
    }
    else
    {
        wxMessageBox("Invalid input", "Fill in all the fields", wxOK | wxICON_INFORMATION);
    }
}
