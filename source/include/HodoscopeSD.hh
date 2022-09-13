#ifndef LEGSB5HodoscopeSD_h
#define LEGSB5HodoscopeSD_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4VSensitiveDetector.hh"
#include "MyHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class EventAction;
class HistoManager;

class HodoscopeSD : public G4VSensitiveDetector
{
  public:
    HodoscopeSD(G4String name);
    virtual ~HodoscopeSD();
    
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    virtual void Initialize(G4HCofThisEvent* hce);
    virtual void EndOfEvent (G4HCofThisEvent* hce);

    inline void SetHistoName(G4String& val);
    inline void SetTargetMaterial(const G4Material* p);

  private:
    // variables for setting name of the file with date
     time_t now = time(0);
     char* data;
     G4String dataNamefile;
     G4String fHistoName;
     G4int fHCID;
     MyHitsCollection* fHitsCollection;


};

// method for setting name of the file with date
inline void HodoscopeSD::SetHistoName(G4String& val)
{
  fHistoName = val;
}

#endif
