#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif
// #include "wx/config.h"

#include "cApp.hpp"
#include "main.hpp"


wxIMPLEMENT_APP(cApp);

cApp::cApp() {}

cApp::~cApp() {}

bool cApp::OnInit() {

  SetVendorName("thallheim");
  SetAppName("Raekan");
  
  m_frameA1 = new cMain();
  m_frameA1->Show();
  return true;
}
