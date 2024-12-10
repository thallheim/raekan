#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "wx/checkbox.h"
#include "wx/colour.h"
#include "wx/event.h"
#include <wx/gbsizer.h>
#include "wx/gdicmn.h"
#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"

#include "../events.hpp"
#include "cLandingPane.hpp"
#include "../util/RandGen.hpp"

enum {
  // Prop grid
  ID_PGRID,
  // Buttons
  ID_BTN_NEW_SEED = wxID_HIGHEST,
  ID_BTN_2
};



cLandingPane::cLandingPane(wxWindow* parent)
  : wxPanel(parent, wxID_ANY), m_parent(parent) {

  m_seed1 = m_rg.getInt(4242, 420042);
  SetBackgroundColour(wxColour(55, 55, 55, 255));
  auto oldCol = GetForegroundColour();
  SetForegroundColour(wxColour(255,255,255,255));

  wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(rootSizer);
  rootSizer->SetSizeHints(this);

  // FIXME: Solve imports. Won't link even with propgrid.h included.
  //
  /* wxPropertyGrid* pg = new wxPropertyGrid(this, ID_PGRID, wxDefaultPosition, wxDefaultSize,
                                          wxPG_AUTO_SORT | wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE );
  pg->Append( new wxStringProperty("TestLabel", "TestName", "TestVal") );
  rootSizer->Add(pg, wxEXPAND); */


  // Info panels
  wxFlexGridSizer* fgSzr;
  fgSzr = new wxFlexGridSizer(0, 2, 5, 5);
  fgSzr->AddGrowableCol(0);
  fgSzr->AddGrowableCol(1);
  fgSzr->SetFlexibleDirection(wxBOTH);
  fgSzr->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

  wxStaticBoxSizer* iBoxSzr1;
  iBoxSzr1 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Status")), wxVERTICAL);

  auto iBox1_text = new wxStaticText(iBoxSzr1->GetStaticBox(), wxID_ANY, _("I am text."), wxDefaultPosition, wxDefaultSize, 0);
  iBox1_text->Wrap(-1);
  iBoxSzr1->Add(iBox1_text, 0, wxALL, 5);

  fgSzr->Add(iBoxSzr1, 2, wxEXPAND, 5);

  wxStaticBoxSizer* iBoxSzr2;
  iBoxSzr2 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Database")), wxVERTICAL);

  fgSzr->Add(iBoxSzr2, 1, wxEXPAND, 5);
  wxPanel* bigPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  rootSizer->Add(fgSzr, 1, wxEXPAND, 5);
  rootSizer->Add(bigPanel, 3, wxEXPAND | wxALL, 5);


}

cLandingPane::~cLandingPane() {}

void cLandingPane::OnButtonTwo(wxCommandEvent& event) {
  wxLogDebug("Landing pane: 'OnButtonTwo()' called");
  wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, EVT_ON_SHOW_MAIN);
  evt.SetString("Show it, yo");
  wxPostEvent(m_parent, evt);
  event.Skip();
}

void cLandingPane::OnNewSeed(wxCommandEvent& event) {
  int old_seed = m_seed1;
  int seed = m_rg.getInt(4242, 420042);
  wxString str = std::to_string(seed);
  m_seedDisplay->SetValue(str.Trim());
  wxLogDebug("New seed: %s", str);
}
