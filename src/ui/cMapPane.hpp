#pragma once

#include "wx/event.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/fontdata.h"

class cMapPane : public wxPanel {

public: 
  cMapPane(wxWindow* parent);
  ~cMapPane();

  void OnPaint(wxPaintEvent & evt);
  void render(wxDC& dc);

  void DrawStar(int x, int y, int width, int height, wxDC &dc);
  void setFontData(wxFontData* in);
private:
  wxFontData* m_fData;
  wxDECLARE_EVENT_TABLE();
};
