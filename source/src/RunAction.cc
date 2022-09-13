#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"
#include "G4AccumulableManager.hh"
#include "HistoManager.hh"
#include "G4Threading.hh"


using namespace CLHEP;
using namespace std;

//Конструктор класса RunAction, обратите внимание, что переменные G4Accumulable
//как Energy(0) должны быть объявлены с неким начальным значением
RunAction::RunAction()
    : G4UserRunAction()
{
    fHistoManager = new HistoManager();

}

RunAction::~RunAction()
{
    delete fHistoManager;
}

//Функция выполняется перед началом запуска потока моделирования
void RunAction::BeginOfRunAction(const G4Run* )
{ 
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
     if ( analysisManager->IsActive() ) {
       analysisManager->OpenFile();
     }
}

void RunAction::EndOfRunAction(const G4Run* )
{

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
      if ( analysisManager->IsActive() ) {
        analysisManager->Write();
        analysisManager->CloseFile();
}
}
