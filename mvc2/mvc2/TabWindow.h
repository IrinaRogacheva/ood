#pragma once

#include "wx/wx.h"
#include <wx/notebook.h>
#include "HarmonicsList.h"
#include "ChartsView.h"
#include "CoordinateTableView.h"

class CTabWindow : public wxNotebook
{
public:
    CTabWindow(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
};
