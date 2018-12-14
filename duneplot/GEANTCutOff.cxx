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
#include "../plotting/PrettyPlot.hh"

void EventDisplay(std::string InputFileName, std::string InputTreeName, std::string OutputFileName, int table){
  
  TFile* InFile = new TFile(InputFileName.c_str(),"READ");
  TTree* Tree = (TTree*)InFile->Get(InputTreeName.c_str());
  
  std::vector<double>   * GenParticleStartX   = NULL;
  std::vector<double>   * GenParticleStartY   = NULL;
  std::vector<double>   * GenParticleStartZ   = NULL;
  std::vector<double>   * GenParticleEndX     = NULL;
  std::vector<double>   * GenParticleEndY     = NULL;
  std::vector<double>   * GenParticleEndZ     = NULL;
  std::vector<int>      * HitSize             = NULL;
  std::vector<int>      * GenParticlePDG      = NULL;
  std::vector<int>      * GenParticleID       = NULL;
  std::vector<int>      * GenParticleMotherID = NULL;
  std::vector<int>      * ProcessEnding       = NULL;
  std::vector<float>    * HitChan             = NULL;
  std::vector<float>    * HitTime             = NULL;
  std::vector<float>    * HitSADC             = NULL;
  std::vector<float>    * Hit_X               = NULL;
  std::vector<float>    * Hit_Y               = NULL;
  std::vector<float>    * Hit_Z               = NULL;
  std::vector<double>   * GenParticleEnergy   = NULL;
  std::vector<double>   * GenParticleStartMom = NULL;
  std::vector<bool>     * ThisNeutronCapture  = NULL;
  std::vector<bool>     * ThisNeutronStaysInTheDetector = NULL;
  
  Tree->SetBranchAddress("HitTime"            , &HitTime            );
  Tree->SetBranchAddress("HitChan"            , &HitChan            );
  Tree->SetBranchAddress("HitSADC"            , &HitSADC            );
  Tree->SetBranchAddress("HitSize"            , &HitSize            );
  Tree->SetBranchAddress("Hit_X"              , &Hit_X              );
  Tree->SetBranchAddress("Hit_Y"              , &Hit_Y              );
  Tree->SetBranchAddress("Hit_Z"              , &Hit_Z              );
  Tree->SetBranchAddress("GenParticlePDG"     , &GenParticlePDG     );
  Tree->SetBranchAddress("GenParticleID"      , &GenParticleID      );
  Tree->SetBranchAddress("GenParticleMotherID", &GenParticleMotherID);
  Tree->SetBranchAddress("GenParticleEnergy"  , &GenParticleEnergy  );
  Tree->SetBranchAddress("GenParticleStartMom", &GenParticleStartMom);
  Tree->SetBranchAddress("GenParticleStartX"  , &GenParticleStartX  );
  Tree->SetBranchAddress("GenParticleStartY"  , &GenParticleStartY  );
  Tree->SetBranchAddress("GenParticleStartZ"  , &GenParticleStartZ  );
  Tree->SetBranchAddress("GenParticleEndX"    , &GenParticleEndX    );
  Tree->SetBranchAddress("GenParticleEndY"    , &GenParticleEndY    );
  Tree->SetBranchAddress("GenParticleEndZ"    , &GenParticleEndZ    );
  Tree->SetBranchAddress("ProcessEnding"      , &ProcessEnding      );
  Tree->SetBranchAddress("ThisNeutronCapture" , &ThisNeutronCapture );
  Tree->SetBranchAddress("ThisNeutronStaysInTheDetector", &ThisNeutronStaysInTheDetector);

  TProfile *cutoff   = new TProfile("", "", 10000, 10e-8, 10e-3, 100, 100000);
  TH1D     *KE       = new TH1D("", "", 100, 0, 0.05);
  
  
  for (int i=0; i<Tree->GetEntries(); ++i){
    //  for (int i=0; i<1; ++i){
    
    
    Tree->GetEntry(i);
    
    std::vector<GenParticle*> vec_GenParticles;
    std::vector<Hit*>         vec_Hits;
    
    vec_GenParticles.clear();
    vec_Hits.clear();
    
    for (int j=0; j<GenParticlePDG->size(); ++j) {
      GenParticle* part = new GenParticle((*GenParticlePDG)[j]               ,
                                          (*GenParticleID)[j]                ,
                                          (*GenParticleMotherID)[j]          ,
                                          (*ProcessEnding)[j]                ,
                                          (*GenParticleEnergy)[j]            ,
                                          (*ThisNeutronStaysInTheDetector)[i],
                                          (*ThisNeutronCapture)[i]           );
      vec_GenParticles.push_back(part);
    }
    
    double Momentum      = (*GenParticleStartMom)[0]*1000;
    double MassEnergy    = 939.565;
    double KineticEnergy = TMath::Sqrt(Momentum*Momentum + MassEnergy*MassEnergy) - MassEnergy;
    
    double displacement  = 0;
    
    for (int it=0; it<GenParticleStartX->size(); ++it) {
      if ((*GenParticlePDG)[it] == 2112) {
        displacement +=
        TMath::Sqrt( ((*GenParticleEndX)[it]-(*GenParticleStartX)[it])*((*GenParticleEndX)[it]-(*GenParticleStartX)[it]) +
                     ((*GenParticleEndY)[it]-(*GenParticleStartY)[it])*((*GenParticleEndY)[it]-(*GenParticleStartY)[it]) +
                     ((*GenParticleEndZ)[it]-(*GenParticleStartZ)[it])*((*GenParticleEndZ)[it]-(*GenParticleStartZ)[it])) ;
      }
    }
    
    cutoff->Fill(KineticEnergy, displacement, 1);
    KE->Fill(KineticEnergy);
  }
  
  PrettyProfile *p = new PrettyProfile("c1", "KEvsDisp", cutoff, "KE [MeV]", "#Delta x [nm]", 0, 1);
  p->MakePlot();
  
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
  
  std::string InputFileName  = "/Users/aranborkum/Docterate/Scripts/DUNE-Plot/RootFiles/10keV_neutron.root";
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
