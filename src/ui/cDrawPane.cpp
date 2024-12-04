#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/font.h"
#include "wx/fontdata.h"
#include "wx/log.h"
#include "wx/event.h"
#include "wx/gdicmn.h"

#include "cDrawPane.hpp"

wxBEGIN_EVENT_TABLE(cDrawPane, wxPanel)
    EVT_PAINT(cDrawPane::OnPaint)
    // some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */
  /*
    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
  */

wxEND_EVENT_TABLE()

cDrawPane::cDrawPane(wxWindow* parent)
: wxPanel(parent, -1) {
  SetBackgroundColour(wxColour(105, 130, 153, 255));

  wxBoxSizer* drawPaneSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(drawPaneSizer);

  // Bind(FONT_CHANGE_EVENT, &cDrawPane::OnParentFontChanged, this);
}

cDrawPane::~cDrawPane() {}

void cDrawPane::OnPaint(wxPaintEvent & evt) {
  wxPaintDC dc(this);
  render(dc);
}

void cDrawPane::render(wxDC& dc) {
  // draw some text
  dc.SetTextBackground(*wxLIGHT_GREY);
  dc.SetTextForeground(wxColour(0,50,200,255));

  std::string fontNameLabel = "Font:";
  wxFont font = m_font;
  
  if (font.IsOk()) {
    dc.SetFont(font);
    fontNameLabel.append("\n\t" + font.GetFaceName());
    // wxString faceName = font.GetFaceName();
    // dc.DrawText(faceName, 5, 15);
  } 
  dc.DrawText(fontNameLabel, 5, 5);

  // draw a circle
  dc.SetBrush(*wxGREEN_BRUSH); // green filling
  dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
  dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

  // draw a rectangle
  dc.SetBrush(*wxBLUE_BRUSH); // blue filling
  dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
  dc.DrawRectangle( 300, 100, 400, 200 );

  // draw a line
  dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
  dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle
}

wxFont cDrawPane::GetParentFont(wxWindow* parent) {
  wxFont parentFont = parent->GetFont();
  return parentFont.IsOk() ? parentFont :
    wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);
}
