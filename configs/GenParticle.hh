#ifndef GENPARTICLE_HH
#define GENPARTICLE_HH
#include <iostream>

class GenParticle {
  
private:
  int    fGenParticlePDG, fGenParticleID, fGenParticleMotherID, fProcessEnding;
  double fGenParticleEnergy;
  bool   fNeutronInternal, fNeutronCapture;
  bool   fIsPhoton  = false;
  bool   fIsNeutron = false;
  
public:
  //CONSTRUCTOR FOR GENERATED PARTICLE
  GenParticle(int    cGenParticlePDG      , int cGenParticleID  ,
              int    cGenParticleMotherID , int cProcessEnding  ,
              double cGenParticleEnergy   ,
              bool   cNeutronInternal     , bool cNeutronCapture)
  {
    fGenParticlePDG      = cGenParticlePDG     ;
    fGenParticleID       = cGenParticleID      ;
    fGenParticleMotherID = cGenParticleMotherID;
    fProcessEnding       = cProcessEnding      ;
    fGenParticleEnergy   = cGenParticleEnergy  ;
    fNeutronInternal     = cNeutronInternal    ;
    fNeutronCapture      = cNeutronCapture     ;
    
    if (cGenParticlePDG == 22  ) {fIsPhoton  = true;}
    if (cGenParticlePDG == 2112) {fIsNeutron = true;}
    
  }
  
  //DESTRUCTOR FOR GEN PARTICLE
  ~GenParticle() {};
  
  //VARIOUS SIMPLE MEMBER FUNCTIONS
  int GetPartPDG() const { return fGenParticlePDG;      };
  int GetPartID () const { return fGenParticleID;       };
  int GetPartMID() const { return fGenParticleMotherID; };
  int GetPartEnd() const { return fProcessEnding;       };

  double GetPartEnergy() const { return fGenParticleEnergy; };
  
  bool GetNeutInternal() const { return fNeutronInternal; };
  bool GetNeutCapture () const { return fNeutronCapture;  };
  bool IsPhoton()        const { return fIsPhoton;        };
  bool IsNeutron()       const { return fIsNeutron;       };
  
  void Print() {
    std::cout << "Particle PDG:       " << GetPartPDG()    << "\n"
              << "Particle ID:        " << GetPartID ()    << "\n"
              << "Particle Mother ID: " << GetPartMID()    << "\n"
              << "End Process:        " << GetPartEnd()    << "\n"
              << "ParticleEnergy:     " << GetPartEnergy() << "\n"
              << std::endl;
  }
  
};
#endif
