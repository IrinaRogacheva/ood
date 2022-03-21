#pragma once

#include "wx/wx.h"
#include "HarmonicsList.h"
#include "AddHarmonicView.h"
class CHarmonicsListController;
#include "HarmonicsListController.h"

class CHarmonicsListView : public wxPanel
{
public:
    CHarmonicsListView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
    ~CHarmonicsListView();
private:
    std::unique_ptr<CHarmonicsListController> m_controller;
    std::shared_ptr<CHarmonicsList> m_model;

    sig::scoped_connection m_addHarmonicConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
    sig::scoped_connection m_changeCurrentHarmonicConnection;

    wxListBox* m_harmonicsList = nullptr;
    wxButton* m_addButton = nullptr;
    wxButton* m_deleteButton = nullptr;
    CAddHarmonicView* m_addHarmonicMenu = nullptr;

    void AddListboxItem(std::shared_ptr<CHarmonic> harmonic);
    void DeleteListboxItem(size_t index);
    void UpdateListboxItem(std::shared_ptr<CHarmonic> harmonic, size_t index);

    void UpdateCurrentHarmonicPanel();
    void ResetFields();

    void OnSelect(wxCommandEvent& event);
    void OnAddHarmonicButtonClick(wxCommandEvent& event);
    void OnDeleteHarmonicButtonClick(wxCommandEvent& event);

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
};
