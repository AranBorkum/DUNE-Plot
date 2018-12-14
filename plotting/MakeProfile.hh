#ifndef MAKEPROFILE_HH
#define MAKEPROFILE_HH

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <unistd.h>
#include "../configs/GenParticle.hh"
#include "../configs/Hit.hh"
#include "../configs/Variable.hh"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"
#include "TMultiGraph.h"
#include "TPad.h"
#include "TProfile.h"
#include "TText.h"
#include "TTree.h"


class MakeProfile {
  
private:
  Variable* fVariable = new Variable();
  
public:
  //CONSTRUCTOR
  MakeProfile(Variable* cVariable)
  {
    fVariable = cVariable;
  };
  
  //DESTRUCTOR
  ~MakeProfile() {};
  
  //FUNCTION TO READ VARIABLE AND MAKE TH1D
  TProfile* GenerateProfile()
  {
    std::vector<float> profileConfig = fVariable->GetBinning();
    TProfile *p1 = new TProfile("", "", profileConfig[0], profileConfig[1], profileConfig[2]
                                      , profileConfig[3], profileConfig[4]);
    return p1;
  }
};

#endif
