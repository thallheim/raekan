#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "wx/event.h"
#include "wx/notebook.h"
#include "wx/fileconf.h"

#include "cLandingPane.hpp"
#include "cPanel_Main.hpp"
#include "cDrawPane.hpp"
#include "cMapPane.hpp"

class cNotebook : public wxNotebook {
public:
  cNotebook(wxWindow* parent, wxFileConfig* config);
  ~cNotebook();

  cLandingPane*  m_landingPane   = nullptr;
  cPanel_Main*   m_mainPanel     = nullptr;
  cDrawPane*     m_drawPane      = nullptr;
  cMapPane*      m_mapPane       = nullptr;

  void OnParentFontChanged(wxCommandEvent& event);
  void OnShowMainPanel(wxCommandEvent& WXUNUSED(event));
  wxFont GetParentFont();

private:
  wxFileConfig* m_config;

  void hideMainTab(wxWindow* parent);
  void disableMainTab(wxWindow* parent);
};
