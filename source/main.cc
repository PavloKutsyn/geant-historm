#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "Randomize.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "QGSP_BERT.hh"
#include "G4UIExecutive.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4HadronicProcessStore.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

int main(int argc,char** argv)

{

    // Setting randomizer
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    G4long seed = time(NULL);
    CLHEP::HepRandom::setTheSeed(seed);
    // Create the run manager
    G4RunManager* theRunManager = new G4RunManager;


    // Set the mandatory initialization classes
  theRunManager->SetUserInitialization(new DetectorConstruction());
  G4VModularPhysicsList* physicsList = new QGSP_BERT;
  G4HadronicProcessStore * hps = G4HadronicProcessStore::Instance();
  hps->SetVerbose(0);
  theRunManager->SetUserInitialization(physicsList);
  theRunManager->SetUserAction(new PrimaryGeneratorAction(""));
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  theRunManager->Initialize();
  theRunManager->SetUserAction(new StackingAction);
  theRunManager->SetUserAction(new SteppingAction);

  RunAction* runAction = new RunAction;
 theRunManager->SetUserAction(runAction);
 EventAction* eventAction = new EventAction();
 theRunManager->SetUserAction(eventAction);


  // Start the visualisation driver
  auto visManager = new G4VisExecutive;
  visManager->Initialize();

  // Process macro or start UI session
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
 if ( argc == 1 ) {
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  UImanager->ApplyCommand("/control/execute vis.mac");
  ui->SessionStart();
  delete ui;
 }
 else {
 G4String command = "/control/execute ";
 G4String fileName = argv[1];
 UImanager->ApplyCommand(command+fileName);
 }
  delete visManager;
  delete theRunManager;
  return EXIT_SUCCESS;
}
