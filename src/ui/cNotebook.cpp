#include "wx/fontdata.h"
#include "wx/log.h"
#include "wx/config.h"
#include "wx/fileconf.h"

#include "cDrawPane.hpp"
#include "cNotebook.hpp"
#include "cMapPane.hpp"
#include "cPanel_Main.hpp"
#include "../events.hpp"
#include "wx/window.h"

cNotebook::cNotebook(wxWindow* parent, wxFileConfig* config) : wxNotebook(parent, -1), m_config(config) {
  m_panel_Main = new cPanel_Main (this);
  m_drawPane =   new cDrawPane   (this);
  m_mapPane =    new cMapPane    (this);

  AddPage(m_panel_Main, "Main", true );
  AddPage(m_drawPane,   "Draw", false);
  AddPage(m_mapPane,    "Map",  false);

  // Bind(FONT_CHANGE_EVENT, &cNotebook::OnParentFontChanged, this);
  // wxLogStatus("Notebook: Init without config obj.");

  if (!m_config->Read("/Main/MainAppFont")) {
    wxLogDebug("Notebook: Init without config obj.");
    // TODO: Set/get (or both) some sort of default. Query top-level?
  } else {
    wxLogDebug("Notebook: Init with provided config.");
      wxLogDebug("Notebook: Children applying font '%s'", m_config->Read("/Main/MainAppFont"));
    for (auto* child : this->GetChildren()) {
      child->SetFont(m_config->Read("/Main/MainAppFont"));
      // wxLogDebug("Font '%s'", m_config->Read("/Main/MainAppFont"));
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
    // TODO: Why was I making this call specifically?
    // m_drawPane->SetFont(fData->GetChosenFont());

    delete fData;
  } else {
    wxLogMessage("Uh-oh");
  }

  Refresh();
  event.Skip();
}
