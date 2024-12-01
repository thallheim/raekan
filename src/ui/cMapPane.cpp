#include <wx/log.h>
#include <wx/event.h>

#include "cMapPane.hpp"
#include "wx/gdicmn.h"
#include "wx/msw/window.h"
#include "wx/sizer.h"

wxBEGIN_EVENT_TABLE(cMapPane, wxPanel)
    EVT_PAINT(cMapPane::paintEvent)
wxEND_EVENT_TABLE()


cMapPane::cMapPane(wxWindow* parent, cMain* main)
: wxPanel(parent, -1), m_parent(main) {
  SetBackgroundColour(*wxBLACK);

  // wxFlexGridSizer* mapPaneSizer = new wxFlexGridSizer(wxVERTICAL);
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  wxPanel* panel = new wxPanel(this, -1);
  sizer->Add(panel,0,0,5);
  SetSizer(sizer);
  
}

cMapPane::~cMapPane() {}


void cMapPane::paintEvent(wxPaintEvent &evt) {
  wxPaintDC dc(this);
  // wxPaintDC dc(panel);
  render(dc);
}

void cMapPane::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

void cMapPane::render(wxDC& dc) {
  // draw a rectangle
  dc.SetBrush(*wxRED_BRUSH); // blue filling
  dc.SetPen( wxPen( wxColor(80,175,80), 5 ) );
  dc.DrawRectangle( 25, 25, 300, 175 );
}
