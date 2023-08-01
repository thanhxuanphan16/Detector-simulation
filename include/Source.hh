#ifndef PARTICLEGUN_HH
#define PARTICLEGUN_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"
#include "globals.hh"

#include "parameters.hh"

class  Source : public G4VUserPrimaryGeneratorAction
{
public:
    Source();
    ~Source();
    virtual void GeneratePrimaries(G4Event*);
private:
    G4ParticleGun *fParticleGun;
};


#endif