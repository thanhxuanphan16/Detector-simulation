#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "PhotoSD.hh"
#include "ScinSD.hh"

#include "G4GenericMessenger.hh"
#include "parameters.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
     DetectorConstruction();
     ~DetectorConstruction();

    virtual G4VPhysicalVolume *Construct();
private:
    void DefineMaterials();

    virtual void ConstructSDandField();
    
   

    //Material
    G4Material *world_mat;
    G4Material *scin_mat;
    G4Material *det_mat;
    G4Material *mylar_mat;

    //Volumes
    G4LogicalVolume *world_log;
    G4VPhysicalVolume *world_phys;

    G4LogicalVolume *scin_log;
    G4VPhysicalVolume *scin_phys;
    
    G4LogicalVolume *det_log;
    G4VPhysicalVolume *det_phys;

    G4LogicalVolume *mylar_log;
    G4VPhysicalVolume *mylar_phys;

    G4OpticalSurface *mirrorSurface;

    //Define optical properties
    G4int NumEntries;
    G4PhysicsOrderedFreeVector *energy_vec;
    G4PhysicsOrderedFreeVector *intensity_vec;
    G4PhysicsOrderedFreeVector *reflec_vec;


    
};

#endif
