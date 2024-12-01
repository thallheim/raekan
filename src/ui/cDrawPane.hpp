#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "../main.hpp"

class cDrawPane : public wxWindow {
public:
  cDrawPane(wxWindow* parent, cMain* main);
  ~cDrawPane();

  void paintEvent(wxPaintEvent & evt);
  void paintNow();

  void OnParentFontChanged(wxCommandEvent& event);
    
  void render(wxDC& dc);
    
private:
  cMain* m_parent;

  DECLARE_EVENT_TABLE();
};
