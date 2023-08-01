#ifndef PHOTOSD_HH
#define PHOTOSD_HH

#include "G4VSensitiveDetector.hh"
#include "g4root.hh"
#include "G4RunManager.hh"
#include "EventAction.hh"
#include "G4EventManager.hh"

class PhotoDetector : public G4VSensitiveDetector
{
public:
    PhotoDetector(G4String);
    ~PhotoDetector();

private:
    virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*);

};
#endif // !PHOTOSD_HH