#include <SQLiteCpp/SQLiteCpp.h>
#include "SQLiteCpp/Database.h"

#include <exception>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
// #include "wx/config.h"

#include "wx/app.h"
#include "cApp.hpp"
#include "main.hpp"


wxIMPLEMENT_APP(cApp);

cApp::cApp() {
  auto& app = wxGetApp();
  app.SetAppName("Raekan");
  app.SetVendorName("thallheim");

}

cApp::~cApp() {}

bool cApp::OnInit() {

  
  m_frameA1 = new cMain();
  m_frameA1->Show();
  return true;
}

