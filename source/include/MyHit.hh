#ifndef MYHIT_HH
#define MYHIT_HH
#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"

class MyHit : public G4VHit
{
public:
    MyHit (G4int);
     MyHit (const MyHit &right);
    virtual ~MyHit ();
//    virtual void Draw();
    virtual void Print();
     const MyHit& operator=(const MyHit &right);
     int operator==(const MyHit &right) const;

     // setter methods

   void SetLocalPos(G4ThreeVector xyz) { fLocalPos = xyz; }
   void SetWorldPos(G4ThreeVector xyz) { fWorldPos = xyz; }
   void SetLayer(G4int copy) { fLayerNumber = copy; }
   void SetReplica(G4int replica) { fReplicaNumber = replica; }
   void SetLogV(G4LogicalVolume* val) { fPLogV = val; }
   const G4LogicalVolume* GetLogV() const { return fPLogV; }
   // getter methods

   G4ThreeVector GetLocalPos() const { return fLocalPos; }
   G4ThreeVector GetWorldPos() const { return fWorldPos; }
   G4int GetLayer() const { return fLayerNumber; }
   G4int GetReplica() const { return fReplicaNumber; }


private:
   G4int fId;

    G4ThreeVector fLocalPos;
    G4ThreeVector fWorldPos;
    G4int fLayerNumber;
    G4int fReplicaNumber;
    const G4LogicalVolume* fPLogV;

    };
#include "G4THitsCollection.hh"

using MyHitsCollection = G4THitsCollection<MyHit> ;

#endif // MYHIT_H
