#ifndef EventAction_h
#define EventAction_h 1


#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Step.hh"
#include "globals.hh"
class RunAction;
class HistoManager;
class Histo;

/// \brief The EventAction class Класс отвечающий
///  за запуск 1 первичной частицы
///
class EventAction: public G4UserEventAction
{
public:
    EventAction();
    ~EventAction();
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);


    private:
    G4int fHodHC1ID;
    G4int fHodHC4;
    G4int fHodHC13;


};
#endif

