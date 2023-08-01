#include "PhotoSD.hh"


PhotoDetector::PhotoDetector(G4String name) :G4VSensitiveDetector(name)
{}

PhotoDetector::~PhotoDetector()
{}

G4bool PhotoDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4ParticleDefinition *particleType = aStep->GetTrack()->GetDefinition();
    G4String particleName = particleType->GetParticleName();
    G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
    G4double time = aStep->GetPreStepPoint()->GetGlobalTime();
    G4double zpre = aStep->GetPreStepPoint()->GetPosition().getZ();
    G4double zpost = aStep->GetPostStepPoint()->GetPosition().getZ();
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    //G4double velocity = aStep->GetPostStepPoint()->GetVelocity();
    G4int eventID=0.;
    G4double fwlen = 1.239841939/energy*1E-6;

    //Variable for photon count


    //Static_cast User Event ACtion to G4USerEventAction for using user-defined function
    EventAction *eventAction = static_cast<EventAction *>(G4EventManager::GetEventManager()->GetUserEventAction());
    
    if(particleName=="opticalphoton"){
    
        eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        man->FillNtupleIColumn(0,0,eventID);
        man->FillNtupleFColumn(0,1,time);
        man->FillNtupleDColumn(0,2,zpre);
        man->FillNtupleDColumn(0,3,fwlen);
        man->AddNtupleRow(0); 

        //accumulating photo count
        eventAction->AddNphoton(1);


        std::cout<<"EventID: "<<eventID<<"\tTen Hat : "<<particleName<<" \tZpre: "<<zpre<<" \twlen : "<<fwlen<<"\ttime :"<<time<<"\n";
    }
    
}