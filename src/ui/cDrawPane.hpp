#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/fontdata.h"

class cDrawPane : public wxPanel {
public:
  cDrawPane(wxWindow* parent);
  ~cDrawPane();

  void OnPaint(wxPaintEvent & evt);
  void render(wxDC& dc);

  wxFont GetParentFont(wxWindow* parent);

private:
  wxFontData* m_fData;
  DECLARE_EVENT_TABLE();
};
