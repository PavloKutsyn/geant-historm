#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>
#include "G4BiasingProcessInterface.hh"


class EventAction;
class G4Event;
class G4LogicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
   ~SteppingAction();


    virtual void UserSteppingAction(const G4Step* );
protected:

  private:
    G4LogicalVolume* fScoringVolume;


};


#endif
