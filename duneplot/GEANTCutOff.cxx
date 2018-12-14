#include <iostream>
#include <string>
#include <unistd.h>
#include "../configs/GenParticle.hh"
#include "../configs/Hit.hh"
#include "TFile.h"
#include "TTree.h"
#include "TPad.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TProfile.h"
#include "TText.h"
#include "TLatex.h"
#include "../plotting/Figure.hh"
#include "../plotting/MakeProfile.hh"
#include "../helpers/ArbitraryAnaInputManager.hh"

void EventDisplay(std::string InputFileName, std::string InputTreeName, std::string OutputFileName, int table){
  
  TFile* InFile = new TFile(InputFileName.c_str(),"READ");
  std::map<int, ArbitraryAnaInputManager*> aaim;
  aaim[0] = new ArbitraryAnaInputManager();
  
  aaim[0]->SetInputTree("primtrineutronbackground10/PrimTriNeutron");
  
  for (auto& it: aaim) {
    it.second->SetInputFile(InputFileName);
    it.second->LoadTree();
  }
  
  Variable *CutOff = new Variable("GEANTCutOff", {"MeV", "nm"}, {"KE", "disp"},
                                  {10000, 10e-8, 10e-3, 100, 100000});

  std::map<int, TProfile*> CutOffProfile;
  
  for (auto const& it: aaim) {
    int fNEvent = -1;
    int adc_threshold = it.first;
    ArbitraryAnaInputManager* im = it.second;
    
    if (fNEvent == -1) { fNEvent = im->GetEntries(); }
    
    CutOffProfile[adc_threshold] = MakeProfile(CutOff).GenerateProfile();
  
    for (int i=0; i<fNEvent; ++i){
    
      im->GetEntry(i);
    
      std::vector<GenParticle*> vec_GenParticles;
      std::vector<Hit*>         vec_Hits;
    
      vec_GenParticles.clear();
      vec_Hits.clear();
    
      for (int j=0; j<im->GenParticlePDG->size(); ++j) {
	GenParticle* part = new GenParticle((*im->GenParticlePDG)[j]               ,
					    (*im->GenParticleID)[j]                ,
					    (*im->GenParticleMotherID)[j]          ,
					    (*im->ProcessEnding)[j]                ,
					    (*im->GenParticleEnergy)[j]            ,
					    (*im->ThisNeutronStaysInTheDetector)[i],
					    (*im->ThisNeutronCapture)[i]           );
	vec_GenParticles.push_back(part);
      }
    
      double Momentum      = (*im->GenParticleStartMom)[0]*1000;
      double MassEnergy    = 939.565;
      double KineticEnergy = TMath::Sqrt(Momentum*Momentum + MassEnergy*MassEnergy) - MassEnergy;
    
      double displacement  = 0;
    
      for (int it=0; it<im->GenParticleStartX->size(); ++it) {
	if ((*im->GenParticlePDG)[it] == 2112) {
	  displacement +=
	    TMath::Sqrt( ((*im->GenParticleEndX)[it]-(*im->GenParticleStartX)[it])*((*im->GenParticleEndX)[it]-(*im->GenParticleStartX)[it]) +
			 ((*im->GenParticleEndY)[it]-(*im->GenParticleStartY)[it])*((*im->GenParticleEndY)[it]-(*im->GenParticleStartY)[it]) +
			 ((*im->GenParticleEndZ)[it]-(*im->GenParticleStartZ)[it])*((*im->GenParticleEndZ)[it]-(*im->GenParticleStartZ)[it])) ;
	}
      }
    
      CutOffProfile[adc_threshold]->Fill(KineticEnergy, displacement, 1);
    }
  
    for (auto const& it: CutOffProfile) {
      FigureProfile(CutOff, it.second, 1, 0).MakePlot();
    }
  
  }
}

void PrintUsage(){
  std::cout << "Option i is the input file name"  << std::endl;
  std::cout << "Option t is the input tree name"  << std::endl;
  std::cout << "Option o is the oupput file name" << std::endl;
}

int main(int argc, char** argv){

  std::vector<std::string> prims = {"primtrineutronbackground10",
            "primtrineutronbackground15",
            "primtrineutronbackground20",
            "primtrineutronbackground25",
            "primtrineutronbackground30"};

  int opt;
  extern char *optarg;
  extern int optopt;
  std::string InputFileName  = "/Users/aranborkum/Docterate/Data Files/Neutron FIles/10keV_neutron.root";
  std::string OutputFileName = "Output_1.pdf";
  std::string InputTreeName  = "primtrineutronbackground10/PrimTriNeutron";

  while ( (opt = getopt(argc, argv, "i:o:t:")) != -1 ) {  // for each option...
    switch ( opt ) {
    case 'i':
      InputFileName = optarg;
      break;
    case 'o':
      OutputFileName = optarg;
      break;
    case 't':
      InputTreeName = optarg;
      break;
    case '?':  // unknown option...
      std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
      PrintUsage();
      break;
    }
  }

  if (InputTreeName != "" && InputFileName != "" && OutputFileName != ""){
    EventDisplay(InputFileName, InputTreeName, OutputFileName, 0);
  }

  return 0;
}
