#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{   


    //Load data file/////////////////////////////////////////
    energy_vec = new G4PhysicsOrderedFreeVector();
    intensity_vec = new G4PhysicsOrderedFreeVector();
    reflec_vec = new G4PhysicsOrderedFreeVector();

    NumEntries = 0.;
    std::ifstream datafile;
    std::ifstream reflecfile;
    datafile.open("ej-276_spec.dat");
    reflecfile.open("reflectivity.dat");

    
    G4double wlen, intensity, energy;
    G4double wlen_r, reflec;

    while(1){

        datafile >> wlen >> intensity;
        if(datafile.eof()) break;

        NumEntries = NumEntries + 1;
   
        //std::cout<<"NumEntries : "<<NumEntries<<G4endl;
        //G4cout<<wlen<<" "<<intensity<<G4endl;
        energy = 1.239841939/wlen*1E+3*eV;
        //G4cout<<energy<<" "<<intensity<<G4endl;
        energy_vec->InsertValues(NumEntries, energy);
        intensity_vec->InsertValues(NumEntries, intensity);
        
    }

    
    while(1){
        reflecfile>>wlen_r>>reflec;
        if(reflecfile.eof()) break;
        energy = 1.239841939/wlen_r*1E+3*eV;
        reflec_vec->InsertValues(energy,reflec);
    }
    

    datafile.close();
    reflecfile.close();
    energy_vec->SetSpline(false);
    intensity_vec->SetSpline(false);
    reflec_vec->SetSpline(false);
    ///////////////////////////////////////////////////////
    
        
}

DetectorConstruction::~DetectorConstruction()
{}

void DetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    //Vacuum
    G4Material *vacuum = new G4Material("vacuum",0.000001*mg/cm3,1);
    vacuum->AddElement(nist->FindOrBuildElement("H"),1);

    

    ///////
    //Plastic
    G4Material *plastic = new G4Material("plastic",1.08*g/cm3,2);
    plastic->AddElement(nist->FindOrBuildElement("C"),9);
    plastic->AddElement(nist->FindOrBuildElement("H"),10);



    G4Material *air = new G4Material("air",0.012479*mg/cm3,4);
    air->AddElement(nist->FindOrBuildElement("N"),0.755268);
    air->AddElement(nist->FindOrBuildElement("O"),0.231781);
    air->AddElement(nist->FindOrBuildElement("Ar"),0.012827);
    air->AddElement(nist->FindOrBuildElement("C"),0.000124);

    G4Material *quartz = new G4Material("quartz",2.65*g/cm3,2);
    quartz->AddElement(nist->FindOrBuildElement("Si"),1);
    quartz->AddElement(nist->FindOrBuildElement("O"),2);

    G4Material *alumimium = new G4Material("aluminium", 2.7*g/cm3,1);
    alumimium->AddElement(nist->FindOrBuildElement("Al"),1);



    //adding Optical properties
    //G4int NumEntries = 10;
    //G4double energy[NumEntries]={  3.44*eV, 3.26*eV, 3.1*eV, 2.95*eV,2.92*eV, 2.82*eV, 2.7*eV, 2.58*eV,2.48*eV,2.39*eV };
    //G4double rindexScin[NumEntries] = { 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58,  1.58, 1.58,1.58};
    //G4double rindexWorld[NumEntries] = {1,1,1,1,1,1,1,1,1,1}; //chinh lai 0.5 0.5
    //G4double abslWorld[NumEntries] = {3*cm,3*cm,3*cm,3*cm,3*cm,3*cm,3*cm,3*cm,3*cm,3*cm};
    //G4double rindexDet[NumEntries]={1,1,1,1,1,1,1,1,1,1};
    //G4double fraction[NumEntries]={ 0.04, 0.07, 0.20, 0.84, 1.00, 0.83,  0.40, 0.17, 0.08, 0.03};
    //G4double reflectivity[NumEntries]={1,1,1,1,1,1,1,1,1,1};


    //Adding Optical properties with data file
    G4double energy[NumEntries]={0};
    G4double rindexScin[NumEntries] = {0};
    G4double rindexWorld[NumEntries] = {0}; 
    G4double abslWorld[NumEntries] = {0};
    G4double rindexDet[NumEntries] = {0};
    G4double fraction[NumEntries] = {0};
    G4double reflectivity[NumEntries]= {0};

    double val;
    for(int i = 0; i<NumEntries; i++){
        
        energy[i] = energy_vec->Value(i+1);
        fraction[i] = intensity_vec->Value(i+1);
        rindexWorld[i] = 1;
        rindexScin[i] = 1.58;
        rindexDet[i] = 1;
        abslWorld[i] = 3*cm;
        //reflectivity[i] = 1;
        
        reflectivity[i] = reflec_vec->Value(energy[i]);
        //std::cout<<"energy : "<<energy[i]<<" refelectivity : "<<reflectivity[i]<<std::endl;

    }



    /////////////////////////////////////////////

    G4MaterialPropertiesTable *mptScin = new G4MaterialPropertiesTable();
    mptScin->AddProperty("RINDEX",energy,rindexScin,NumEntries);
    mptScin->AddProperty("SCINTILLATIONCOMPONENT1",energy, fraction,NumEntries);
    mptScin->AddProperty("SCINTILLATIONCOMPONENT2",energy,fraction,NumEntries);
    mptScin->AddProperty("SCINTILLATIONCOMPONENT3",energy,fraction,NumEntries);

    double scin_yield = 8600*0.3/MeV; //30% quantum efficiency
    mptScin->AddConstProperty("SCINTILLATIONYIELD",scin_yield);
    

    if(particle=="gamma"){
        //Gamma constants
    
        mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT1",4.6*ns);
        mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT2",19*ns);
        mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT3",130*ns);
        mptScin->AddConstProperty("SCINTILLATIONYIELD1",0.73);
        mptScin->AddConstProperty("SCINTILLATIONYIELD2",0.16);
        mptScin->AddConstProperty("SCINTILLATIONYIELD3",0.11);
        mptScin->AddConstProperty("RESOLUTIONSCALE",2.43);
        //std::cout<<"Day la` : "<<particle<<std::endl;
    }
    else if(particle=="neutron"){
           //neutron constants
   
        mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT1",5.0*ns);
        mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT2",22*ns);
        mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT3",180*ns);
        mptScin->AddConstProperty("SCINTILLATIONYIELD1",0.54);
        mptScin->AddConstProperty("SCINTILLATIONYIELD2",0.21);
        mptScin->AddConstProperty("SCINTILLATIONYIELD3",0.25);
        mptScin->AddConstProperty("RESOLUTIONSCALE",2.43);

        //std::cout<<"Day la` : "<<particle<<std::endl;
    }
    
    


    //Set the Birks Constant for Plastic Scintillator
    plastic->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
    



    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX",energy,rindexWorld,NumEntries);
    mptWorld->AddProperty("ABSLENGTH",energy,abslWorld,NumEntries);

    G4MaterialPropertiesTable *mptDet = new G4MaterialPropertiesTable();
    mptDet->AddProperty("RINDEX",energy,rindexDet,NumEntries);


    plastic->SetMaterialPropertiesTable(mptScin);
    air->SetMaterialPropertiesTable(mptWorld);
    vacuum->SetMaterialPropertiesTable(mptDet);

    //mirror///
    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY",energy,reflectivity,NumEntries);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);



    //Asign Volume material
    world_mat = air;
    scin_mat = plastic;
    det_mat = vacuum;
    mylar_mat = alumimium;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    DefineMaterials();

    ///World//////////////////////
    G4double half_world_x = 0.5*m;
    G4double half_world_y = 0.5*m;
    G4double half_world_z = 0.5*m;

    G4Box *world_sol = new G4Box("world_sol",half_world_x, half_world_y,half_world_z);
    world_log = new G4LogicalVolume(world_sol,world_mat,"world_log");
    world_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),world_log,"world_phys",0,false,0,true);

    //Aluminium Mylar volume
    G4double half_mylar1_x = 7.*mm;
    G4double half_mylar1_y = 20.*mm;
    G4double half_mylar1_z = 7.*mm;

    G4double half_mylar2_x = 7.01*mm;
    G4double half_mylar2_y = 20.01*mm;
    G4double half_mylar2_z = 7.005*mm;

    G4Box *mylar_sol1 = new G4Box("mylar_sol1",half_mylar1_x,half_mylar1_y,half_mylar1_z);
    G4Box *mylar_sol2 = new G4Box("mylar_sol2",half_mylar2_x,half_mylar2_y,half_mylar2_z);
    G4SubtractionSolid *mylar_sol = new G4SubtractionSolid("mylar_sol",
    mylar_sol2,mylar_sol1,0,G4ThreeVector(0,0,-0.01*mm));
    mylar_log = new G4LogicalVolume(mylar_sol, mylar_mat,"mylar_log");
    mylar_phys = new G4PVPlacement(0,G4ThreeVector(0,0,-6.99*mm),mylar_log,"mylar_phys",world_log,false,0,true);

    //Mirror mylar
    G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",mylar_log,mirrorSurface);

    ////Scintillator Volume////
    G4double half_scin_x = 7.*mm;
    G4double half_scin_y = 20.*mm;
    G4double half_scin_z = 7.*mm;

    G4Box *scin_sol = new G4Box("scin_sol",half_scin_x,half_scin_y,half_scin_z);
    scin_log = new G4LogicalVolume(scin_sol,scin_mat,"scin_log");
    scin_phys = new G4PVPlacement(0,G4ThreeVector(0.*mm,0.*mm,-7*mm),scin_log,"scin_phys",world_log,false,0,true);




    ///Photo Detector///
    G4double half_det_x = 25.*mm;
    G4double half_det_y = 25.*mm;
    G4double half_det_z = 1.*mm;

    G4Box *det_sol = new G4Box("det_sol",half_det_x,half_det_y,half_det_z);
    det_log = new G4LogicalVolume(det_sol, det_mat, "det_log");
    det_phys = new G4PVPlacement(0,G4ThreeVector(0.*mm,0.*mm,-15.00001*mm),det_log,"det_phys",world_log,false,0,true);


    return world_phys;

}

void DetectorConstruction::ConstructSDandField()
{
   PhotoDetector *sensDet = new PhotoDetector("SensitiveDetector");
   det_log->SetSensitiveDetector(sensDet);

   ScinSD *sensScin = new ScinSD("SensitiveDetector_Scin");
   scin_log->SetSensitiveDetector(sensScin);

}

