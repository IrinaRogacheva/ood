#include "App.h"

wxIMPLEMENT_APP(CApp);

bool CApp::OnInit()
{
    std::shared_ptr<CHarmonicsList> model = std::make_shared<CHarmonicsList>();

    m_frame = new wxFrame(NULL, wxID_ANY, "Chart Drawer", wxPoint(400, 200), wxSize(500, 410));
    m_frame->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* commonSizer = new wxBoxSizer(wxVERTICAL);
    
    wxPanel* panel = new wxPanel(m_frame, wxID_ANY, wxPoint(0, 0), wxSize(500, 1), wxBORDER_SIMPLE);
    commonSizer->Add(panel, 0, wxEXPAND);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    m_harmonicsListView = new CHarmonicsListView(m_frame, model);
    topSizer->Add(m_harmonicsListView, 1, wxRIGHT, 65);

    m_updateHarmonicView = new CUpdateHarmonicView(m_frame, model);
    topSizer->Add(m_updateHarmonicView, 0, wxTOP, 10);

    commonSizer->Add(topSizer, 0, wxALL, 15);

    m_tabWindow = new CTabWindow(m_frame, model);
    commonSizer->Add(m_tabWindow, 1, wxEXPAND|wxALL, 15);
    
    m_frame->SetSizerAndFit(commonSizer);
    m_frame->Show(true);

    return true;
}
