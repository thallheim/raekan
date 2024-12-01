#include "wx/log.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "wx/event.h"
#include "wx/gdicmn.h"

#include "cDrawPane.hpp"
#include "../main.hpp"

wxBEGIN_EVENT_TABLE(cDrawPane, wxPanel)
    EVT_PAINT(cDrawPane::paintEvent)
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

cDrawPane::cDrawPane(wxWindow* parent, cMain* main)
: wxWindow(parent, -1), m_parent(main) {
  SetBackgroundColour(wxColour(105, 130, 153, 255));


  wxBoxSizer* drawPaneSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(drawPaneSizer);

}

cDrawPane::~cDrawPane() {}

void cDrawPane::paintEvent(wxPaintEvent & evt) {
  wxPaintDC dc(this);
  render(dc);
}

void cDrawPane::render(wxDC& dc) {
  // draw some text
  dc.SetTextBackground(*wxLIGHT_GREY);
  dc.SetTextForeground(*wxGREEN);
 
  wxFont font = m_parent->getSelectedFont();
  if (font.IsOk()) {
    dc.SetFont(font);
    std::string fontNameLabel = "Font: \n\t";
    fontNameLabel.append(font.GetFaceName());
    dc.DrawText(fontNameLabel, 5, 5);
  } else {
    // Fallback to default font if no font was selected
    wxFont defaultFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc.SetFont(defaultFont);
    dc.DrawText("No font selected :<", 5, 5);
  }

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

void cDrawPane::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

void cDrawPane::OnParentFontChanged(wxCommandEvent& event) {
    // Force repaint when the font changes
    Refresh();
    // wxLogMessage("Font changed.");
    event.Skip(); // Let the event propagate upwards
}
