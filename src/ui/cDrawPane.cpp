#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
#include "wx/brush.h"
#include "wx/event.h"
#include "wx/font.h"
#include "wx/fontdata.h"
#include "wx/gdicmn.h"
#include "wx/log.h"

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
  // dc.SetTextBackground(wxColour(15,65,112,255));
  dc.SetTextBackground(*wxLIGHT_GREY);
  dc.SetBackgroundMode(wxBRUSHSTYLE_SOLID);
  // dc.SetTextForeground(wxColour(255,140,0,255));
  dc.SetTextForeground(wxColour(15,65,112,255));

  std::string fontNameLabel = "Font: ";
  wxFont font = m_font;
  
  if (font.IsOk()) {
    dc.SetFont(font);
    fontNameLabel.append(font.GetFaceName());
    // wxString faceName = font.GetFaceName();
    // dc.DrawText(faceName, 5, 15);
  } 
  dc.DrawText(fontNameLabel, 5, 5);
  dc.SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);

  // draw a circle
  wxBrush bCircle;
  bCircle.SetColour(0,200,35);
  dc.SetBrush(bCircle);
  wxPen pCircle;
  pCircle.SetColour(255,0,0);
  pCircle.SetWidth(3);
  dc.SetPen( wxPen(pCircle));
  dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

  // draw a rectangle
  wxBrush bRect;
  bRect.SetColour(80,80,80);
  dc.SetBrush(bRect);
  dc.SetPen( wxPen( wxColor(255,175,175), 10)); // 10-pixels-thick pink outline
  dc.DrawRectangle( 300, 100, 400, 200 );

  // draw a line
  dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
  dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle

  auto ogBrush = dc.GetBrush();
  auto ogPen = dc.GetPen();
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.SetPen(*wxWHITE_PEN);
  dc.DrawArc(20,20,100,100,50,50);

  dc.SetPen(ogPen);
  dc.SetBrush(ogBrush);

}

wxFont cDrawPane::GetParentFont(wxWindow* parent) {
  wxFont parentFont = parent->GetFont();
  return parentFont.IsOk() ? parentFont :
    wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);
}
