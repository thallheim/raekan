#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include <wx/colour.h>
#include "wx/event.h"
#include "wx/gdicmn.h"
#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"

#include "../events.hpp"
#include "cLandingPane.hpp"
#include "../util/RandGen.hpp"

const int ID_BTN_NEW_SEED = 11001;
const int ID_BTN_2        = 11002;

cLandingPane::cLandingPane(wxWindow* parent)
  : wxPanel(parent, wxID_ANY), m_parent(parent) {

  m_seed1 = m_rg.getInt(4242, 420042);
  SetBackgroundColour(wxColour(55, 55, 55, 255));

  wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(rootSizer);
  // rootSizer->SetSizeHints(this);
  rootSizer->Layout();

  wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
  wxButton* m_button_newSeed = new wxButton(this, ID_BTN_NEW_SEED, "Random seed");
  wxButton* m_button_two = new wxButton(this, ID_BTN_2, ("Button two"));
  m_seedDisplay = new wxTextCtrl(this, -1, "Seed",  wxPoint(5, 45), wxSize(100,20), wxTE_READONLY | wxTE_LEFT | wxTE_NOHIDESEL | wxTE_RICH2);

  btnSizer->Add(m_button_newSeed);
  btnSizer->Add(m_button_two);
  rootSizer->Add(btnSizer);
  rootSizer->Add(m_seedDisplay);

  // Bindings
  m_button_newSeed->Bind( wxEVT_BUTTON, &cLandingPane::OnNewSeed,   this);
  m_button_two->Bind(     wxEVT_BUTTON, &cLandingPane::OnButtonTwo, this);
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
