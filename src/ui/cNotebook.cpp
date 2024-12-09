#include "wx/debug.h"
#include "wx/fontdata.h"
#include "wx/log.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/rtti.h"
#include "wx/window.h"

#include "cDrawPane.hpp"
#include "cMapPane.hpp"
#include "cLandingPane.hpp"
#include "cNotebook.hpp"
#include "cPanel_Main.hpp"
#include "../events.hpp"

cNotebook::cNotebook(wxWindow* parent, wxFileConfig* config) : wxNotebook(parent, wxID_ANY), m_config(config) {

  m_landingPane = new cLandingPane (this);
  m_mainPanel   = new cPanel_Main  (this);
  m_drawPane    = new cDrawPane    (this);
  m_mapPane     = new cMapPane     (this);

  AddPage(m_landingPane, "Landing", true);
  AddPage(m_mainPanel,   "Main",    false);
  AddPage(m_drawPane,    "Draw",    false);
  AddPage(m_mapPane,     "Map",     false);

  if (dm_mainPaneID == 0) {
    dm_mainPaneID = m_mainPanel->GetId();
  }

  if (!m_config->Read("/Main/MainAppFont")) {
    wxLogDebug("Notebook: Init without config.");
    // TODO: Set/get (or both) some sort of default. Query top-level?
  } else {
    for (auto* child : this->GetChildren()) {
      child->SetFont(m_config->Read("/Main/MainAppFont"));
    }
  }
}


cNotebook::~cNotebook() {}

void cNotebook::OnParentFontChanged(wxCommandEvent& event) {
  wxLogDebug("Notebook: OnParentFontChanged() invoked on: %p", this);
  wxFontData* fData = static_cast<wxFontData*>(event.GetClientData());
  if (fData) {
    // wxLogDebug("cNotebook: Got font change event.");
    m_font = fData->GetChosenFont();
    for (auto* child : this->GetChildren()) {
      child->SetFont(fData->GetChosenFont());
      child->Refresh();
    }

    delete fData;
  } else {
    wxLogMessage("Uh-oh");
  }

  Refresh();
  event.Skip();
}

void cNotebook::OnShowMainPanel(wxCommandEvent& WXUNUSED(event)) {
  int pc = this->GetPageCount();
  wxLogDebug("Notebook: ID: %d", this->GetId());
  wxLogDebug("Notebook: Page count: %d", pc);
}

void cNotebook::GetNumPages(wxCommandEvent& event) {
  long pc = this->GetPageCount();
  wxLogDebug("Notebook: Num pages: %d", pc);
}
