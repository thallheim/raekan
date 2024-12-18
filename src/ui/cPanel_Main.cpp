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

#include "cPanel_Main.hpp"
#include "../util/RandGen.hpp"

const int ID_BTN_NEW_SEED = 11031;
const int ID_BTN_2        = 11032;

wxBEGIN_EVENT_TABLE(cPanel_Main, wxPanel)
    EVT_BUTTON(ID_BTN_NEW_SEED, cPanel_Main::OnNewSeed)
    EVT_BUTTON(ID_BTN_2, cPanel_Main::OnButtonTwo)
wxEND_EVENT_TABLE();

cPanel_Main::cPanel_Main(wxWindow* parent)
  : wxPanel(parent, wxID_ANY) {

  m_seed1 = m_rg.getInt(4242, 420042);
  SetBackgroundColour(wxColour(55, 55, 55, 255));

  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->SetSizeHints(this);
  SetSizer(sizer);

  wxButton* m_buttonQ = new wxButton(this, ID_BTN_NEW_SEED, "Random seed");
  wxButton* m_button1 = new wxButton(this, ID_BTN_2, ("Button two"));
  m_seedDisplay = new wxTextCtrl(this, -1, "Seed",  wxPoint(5, 45), wxSize(100,20), wxTE_READONLY | wxTE_LEFT | wxTE_NOHIDESEL | wxTE_RICH2);

  sizer->Add(m_buttonQ);
  sizer->Add(m_button1);
  sizer->Add(m_seedDisplay);

  // wxLogDebug("cPanel_Main created");
}

cPanel_Main::~cPanel_Main() {}

void cPanel_Main::OnButtonTwo(wxCommandEvent& WXUNUSED(event)) {
  wxLogMessage("Woo!");
}

void cPanel_Main::OnNewSeed(wxCommandEvent& event) {
  int old_seed = m_seed1;
  int seed = m_rg.getInt(4242, 420042);
  wxString str = std::to_string(seed);
  m_seedDisplay->SetValue(str.Trim());
  wxLogDebug("New seed: %s", str);
}
