#include "wx/fontdata.h"
#include "wx/log.h"

#include "cDrawPane.hpp"
#include "cNotebook.hpp"
#include "cMapPane.hpp"
#include "cPanel_Main.hpp"
#include "../events.hpp"

cNotebook::cNotebook(wxWindow* parent) : wxNotebook(parent, -1) {
  m_panel_Main = new cPanel_Main (this);
  m_drawPane =   new cDrawPane   (this);
  m_mapPane =    new cMapPane    (this);
  
  AddPage(m_panel_Main, "Main", true );
  AddPage(m_drawPane,   "Draw", false);
  AddPage(m_mapPane,    "Map",  false);

  Bind(FONT_CHANGE_EVENT, &cNotebook::OnParentFontChanged, this);
}

cNotebook::~cNotebook() {}

void cNotebook::OnParentFontChanged(wxCommandEvent& event) {
  wxFontData* fData = static_cast<wxFontData*>(event.GetClientData());
  if (fData) {
    // wxLogDebug("cNotebook: Got font change event.");
    for (auto* child : this->GetChildren()) {
      child->SetFont(fData->GetChosenFont());
      child->Refresh();
      
    }
    m_drawPane->SetFont(fData->GetChosenFont());
    wxLogDebug("cNotebook: children notified of font change.");
    delete fData;
  } else {
    wxLogMessage("Uh-oh");
  }
  
  Refresh();
  event.Skip();
}
