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

    sig::scoped_connection m_addHarmonicConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
    sig::scoped_connection m_changeCurrentHarmonicConnection;
    sig::scoped_connection m_changeCurrentHarmonicIndexConnection;

    wxListBox* m_harmonicsList = nullptr;
    wxButton* m_addButton = nullptr;
    wxButton* m_deleteButton = nullptr;
    CAddHarmonicView* m_addHarmonicMenu = nullptr;

    void AddHarmonic(std::shared_ptr<CHarmonic> harmonic);
    void DeleteHarmonic(size_t index);
    void UpdateHarmonic(std::shared_ptr<CHarmonic> harmonic, size_t index);

    void OnSelect(wxCommandEvent& event);
    void OnAddHarmonicButtonClick(wxCommandEvent& event);
    void OnDeleteHarmonicButtonClick(wxCommandEvent& event);
};
