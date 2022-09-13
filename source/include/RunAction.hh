#ifndef B2RunAction_h
#define B2RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Accumulable.hh"

class G4Run;
class HistoManager;
class ActionInitilization;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();
     void BeginOfRunAction(const G4Run*);

    void EndOfRunAction(const G4Run*);

private:
  HistoManager* fHistoManager;

   };

#endif
