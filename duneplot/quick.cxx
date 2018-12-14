#include <iostream>
#include <string>
#include <unistd.h>
#include "../configs/GenParticle.hh"
#include "../configs/Variable.hh"
#include "../configs/Hit.hh"
#include "TFile.h"
#include "TTree.h"
#include "TPad.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "../plotting/Figure.hh"
#include "../plotting/MakeHist.hh"
#include "../helpers/ArbitraryAnaInputManager.hh"

void EventDisplay(std::string InputFileName, std::string OutputFileName) {
  
  TFile* InFile = new TFile(InputFileName.c_str(),"READ");
  std::map<int, ArbitraryAnaInputManager*> aaim;
  aaim[0] = new ArbitraryAnaInputManager();
  
  aaim[0]->SetInputTree("trineutronbackground/TriNeutron");
  
  for (auto& it: aaim) {
    it.second->SetInputFile(InputFileName);
    it.second->LoadTree();
  }
  
  for (auto const& it: aaim) {
    int fNEvent = -1;
    int adc_threshold = it.first;
    ArbitraryAnaInputManager* im = it.second;
    
    if (fNEvent == -1) { fNEvent = im->GetEntries(); }
    
    Variable *SumEGamma = new Variable("SumGammaEnergy"  ,
                                       "GeV"             ,
                                       "#SigmaE_{#gamma}",
                                       {100, 0, 20})          ;
    
    TH1D *EnergyHist = MakeHist(SumEGamma).GenerateHistogram();
    
    for (int i=0; i<fNEvent; ++i){
      
      im->GetEntry(i);
      for (int it=0; it<(*im->GenParticleEnergy).size(); ++it)
      EnergyHist->Fill((*im->GenParticleEnergy)[it]*1000);
      
    }
    FigureHist(SumEGamma, EnergyHist, 1, 0).MakePlot();
  }
}


void PrintUsage(){
  std::cout << "Option i is the input file name"  << std::endl;
  std::cout << "Option t is the input tree name"  << std::endl;
  std::cout << "Option o is the oupput file name" << std::endl;
}

int main(int argc, char** argv){
  
  int opt;
  extern char *optarg;
  extern int optopt;
  
  std::string InputFileName  = "/Users/aranborkum/Docterate/Data Files/Neutron FIles/1e4_neutron.root";
  std::string OutputFileName = "Output_1.pdf";
  
  while ( (opt = getopt(argc, argv, "i:o:t:")) != -1 ) {  // for each option...
    switch ( opt ) {
      case 'i':
        InputFileName = optarg;
        break;
      case 'o':
        OutputFileName = optarg;
        break;
      case '?':  // unknown option...
        std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
        PrintUsage();
        break;
    }
  }
  
  if (InputFileName != "" && OutputFileName != ""){
    EventDisplay(InputFileName, OutputFileName);
  }
  
  return 0;
}
