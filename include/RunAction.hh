#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "g4root.hh"
#include <time.h>
#include "G4GenericMessenger.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();
    clock_t start_time;
    clock_t end_time;

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
private:
    G4GenericMessenger *fMessenger;
    std::string file_name;
};
#endif // !RUNACTION_HH