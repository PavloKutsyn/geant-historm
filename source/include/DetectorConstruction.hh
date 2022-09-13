#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include <vector>
#include "G4Material.hh"

class G4LogicalVolume;
class DetectorMessenger;
class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual void ConstructSDandField(); // declaration of method for constructing sensitive field

    virtual G4VPhysicalVolume* Construct(); // declaration of method for constracting physical volumes
    //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  private:
    // Setting pointer of logical volumes for further assigning as sensitive detector
    G4LogicalVolume* fHodoscope1Logical;
    G4LogicalVolume* fHodoscope2Logical;
    G4LogicalVolume* fHodoscope3Logical;
    G4LogicalVolume* fHodoscope4Logical;
    G4LogicalVolume* fHodoscope5Logical;
    G4LogicalVolume* fHodoscope6Logical;
    G4LogicalVolume* fHodoscope7Logical;
    G4LogicalVolume* fHodoscope8Logical;
    G4LogicalVolume* fHodoscope9Logical;
    G4LogicalVolume* fHodoscope10Logical;
    G4LogicalVolume* fHodoscope11Logical;
    G4LogicalVolume* fHodoscope12Logical;
    G4LogicalVolume*  fScoringVolume;


};

#endif
