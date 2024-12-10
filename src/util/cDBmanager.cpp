#include "cDBmanager.hpp"

cDBmanager* cDBmanager::cDBmanager_ = nullptr;

cDBmanager::cDBmanager() {}
    
cDBmanager *cDBmanager::GetInstance() {
  if (cDBmanager_ == nullptr) {
    cDBmanager_ = new cDBmanager();
  }
  return cDBmanager_;
}
