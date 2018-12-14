#ifndef ARBITRARYANAINPUTMANAGER_HH
#define ARBITRARYANAINPUTMANAGER_HH
#include "InputManager.hh"

#include "TTree.h"

class ArbitraryAnaInputManager: public InputManager {

public:
  int Run   ;
  int SubRun;
  int Event ;
  
  std::vector<int>      * GenParticlePDG               ;
  std::vector<int>      * GenParticleID                ;
  std::vector<int>      * GenParticleMotherID          ;
  std::vector<int>      * ProcessEnding                ;
  std::vector<double>   * GenParticleEnergy            ;
  std::vector<double>   * GenParticleStartMom          ;
  std::vector<bool>     * ThisNeutronStaysInTheDetector;
  std::vector<bool>     * ThisNeutronCapture           ;
  
  std::vector<float>    * Hit_X  ;
  std::vector<float>    * Hit_Y  ;
  std::vector<float>    * Hit_Z  ;
  std::vector<float>    * HitChan;
  std::vector<float>    * HitTime;
  std::vector<float>    * HitSADC;
  std::vector<int>      * HitSize;
  
  std::vector<double>   * GenParticleStartX;
  std::vector<double>   * GenParticleStartY;
  std::vector<double>   * GenParticleStartZ;
  std::vector<double>   * GenParticleEndX  ;
  std::vector<double>   * GenParticleEndY  ;
  std::vector<double>   * GenParticleEndZ  ;

  ArbitraryAnaInputManager():
  Run        (0),
  SubRun     (0),
  Event      (0),

  GenParticleStartX            (NULL),
  GenParticleStartY            (NULL),
  GenParticleStartZ            (NULL),
  GenParticleEndX              (NULL),
  GenParticleEndY              (NULL),
  GenParticleEndZ              (NULL),
  
  GenParticlePDG               (NULL),
  GenParticleID                (NULL),
  GenParticleMotherID          (NULL),
  ProcessEnding                (NULL),
  GenParticleEnergy            (NULL),
  GenParticleStartMom          (NULL),
  ThisNeutronStaysInTheDetector(NULL),
  ThisNeutronCapture           (NULL),

  Hit_X                        (NULL),
  Hit_Y                        (NULL),
  Hit_Z                        (NULL),
  HitChan                      (NULL),
  HitTime                      (NULL),
  HitSADC                      (NULL),
  HitSize                      (NULL){};
  
  ~ArbitraryAnaInputManager() {
    delete GenParticleStartX; GenParticleStartX = NULL;
    delete GenParticleStartY; GenParticleStartY = NULL;
    delete GenParticleStartZ; GenParticleStartZ = NULL;
    delete GenParticleEndX  ; GenParticleEndX   = NULL;
    delete GenParticleEndY  ; GenParticleEndY   = NULL;
    delete GenParticleEndZ  ; GenParticleEndZ   = NULL;
    
    delete GenParticlePDG               ; GenParticlePDG                = NULL;
    delete GenParticleID                ; GenParticleID                 = NULL;
    delete GenParticleMotherID          ; GenParticleMotherID           = NULL;
    delete ProcessEnding                ; ProcessEnding                 = NULL;
    delete GenParticleEnergy            ; GenParticleEnergy             = NULL;
    delete GenParticleStartMom          ; GenParticleStartMom           = NULL;
    delete ThisNeutronStaysInTheDetector; ThisNeutronStaysInTheDetector = NULL;
    delete ThisNeutronCapture           ; ThisNeutronCapture            = NULL;
    
    delete Hit_X  ; Hit_X   = NULL;
    delete Hit_Y  ; Hit_Y   = NULL;
    delete Hit_Z  ; Hit_Z   = NULL;
    delete HitChan; HitChan = NULL;
    delete HitTime; HitTime = NULL;
    delete HitSADC; HitSADC = NULL;
    delete HitSize; HitSize = NULL;
    if (f_Input) f_Input->Close();
  };

  void LoadTree() {
    Initialise();
    
    t_Input->SetBranchAddress("Run"   , &Run   );
    t_Input->SetBranchAddress("SubRun", &SubRun);
    t_Input->SetBranchAddress("Event" , &Event );

    t_Input->SetBranchAddress("GenParticleStartX", &GenParticleStartX);
    t_Input->SetBranchAddress("GenParticleStartY", &GenParticleStartY);
    t_Input->SetBranchAddress("GenParticleStartZ", &GenParticleStartZ);
    t_Input->SetBranchAddress("GenParticleEndX"  , &GenParticleEndX  );
    t_Input->SetBranchAddress("GenParticleEndY"  , &GenParticleEndY  );
    t_Input->SetBranchAddress("GenParticleEndZ"  , &GenParticleEndZ  );
    
    t_Input->SetBranchAddress("GenParticlePDG"               , &GenParticlePDG               );
    t_Input->SetBranchAddress("GenParticleID"                , &GenParticleID                );
    t_Input->SetBranchAddress("GenParticleMotherID"          , &GenParticleMotherID          );
    t_Input->SetBranchAddress("ProcessEnding"                , &ProcessEnding                );
    t_Input->SetBranchAddress("GenParticleEnergy"            , &GenParticleEnergy            );
    t_Input->SetBranchAddress("GenParticleStartMom"          , &GenParticleStartMom          );
    t_Input->SetBranchAddress("ThisNeutronStaysInTheDetector", &ThisNeutronStaysInTheDetector);
    t_Input->SetBranchAddress("ThisNeutronCapture"           , &ThisNeutronCapture           );
    
    t_Input->SetBranchAddress("Hit_X"  , &Hit_X  );
    t_Input->SetBranchAddress("Hit_Y"  , &Hit_Y  );
    t_Input->SetBranchAddress("Hit_Z"  , &Hit_Z  );
    t_Input->SetBranchAddress("HitChan", &HitChan);
    t_Input->SetBranchAddress("HitTime", &HitTime);
    t_Input->SetBranchAddress("HitSADC", &HitSADC);
    t_Input->SetBranchAddress("HitSize", &HitSize);
    
  };
  
};

#endif
