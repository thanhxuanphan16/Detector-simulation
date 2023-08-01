#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

PhysicsList::PhysicsList()
{
    RegisterPhysics (new G4EmStandardPhysics()); //goi EMZ
    RegisterPhysics (new G4OpticalPhysics());

}

PhysicsList::~PhysicsList()
{}
