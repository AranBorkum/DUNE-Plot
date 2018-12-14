#ifndef MAKEHIST2D_HH
#define MAKEHIST2D_HH

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


class MakeHist2D {
  
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
  TH2D* GenerateHistogram2D()
  {
    std::vector<float> hist2DConfig = fVariable->GetBinning();
    TH2D *h1 = new TH2D("", "", hist2DConfig[0], hist2DConfig[1], hist2DConfig[2],
                                hist2DConfig[3], hist2DConfig[4], hist2DConfig[5]);
    return h1;
  }
};

#endif
