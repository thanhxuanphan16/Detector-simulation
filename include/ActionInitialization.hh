#ifndef ACTIONINITIALIZER_HH
#define ACTIONINITIALIZER_HH

#include "G4VUserActionInitialization.hh"
#include "Source.hh"
#include "RunAction.hh"
#include "EventAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    ~ActionInitialization();

    virtual void Build() const;
    
};

#endif // !ACTIONINITIALIZER_HH