#pragma once
#include "wx/wx.h"
class CAddHarmonicController;
#include "AddHarmonicController.h"

class CAddHarmonicView : public wxDialog
{
public:
    CAddHarmonicView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
    ~CAddHarmonicView();
private:
    void UpdateEquation(wxCommandEvent& event);
    void ResetFields();
    void OnCancel(wxCommandEvent& event);
    void OnOk(wxCommandEvent& event);

    std::unique_ptr<CAddHarmonicController> m_controller;

    wxStaticText* m_amplitudeLabel;
    wxString* m_amplitudeValue = new wxString("1");
    wxTextCtrl* m_amplitude;
    wxStaticText* m_frequencyLabel;
    wxString* m_frequencyValue = new wxString("1");
    wxTextCtrl* m_frequency;
    wxStaticText* m_phaseLabel;
    wxString* m_phaseValue = new wxString("0");
    wxTextCtrl* m_phase;
    wxStaticText* m_equation;
    wxRadioButton* m_sin;
    wxRadioButton* m_cos;

    wxButton* m_okButton;
    wxButton* m_cancelButton;
};
