#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
#include <memory>
#include "HarmonicsListView.h"
#include "UpdateHarmonicView.h"
#include "TabWindow.h"
#include "wx/wx.h"

class CApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	wxFrame* m_frame;
	CHarmonicsListView* m_harmonicsListView;
	CUpdateHarmonicView* m_updateHarmonicView;
	CTabWindow* m_tabWindow;
};