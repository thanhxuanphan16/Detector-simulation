#include "RunAction.hh"

RunAction::RunAction()
{
    //define command while running
    fMessenger = new G4GenericMessenger(this, "/file/","file saving");

    fMessenger->DeclareProperty("file_name",file_name,"Declare save file");
    
    file_name = "light_output.root"; //default file name

}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run*)
{   
    start_time = clock();
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    std::string file_dir  = "../output/"+file_name; //file name have to declare while running
    man->OpenFile(file_dir);
    man->CreateNtuple("Photon","Photon");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleFColumn("fTime");
    man->CreateNtupleDColumn("Z");
    man->CreateNtupleDColumn("fWlen");

    man->FinishNtuple(0);
    
    man->CreateNtuple("Scoring","Scoring");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fEdep");
    man->CreateNtupleIColumn("fNphoton");
    
    man->FinishNtuple(1);
}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
    end_time = clock();
    std::cout<<"=========== Time for each run : "<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<" s ===========\n";
}
