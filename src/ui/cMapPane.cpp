#include <wx/config.h>
#include <wx/log.h>
#include <wx/event.h>

#include "cMapPane.hpp"
#include "wx/fileconf.h"
#include "wx/gdicmn.h"
#include "wx/sizer.h"


wxBEGIN_EVENT_TABLE(cMapPane, wxPanel)
    EVT_PAINT(cMapPane::OnPaint)
wxEND_EVENT_TABLE()


// cMapPane::cMapPane(wxWindow* parent, wxFileConfig* config)
// : wxPanel(parent, -1), m_config(config) {
cMapPane::cMapPane(wxWindow* parent)
: wxPanel(parent, -1) {
  SetBackgroundColour(*wxBLACK);




  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  // wxPanel* panel = new wxPanel(this, -1);
  // sizer->Add(panel,0,0,5);
  SetSizer(sizer);
  
}

cMapPane::~cMapPane() {}

void cMapPane::OnPaint(wxPaintEvent &evt) {
  wxPaintDC dc(this);
  render(dc);
}

void cMapPane::render(wxDC& dc) {
  dc.SetTextForeground(wxColour(245,170,5,255));

  this->DrawCross(dc.FromDIP(25), dc.FromDIP(300),
                 dc.FromDIP(50), dc.FromDIP(50),
                 dc);
  
  auto ogPen = dc.GetPen();
  dc.SetPen(*wxWHITE_PEN);
  dc.DrawPoint(10,10);

  dc.SetPen(ogPen);

}

void cMapPane::setFontData(wxFontData *inputData) { m_fData = inputData; }

void cMapPane::drawStar(int posX, int posY, int radius, wxDC &dc) {
  
}

void cMapPane::DrawCross(int x, int y, int width, int height, wxDC &dc) {
  dc.DrawText("Star", dc.FromDIP(x), dc.FromDIP(y-m_font.GetPixelSize().y-1));
  dc.SetClippingRegion(dc.FromDIP(x), dc.FromDIP(y), dc.FromDIP(width), dc.FromDIP(height));
  dc.SetPen(wxPen(*wxBLUE, 1));
  // dc.CrossHair(dc.FromDIP(x + width / 2), dc.FromDIP(y + height / 2));
  dc.CrossHair(dc.FromDIP(x), dc.FromDIP(y));
  dc.DestroyClippingRegion();
}
