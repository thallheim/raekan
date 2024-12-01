#pragma once

#include "util/RandGen.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/event.h"
#include <wx/fontdata.h>
#include <wx/notebook.h>

class cMain : public wxFrame {
public:
  cMain();
  ~cMain();

  // Toolbar
  wxToolBar* m_mainToolbar = nullptr;
  wxToolBarToolBase* m_tool1 = nullptr;
  wxToolBarToolBase* m_tool2 = nullptr;
  wxToolBarToolBase* m_tool3 = nullptr;

  // Statusbar
  wxStatusBar* m_mainStatusbar = nullptr;

  // Book
  wxNotebook* m_book = nullptr;

  // Info fields
  wxTextCtrl* m_iField_seed = nullptr;

  // MISC
  wxFont m_selectedFont;
  wxFontData m_selectedFont_data;
  wxFont getSelectedFont();
  
  // Handlers
  void OnFileQ(wxCommandEvent& WXUNUSED(event));
  void OnAbout(wxCommandEvent& WXUNUSED(event));

  void OnNewSeed(wxCommandEvent& event);
  void OnChooseFont(wxCommandEvent& event);
  void TransformStatusBar(wxCommandEvent& WXUNUSED(event));
  void popSB(wxCommandEvent& WXUNUSED(event));
  void SayHi(wxCommandEvent& WXUNUSED(event));

private:
  cRandGen* m_RandGen;
  int rSeed;

  wxDECLARE_EVENT_TABLE();
};

