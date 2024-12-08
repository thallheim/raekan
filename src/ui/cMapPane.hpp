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

  void DrawCross(int x, int y, int width, int height, wxDC &dc);
  void setFontData(wxFontData* in);
  void drawStar(int posX, int posY, int radius, wxDC &dc);
  
private:
  wxFontData* m_fData;
  wxBrush* m_activeBrush;
  
  wxDECLARE_EVENT_TABLE();
};
