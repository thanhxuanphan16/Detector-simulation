#include <iostream>

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "G4OpticalParameters.hh"


#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4OpticalPhysics.hh"

#include "DetectorConstruction.hh"
//#include "PhysicsList.hh" //Disable physics file and use physics list
#include "ActionInitialization.hh"
int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();


    //Physics lists//
    G4int verbose = 1;
    G4PhysListFactory factory;
    G4VModularPhysicsList *physlist = factory.GetReferencePhysList("QGSP_BERT_HP_EMZ");
    physlist->RegisterPhysics(new G4OpticalPhysics()); //adding optical process
    physlist->SetVerboseLevel(verbose);


    
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(physlist);
    //runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization);

    runManager->Initialize();

    //setting some optical parameters
    auto opticalParams = G4OpticalParameters::Instance();
    opticalParams->SetScintEnhancedTimeConstants(true);

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialise();

    G4UImanager *UImanager =  G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefesh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    
    ui->SessionStart();

    
    
    return 0;
}