#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "../util/RandGen.hpp"

class cLandingPane : public wxPanel {
public:
  cLandingPane(wxWindow* parent);
  ~cLandingPane();

  wxString m_seedFieldValue;
  
  void OnNewSeed(wxCommandEvent&);
  void OnButtonTwo(wxCommandEvent& event);
  
private:

  wxWindow* m_parent = nullptr;
  cRandGen m_rg;
  wxTextCtrl* m_seedDisplay;
  int m_seed1 = NULL;

};
