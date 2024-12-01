#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

#include "wx/event.h"
#include "wx/gdicmn.h"
#include <wx/colour.h>
#include "wx/textctrl.h"

#include "cPanel_Main.hpp"
#include "../util/RandGen.hpp"

const int ID_BTN_NEW_SEED = 11001;
const int ID_BTN_2 = 11002;

wxBEGIN_EVENT_TABLE(cPanel_Main, wxPanel)
    EVT_BUTTON(ID_BTN_NEW_SEED, cPanel_Main::OnNewSeed)
    EVT_BUTTON(ID_BTN_2, cPanel_Main::OnButtonTwo)
wxEND_EVENT_TABLE();

cPanel_Main::cPanel_Main(wxWindow* parent)
  : wxPanel(parent, wxID_ANY) {

  m_seed1 = m_rg.getInt(4242, 420042);
  SetBackgroundColour(wxColour(55, 55, 55, 255));

  wxButton* m_buttonQ = new wxButton(this, ID_BTN_NEW_SEED, "New seed", wxPoint(5, 5), wxSize(100, 30));
  wxButton* m_button1 = new wxButton(this, ID_BTN_2, "Two button", wxPoint(120, 5), wxSize(100, 30));
  m_seedDisplay = new wxTextCtrl(this, -1, "HENLO, SEEDO",  wxPoint(5, 45), wxSize(100,20), wxTE_READONLY | wxTE_LEFT | wxTE_NOHIDESEL | wxTE_RICH2);
   
}

cPanel_Main::~cPanel_Main() {}

void cPanel_Main::OnButtonTwo(wxCommandEvent& WXUNUSED(event)) {

}

void cPanel_Main::OnNewSeed(wxCommandEvent& event) {
  int old_seed = m_seed1;
  int seed = m_rg.getInt(4242, 420042);
  wxString str = std::to_string(seed);
  m_seedDisplay->SetValue(str.Trim());
}
