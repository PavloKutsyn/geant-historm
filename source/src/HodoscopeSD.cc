#include "HodoscopeSD.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include <iostream>
#include <fstream>
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include <iostream>
#include <vector>
#include "HistoManager.hh"

int i =0;
HodoscopeSD::HodoscopeSD(G4String name)
: G4VSensitiveDetector(name),
  data(ctime(&now)),
  dataNamefile(data),
  fHistoName(dataNamefile + ".csv" ),
  fHCID(-1),
  fHitsCollection(0)
{      collectionName.insert("myCollection");
 }

HodoscopeSD::~HodoscopeSD()
{

}

void HodoscopeSD::Initialize (G4HCofThisEvent* hce)
{
    fHitsCollection
      = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);

    // Add this collection in hce
    if (fHCID<0) {
      fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fHCID,fHitsCollection);
}
G4bool HodoscopeSD::ProcessHits(G4Step* step, G4TouchableHistory* ROhist)
{

  G4ParticleDefinition* particleType = step->GetTrack()->GetDefinition();
  G4int PDGencoding = particleType -> GetPDGEncoding();
  const G4VTouchable* touchable  = step->GetPreStepPoint()->GetTouchable();
  G4VPhysicalVolume* motherPhysical = touchable->GetVolume(); // mother
  G4int copyNo = motherPhysical->GetCopyNo();
  auto preStepPoint = step->GetPreStepPoint();
  G4ThreeVector worldPos = preStepPoint->GetPosition();
  G4ThreeVector localPos = touchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(worldPos);


  auto hit = new MyHit(copyNo);
    auto physical = touchable->GetVolume();
    hit->SetLogV(physical->GetLogicalVolume());
    hit->SetWorldPos(worldPos);
    hit->SetLocalPos(localPos);


 fHitsCollection->insert(hit);

  G4RunManager* runManager = G4RunManager::GetRunManager();
  G4int event = runManager->GetCurrentEvent()->GetEventID();
  G4bool condition = step->IsLastStepInVolume();


//i++;
//G4String nam = fHistoName;
//std::ofstream File;

//if (condition==true){
// File.open(nam, std::ios::app);
// if (File.is_open()){
//        File
//            << std::setiosflags(std::ios::fixed)
//            << std::setprecision(2)
//            << event<< ","
//            << step->GetTrack()->GetPosition().x()/cm<< ","
//            << step->GetTrack()->GetPosition().y()/cm<< ","
//            << step->GetTrack()->GetPosition().z()/cm<< ","
//            << step->GetTrack()->GetGlobalTime()/ns<< ","
//            << step->GetTotalEnergyDeposit()/MeV<< ","
//            << step->GetTrack()->GetTrackID() <<","
//            << copyNo <<","
//            << step->GetTrack()->GetKineticEnergy()/MeV<< ","
//            << PDGencoding
//            <<G4endl;}
//}
//File.close();

  return true;
}
void HodoscopeSD::EndOfEvent(G4HCofThisEvent* )
{;}
