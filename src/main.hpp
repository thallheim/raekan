#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include "SQLiteCpp/Database.h"

#include "ui/cNotebook.hpp"
#include "util/RandGen.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/event.h"
#include <wx/fontdata.h>
#include <wx/notebook.h>
#include "wx/config.h"
#include "wx/fileconf.h"

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
  cNotebook* m_book = nullptr;

  // Info fields
  wxTextCtrl* m_iField_seed = nullptr;

  // MISC
  wxFont m_selectedFont;
  wxFontData m_selectedFont_data;
  wxFont getSelectedFont();
  
  // Handlers
  void OnFileQ(wxCommandEvent& WXUNUSED(event));
  void OnAbout(wxCommandEvent& WXUNUSED(event));
  void OnChooseFont(wxCommandEvent& event);
  void OnNewSeed(wxCommandEvent& event);
   
private:
  SQLite::Database* m_db;
  cRandGen* m_RandGen;
  int rSeed;
  wxFileConfig* m_config;

  bool initDB();

  wxDECLARE_EVENT_TABLE();
};

