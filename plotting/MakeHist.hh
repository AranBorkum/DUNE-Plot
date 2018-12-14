#ifndef MAKEHIST_HH
#define MAKEHIST_HH

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


class MakeHist {
  
private:
  Variable* fVariable = new Variable();
  
public:
  //CONSTRUCTOR
  MakeHist(Variable* cVariable)
  {
    fVariable = cVariable;
  };
  
  //DESTRUCTOR
  ~MakeHist() {};
  
  //FUNCTION TO READ VARIABLE AND MAKE TH1D
  TH1D* GenerateHistogram()
  {
    std::vector<int> histConfig = fVariable->GetBinning();
    TH1D *h1 = new TH1D("", "", histConfig[0], histConfig[1], histConfig[2]);
    return h1;
  }
};

#endif
