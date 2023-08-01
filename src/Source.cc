#include "Source.hh"

Source::Source()
{
    fParticleGun = new G4ParticleGun(1);
}

Source::~Source()
{
    delete fParticleGun;
}

void Source::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    //G4String particleName = "neutron";
    G4ParticleDefinition *fparticle = particleTable->FindParticle(particle);
    G4String spectrumType = "Co-60";

    G4ThreeVector pos(0.,0.,1.*mm);
    //G4ThreeVector mom(0.,0,-1.);

    G4double cosTheta = -0.95*G4UniformRand() - 0.05; //random [-0.05, -0.95]
    G4double phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1.- cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi);
    G4double uy = sinTheta*std::sin(phi);
    G4double uz = cosTheta;


    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux, uy,uz));
    //fParticleGun->SetParticleMomentum(1*MeV);

    fParticleGun->SetParticleDefinition(fparticle);
////////////////////////////////////////////////////Energy random///////////////////////
    double energy_final = 0.;


    if(spectrumType == "Mono"){
        energy_final = 0.662; //MeV
    }
    else if (spectrumType == "Co-60"){
        double energy[2] = {1.173, 1.332};
        double intensity[2] = {99.85, 99.9826};
        double ratio = intensity[0]/(intensity[0]+intensity[1]);

        double r = G4UniformRand();


        if(r<ratio) energy_final = energy[0];
        else energy_final = energy[1];
    }
    else if (spectrumType == "Na-22"){
        double energy[2] = {0.511, 1.274};
        double intensity[2] = {180.7, 99.94};
        double ratio = intensity[0]/(intensity[0]+intensity[1]);

        double r = G4UniformRand();


        if(r<ratio) energy_final = energy[0];
        else energy_final = energy[1];
    }
    else if (spectrumType=="neutron-Cf-252"){ //neutron spectrum of Cf-252
        double a, b, gpar, ferg, g2;

        a = 1.175;
        b = 1.04;
        do{
            gpar = std::sqrt(std::pow(1+0.125*a*b,2)-1)+(1+0.125*a*b);
            g2 = -std::log(G4UniformRand());

            ferg = a*gpar*g2;
        }while(std::pow((1-gpar)*(1+g2)-std::log(G4UniformRand()),2)>b*ferg);

        energy_final = ferg;

    }
    else{ //gamma spectrum of Cf-252
        double r = G4UniformRand();

        if(r==0.0) energy_final = 0.085;
        else if(r<=0.0001) energy_final = 0.0855 + 0.01692*(r/0.0001)-0.02401*std::pow(r/0.0001,2)+0.01274*std::pow(r/0.0001,3);
        else if(r>0.0001&&r<=0.01) energy_final = 0.09141 + 0.23846*((r-0.0001)/0.0099)-1.75947*std::pow((r-0.0001)/0.0099,2)+10.98611*std::pow((r-0.0001)/0.0099,3) - 43.19181*std::pow((r-0.0001)/0.0099,4)+105.70005*std::pow((r-0.0001)/0.0099,5)-160.72894*std::pow((r-0.0001)/0.0099,6)+147.43399*std::pow((r-0.0001)/0.0099,7)-74.60043*std::pow((r-0.0001)/0.0099,8)+15.97547*std::pow((r-0.0001)/0.0099,9);
	    else if(r>0.01 && r<=0.1537) energy_final = 0.14486 + 0.40914*((r-0.01)/0.1437)-1.2815*std::pow((r-0.01)/0.1437,2) + 5.07377*std::pow((r-0.01)/0.1437,3)-15.42031*std::pow((r-0.01)/0.1437,4)+31.96346*std::pow((r-0.01)/0.1437,5)-43.12605*std::pow((r-0.01)/0.1437,6)+36.02908*std::pow((r-0.01)/0.1437,7)-16.87185*std::pow((r-0.01)/0.1437,8)+3.37941*std::pow((r-0.01)/0.1437,9);
	    else if (r>0.1537&&r<=0.7114) energy_final = (-1/2.3)*std::log(0.71956*(0.1537-r)+0.50158);
	    else{ energy_final = (-1/1.1)*std::log(1.15292*(0.7114-r)+0.33287);}
                
    }

    

    fParticleGun->SetParticleEnergy(energy_final);

////////////////////////////////////////////////////////////////////////////////////////

    fParticleGun->GeneratePrimaryVertex(anEvent);
}