#include <iostream>
#include <string>
#include <unistd.h>
#include "../configs/GenParticle.hh"
#include "../configs/Hit.hh"
#include "../configs/Variable.hh"
#include "TFile.h"
#include "TTree.h"
#include "TPad.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "../plotting/MakeHist.hh"
#include "../plotting/Figure.hh"
#include "../helpers/ArbitraryAnaInputManager.hh"

void EventDisplay(std::string InputFileName, std::string OutputFileName){
  
  TFile* InFile = new TFile(InputFileName.c_str(),"READ");
  std::map<int, ArbitraryAnaInputManager*> aaim;
  aaim[0] = new ArbitraryAnaInputManager();

  aaim[0]->SetInputTree("trineutronbackground/TriNeutron");

  for (auto& it: aaim) {
    it.second->SetInputFile(InputFileName);
    it.second->LoadTree();
  }
  
  Variable *gammaEnergy   = new Variable("GammaEnergies", "GeV", "E_{#gamma}", {50, 0, 12}, {10e-2, 10e5});
  Variable *SumGammaE     = new Variable("SumGammaEnergy", "GeV", "#SigmaE_{#gamma}", {100, 0, 20});
  Variable *ProcessEnd    = new Variable("EndProcess", "#", "End Process", {10, 0, 10});
  
  std::map<int, TH1D*> gammaEnergies;
  std::map<int, TH1D*> gammaESum;
  std::map<int, TH1D*> endProcesses;
//  std::map<int, TH2D*> eventDisplay;
  
  for (auto const& it: aaim) {
    int fNEvent = -1;
    int adc_threshold = it.first;
    ArbitraryAnaInputManager* im = it.second;
    
    if (fNEvent == -1) { fNEvent = im->GetEntries(); }
    
    gammaEnergies[adc_threshold] = MakeHist(gammaEnergy).GenerateHistogram();
    gammaESum    [adc_threshold] = MakeHist(SumGammaE)  .GenerateHistogram();
    endProcesses [adc_threshold] = MakeHist(ProcessEnd) .GenerateHistogram();
//    eventDisplay [adc_threshold] = new TH2D("", "", 30000, 0, 30000, 4500, 0, 4500);
    
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
      for (int j=0; j<im->GenParticlePDG->size(); ++j) {
        if ((*im->GenParticlePDG)[j] == 2112) {
          for (int k=0; k<im->Hit_X->size(); ++k) {
            Hit* hit = new Hit((*im->Hit_X)[k],
                               (*im->Hit_Y)[k],
                               (*im->Hit_Z)[k],
                               (*im->HitChan)[k],
                               (*im->HitTime)[k],
                               (*im->HitSADC)[k],
                               (*im->HitSize)[k]);
            vec_Hits.push_back(hit);
          }
        }
      }

      int    IDToLookFor = -1;
      double GammaETotal =  0;

      for (int part=0; part<vec_GenParticles.size(); ++part) {
        GenParticle* particle = vec_GenParticles[part];
        if (particle->GetNeutInternal() == 1 && particle->GetNeutCapture() == 1)
          continue;
        if (particle->IsNeutron() && particle->GetPartEnd() == 10)
          IDToLookFor = particle->GetPartID();
      }
      if (IDToLookFor != 1) {
        for (int part=0; part<vec_GenParticles.size(); ++part) {
          GenParticle* particle = vec_GenParticles[part];
          if (particle->GetPartMID() == IDToLookFor && particle->IsPhoton()) {
            gammaEnergies[adc_threshold]->Fill(particle->GetPartEnergy() * 1000);
            GammaETotal  +=    (particle->GetPartEnergy() * 1000);
          }
        }
        if (GammaETotal != 0)
          gammaESum[adc_threshold]->Fill(GammaETotal);
      }

//      if (1 == 0) {
//        for (int it=0; it<vec_Hits.size(); ++it){
//          Hit* hit = vec_Hits[it];
//          eventDisplay[adc_threshold]->Fill(hit->GetHitChan(), hit->GetHitTime(), hit->GetHitSADC()/hit->GetHitSize());
//          for (int t = 1; t<(*im->HitSize)[it]/2; ++t){
//            eventDisplay[adc_threshold]->Fill(hit->GetHitChan(), hit->GetHitTime()-t,
//                               hit->GetHitSADC()/hit->GetHitSize());
//            eventDisplay[adc_threshold]->Fill(hit->GetHitChan(), hit->GetHitTime()+t,
//                               hit->GetHitSADC()/hit->GetHitSize());
//          }
//        }
//      }
      
      for (auto& it: vec_GenParticles) {
        delete it;
        it = NULL;
      }
      vec_GenParticles.clear();
      for (auto& it: vec_Hits) {
        delete it;
        it = NULL;
      }
      vec_Hits.clear();

    }
  }
  
  for (auto const& it: gammaEnergies) {
    FigureHist(gammaEnergy, it.second, 1, 0).MakePlot();
  }
  for (auto const& it: gammaESum) {
    FigureHist(SumGammaE, it.second, 0, 0).MakePlot();
  }
}


void PrintUsage(){
  std::cout << "Option i is the input file name"  << std::endl;
  std::cout << "Option t is the input tree name"  << std::endl;
  std::cout << "Option o is the output file name" << std::endl;
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
