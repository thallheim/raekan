#pragma once

#include "wx/event.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "../main.hpp"

class cMapPane : public wxPanel {

public: 
  cMapPane(wxWindow* parent, cMain* main);
  ~cMapPane();

  void paintEvent(wxPaintEvent & evt);
  void paintNow();
  void render(wxDC& dc);
private:
  cMain* m_parent;

  wxDECLARE_EVENT_TABLE();
};
