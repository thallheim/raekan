#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif


class cDBmanager {
public:
  cDBmanager(cDBmanager& other) = delete;
  void operator=(const cDBmanager &) = delete;

  static cDBmanager* GetInstance();

protected:
  cDBmanager();

  static cDBmanager* cDBmanager_;
  
private:

};  
