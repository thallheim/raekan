#include "cApp.hpp"
#include "main.hpp"

wxIMPLEMENT_APP(cApp);

cApp::cApp() {}

cApp::~cApp() {}

bool cApp::OnInit() {
  m_frameA1 = new cMain();
  m_frameA1->Show();
  return true;
}
