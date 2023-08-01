#include "ScinSD.hh"

ScinSD::ScinSD(G4String name) :G4VSensitiveDetector(name)
{}

ScinSD::~ScinSD()
{}


G4bool ScinSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4ParticleDefinition *particleType = aStep->GetTrack()->GetDefinition();
    G4String particleName = particleType->GetParticleName();
    G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
    G4double edep = aStep->GetTotalEnergyDeposit();
    
    G4double z = aStep->GetPostStepPoint()->GetPosition().getZ();
    //if(particleName!="opticalphoton"){ 
        
    //std::cout<<"Ten Hat : "<<particleName<<"\t"<<"nang luong : "<<energy<<"\n";
    //}
    G4int eventID=0.;
    EventAction *eventAction = static_cast<EventAction *>(G4EventManager::GetEventManager()->GetUserEventAction());
    eventAction->AddEdep(edep);
    if(edep>0){
        eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
        //std::cout<<"EventID"<<eventID<<" \tZ : "<<z<<" \tEdep : "<<edep<<"\n"; 
    }

}