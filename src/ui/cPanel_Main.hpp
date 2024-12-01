#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/msw/panel.h"

#include "../util/RandGen.hpp"

class cPanel_Main : public wxPanel {
public:
  cPanel_Main(wxWindow* parent);
  ~cPanel_Main();

  void OnNewSeed(wxCommandEvent&);
  void OnButtonTwo(wxCommandEvent& WXUNUSED(event));
  wxString m_seedFieldValue;
  

private:

  cRandGen m_rg;
  wxTextCtrl* m_seedDisplay;
  int m_seed1 = NULL;
  
  // TODO: Sort event handler out again
  wxDECLARE_EVENT_TABLE();

};
