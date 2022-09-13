#include "EventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "MyHit.hh"
#include "G4SDManager.hh"
#include "HistoManager.hh"

//using namespace CLHEP;
EventAction::EventAction(): G4UserEventAction(),
    fHodHC1ID(-1),
    fHodHC4(-1)
 {

  //  G4RunManager::GetRunManager()->SetPrintProgress(1);

}

EventAction::~EventAction() {}
//Выполняется перед запуском начальной частицы
void EventAction::BeginOfEventAction(const G4Event*)
{
if (fHodHC1ID == -1) {
    auto sdManager = G4SDManager::GetSDMpointer();
    fHodHC4= sdManager->GetCollectionID("hodoscope1/myCollection");


}
}


//Запускается после моделирования прохождения частицы
void EventAction::EndOfEventAction(const G4Event* event)
{   auto analysisManager = G4AnalysisManager::Instance();

    auto hce = event->GetHCofThisEvent();
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("B5EventAction::EndOfEventAction()",
                    "B5Code001", JustWarning, msg);
        return;
    }

    auto hHC4
      = static_cast<MyHitsCollection*>(hce->GetHC(fHodHC4));


     if ((!hHC4)){

         G4ExceptionDescription msg;
         msg << "Some of hits collections of this event not found." << G4endl;
         G4Exception("B5EventAction::EndOfEventAction()",
                     "B5Code001", JustWarning, msg);
         return;
     }

          for (auto i=0;i<hHC4->entries();i++) {  }


    auto nhit  = hHC4->entries();

     for (auto i=0;i<nhit ;i++) {
       auto hit = (*hHC4)[i];
       auto hitPos = hit->GetLocalPos();
      // auto copyNo = hit->GetLayer();
       hit->Print();

    analysisManager->FillH2(0, hitPos.x(), hitPos.y());

      }

}




