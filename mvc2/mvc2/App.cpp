#include "App.h"

wxIMPLEMENT_APP(CApp);

bool CApp::OnInit()
{
    std::shared_ptr<CHarmonicsList> model = std::make_shared<CHarmonicsList>();

    m_frame = new wxFrame(NULL, wxID_ANY, "Chart Drawer", wxPoint(400, 200), wxSize(500, 410));
    m_frame->SetBackgroundColour(*wxWHITE);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    
    wxPanel* panel = new wxPanel(m_frame, wxID_ANY, wxPoint(0, 0), wxSize(500, 1), wxBORDER_SIMPLE);
    sizer->Add(panel, 0, wxEXPAND);

    m_harmonicsListView = new CHarmonicsListView(m_frame, model);
    sizer->Add(m_harmonicsListView, 0, wxLEFT, 15);

    m_tabWindow = new CTabWindow(m_frame, model);
    sizer->Add(m_tabWindow, 1, wxEXPAND|wxALL, 15);
    
    m_frame->SetSizerAndFit(sizer);
    m_frame->Show(true);

    return true;
}
