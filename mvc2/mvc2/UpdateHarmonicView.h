#pragma once
#include "wx/wx.h"
class CUpdateHarmonicController;
#include "UpdateHarmonicController.h"

class CUpdateHarmonicView : public wxPanel
{
public:
    CUpdateHarmonicView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
private:
    void UpdateCurrentHarmonic();
    std::unique_ptr<CUpdateHarmonicController> m_controller;
    wxStaticText* m_amplitudeLabel;
    wxTextCtrl* m_amplitude;
    wxStaticText* m_frequencyLabel;
    wxTextCtrl* m_frequency;
    wxStaticText* m_phaseLabel;
    wxTextCtrl* m_phase;
    wxRadioButton* m_sin;
    wxRadioButton* m_cos;

    void OnAmplitudeChange(wxCommandEvent& event);
    void OnSinChoose(wxCommandEvent& event);
    void OnCosChoose(wxCommandEvent& event);
    void OnFrequencyChange(wxCommandEvent& event);
    void OnPhaseChange(wxCommandEvent& event);
    void ResetFields();
    
    sig::scoped_connection m_currentHarmonicIndexConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
};
