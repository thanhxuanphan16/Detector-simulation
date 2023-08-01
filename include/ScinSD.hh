#ifndef SCINSD_HH
#define SCINSD_HH

#include "G4VSensitiveDetector.hh"
#include "g4root.hh"
#include "G4RunManager.hh"

#include "EventAction.hh"
#include "G4EventManager.hh"

class ScinSD : public G4VSensitiveDetector
{
public:
    ScinSD(G4String);
    ~ScinSD();

private:
    virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*);
    EventAction *fEventAction;
};
#endif // !PHOTOSD_HH