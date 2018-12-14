#ifndef HIT_HH
#define HIT_HH
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TPad.h"
#include "TH1D.h"
#include "TCanvas.h"

class Hit {
  
private:
  
  int   fHitSize;
  float fHit_X, fHit_Y, fHit_Z;
  float fHitChan, fHitTime, fHitSADC;
  
  
public:
  //CONSTRUCTOR FOR HIT
  Hit (float cHit_X  , float cHit_Y  , float cHit_Z  ,
       float cHitChan, float cHitTime, float cHitSACD,
       int   cHitSize)
  {
    fHit_X   = cHit_X  ;
    fHit_Y   = cHit_Y  ;
    fHit_Z   = cHit_Z  ;
    fHitChan = cHitChan;
    fHitTime = cHitTime;
    fHitSADC = cHitSACD;
    fHitSize = cHitSize;
  }
  
  //DESTRUCTOR FOR HIT
  ~Hit() {};
  
  //VARIOUS SIMPLE MEMBER FUNCTIONS
  int   GetHitSize() const { return fHitSize; };
  float GetHitChan() const { return fHitChan; };
  float GetHitTime() const { return fHitTime; };
  float GetHitSADC() const { return fHitSADC; };

  float GetHit_X() const{ return fHit_X; };
  float GetHit_Y() const{ return fHit_Y; };
  float GetHit_Z() const{ return fHit_Z; };
  
  void Print() {
    std::cout << "Hit Size:    " << GetHitSize()    << "\n"
              << "Hit Channel: " << GetHitChan()    << "\n"
              << "Hit Time:    " << GetHitTime()    << "\n"
              << "Hit Sum ADC: " << GetHitSADC()    << "\n"
              << "Hit X \tHit Y \tHit Z"            << "\n"
              << GetHit_X()                         << " \t"
              << GetHit_Y()                         << " \t"
              << GetHit_Z()                         << "\n"
              << std::endl;
  }

};
#endif
