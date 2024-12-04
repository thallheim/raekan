#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "wx/event.h"
#include "wx/notebook.h"

#include "cPanel_Main.hpp"
#include "cDrawPane.hpp"
#include "cMapPane.hpp"

class cNotebook : public wxNotebook {
public:
  cNotebook(wxWindow* parent);
  ~cNotebook();

  cPanel_Main* m_panel_Main = nullptr;
  cDrawPane*   m_drawPane   = nullptr;
  cMapPane*    m_mapPane    = nullptr;

  void OnParentFontChanged(wxCommandEvent& event);
  wxFont GetParentFont();

private:

};
