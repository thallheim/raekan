#pragma once

class cRandGen{
public:
  cRandGen();
  ~cRandGen();
  
  int getInt();
  int getInt(int min, int max);
  int getSeed();
  void setSeed(int seed);
  
private:
  int m_Seed1;

};  
