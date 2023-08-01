#include "EventAction.hh"

EventAction::EventAction(RunAction*)
{
    fEdep = 0.;
    fnumPhoton=0.;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fEdep =0.;
    fnumPhoton=0.;
}


void EventAction::EndOfEventAction(const G4Event* aEvent)
{
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    G4int eventID = aEvent->GetEventID();

    //Saving Data
    if(fEdep >0){
        man->FillNtupleIColumn(1,0,eventID);
        man->FillNtupleDColumn(1,1,fEdep);
        man->FillNtupleIColumn(1,2,fnumPhoton);
        man->AddNtupleRow(1);
    }


    G4cout<<"EventID : "<<eventID<<" \tEnergy deposition : "<<fEdep<<" \tPhoton counts : "<<fnumPhoton<<G4endl;
}