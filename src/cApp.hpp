#pragma once
#include "main.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class cApp : public wxApp {

public:
  cApp();
  ~cApp();

private:
  cMain *m_frameA1 = nullptr;

  virtual bool OnInit();
};
