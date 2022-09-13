
#include "SteppingAction.hh"

#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"
#include "G4DynamicParticle.hh"
#include "G4TrajectoryPoint.hh"
#include "G4ParticleChange.hh"
#include "G4BiasingProcessInterface.hh"
#include "G4SteppingManager.hh"
#include "DetectorConstruction.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction()
:G4UserSteppingAction(),   fScoringVolume(0)

{


}
SteppingAction::~SteppingAction()
{ }


void SteppingAction::UserSteppingAction(const G4Step* aStep)
{



}
