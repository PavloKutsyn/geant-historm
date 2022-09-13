#include "DetectorConstruction.hh"
#include "HodoscopeSD.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"
#include "G4PVDivision.hh"
#include "G4UnionSolid.hh"
#include "G4Para.hh"
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4SubtractionSolid.hh"
#include "G4TwoVector.hh"
#include "G4ExtrudedSolid.hh"
#include "G4MultiUnion.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
   fScoringVolume(nullptr)
{}

DetectorConstruction::~DetectorConstruction()
{  }

G4VPhysicalVolume* DetectorConstruction::Construct() // construing geometry
{
    G4bool checkOverlaps = true; // Option to switch on/off checking of volumes overlaps. Verifies if the placed volume is overlapping with existing daughters or with the mother volume.

   // Getting poiner for G4NistManager - Element data base from the NIST DB on Atomic Weights and Isotope Compositions
    G4NistManager* nist = G4NistManager::Instance();

G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
G4Material* concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
G4Material* steel =  nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
G4Material* helium =  nist->FindOrBuildMaterial("G4_He");
G4Material* uran =  nist->FindOrBuildMaterial("G4_URANIUM_OXIDE");

   G4RotationMatrix* rot = new G4RotationMatrix();
   rot->rotateX(90.*deg);
 //  G4PhysicalVolumeStore::GetInstance()->Clean();
   //G4LogicalVolumeStore::GetInstance()->Clean();

   //PK Word Solid
     auto worldSolid
       = new G4Box("worldBox", 16*m/2 ,16*m/2, 16.*m/2);

     auto worldLogical
       = new G4LogicalVolume(worldSolid,
                             world_mat,
                             "worldBox");
     auto worldPhysical
       = new G4PVPlacement(0,
                           G4ThreeVector(0. *m, 0. *m, 0. *m),
                           worldLogical,
                           "worldBox",
                           0,
                           false,
                           0);


 //The HI_STORM_ZERO object binds all volumes to one point "zero" and
 //thus makes it possible to move the entire group of Hi-STORM objects in space.
 G4double X_HI_STORM_ZERO = -0. *cm;
 G4double Y_HI_STORM_ZERO = -0. *cm;
 G4double Z_HI_STORM_ZERO = -0. *cm;

 //The Rot_HI_STORM object is assigned to all volumes and
 //thus makes it possible to rotate the entire group of Hi-STORM objects in space.
 G4RotationMatrix* Rot_HI_STORM= new G4RotationMatrix();
                   Rot_HI_STORM -> rotateX(0.*deg);
                   Rot_HI_STORM -> rotateY(0.*deg);
                   Rot_HI_STORM -> rotateZ(0.*deg);

 //startAngle_HI_STORM,
 //spanningAngle_HI_STORM objects for all cylindrical volumes
 G4double startAngle_HI_STORM = 0.*deg;
 G4double spanningAngle_HI_STORM = 360.*deg;

 //____________________________________________________________________________//


 //____________________________________This is the outer steel wall of HI-STORM//
 //############################################################################//
 //_______________________________________________________________Object_tube_1//

 G4ThreeVector Object_tube_1 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO +0. *cm));

              G4double innerRadius_tube_1 = 174.53 *cm;
              G4double outerRadius_tube_1 = 176.53 *cm;
              G4double hz_tube_1 = (402. *cm)/2;

              G4Tubs* solidtube_1 =
                      new G4Tubs("tube_1",
                       innerRadius_tube_1,
                       outerRadius_tube_1,
                                hz_tube_1,
                      startAngle_HI_STORM,
                  spanningAngle_HI_STORM);

 //Logical volume
              G4LogicalVolume* logictube_1 =
                      new G4LogicalVolume(solidtube_1,  //its solid
                                                steel,  //its material
                                             "tube_1");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_1,  //at position
                             logictube_1,  //its logical volume
                                "tube_1",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //____________________________________________This is a HI-STORM concrete wall//
 //############################################################################//
 //_______________________________________________________________Object_tube_2//

 G4ThreeVector Object_tube_2 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO +0. *cm));

              G4double innerRadius_tube_2 = 104.65 *cm;
              G4double outerRadius_tube_2 = 174.5 *cm;
              G4double hz_tube_2 = (402. *cm)/2;

              G4Tubs* solidtube_2 =
                      new G4Tubs("tube_2",
                       innerRadius_tube_2,
                       outerRadius_tube_2,
                                hz_tube_2,
                      startAngle_HI_STORM,
                  spanningAngle_HI_STORM);

 //Logical volume
              G4LogicalVolume* logictube_2 =
                      new G4LogicalVolume(solidtube_2,  //its solid
                                                concrete,  //its material
                                             "tube_2");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_2,  //at position
                             logictube_2,  //its logical volume
                                "tube_2",  //its name
                            logictube_1,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //_________________________________________This is a HI-STORM inner steel wall//
 //############################################################################//
 //_______________________________________________________________Object_tube_3//

 G4ThreeVector Object_tube_3 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO +0. *cm));

              G4double innerRadius_tube_3 = 102.6 *cm;
              G4double outerRadius_tube_3 = 104.6 *cm;
              G4double hz_tube_3 = (402. *cm)/2;

              G4Tubs* solidtube_3 =
                      new G4Tubs("tube_3",
                       innerRadius_tube_3,
                       outerRadius_tube_3,
                                hz_tube_3,
                      startAngle_HI_STORM,
                  spanningAngle_HI_STORM);

 //Logical volume
              G4LogicalVolume* logictube_3 =
                      new G4LogicalVolume(solidtube_3,  //its solid
                                                concrete,  //its material
                                             "tube_3");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_3,  //at position
                             logictube_3,  //its logical volume
                                "tube_3",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //_______________________________This is the steel bottom of the БЦК-31 basket//
 //############################################################################//
 //_______________________________________________________________Object_tube_4//

 G4ThreeVector Object_tube_4 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO -176.5 *cm));

              G4double innerRadius_tube_4 = 0.0 *cm;
              G4double outerRadius_tube_4 = 96.2 *cm;
              G4double hz_tube_4 = (49. *cm)/2;

              G4VSolid* solidtube_4 =
                      new G4Tubs("tube_4",
                               innerRadius_tube_4,
                               outerRadius_tube_4,
                                        hz_tube_4,
                              startAngle_HI_STORM,
                          spanningAngle_HI_STORM);

 //___________________________________________________________Object_tube_del_4//


              G4double innerRadius_tube_del_4 = 0.0 *cm;
              G4double outerRadius_tube_del_4 = 95.2 *cm;
              G4double hz_tube_del_4 = (29. *cm)/2;

              G4VSolid* solidtube_del_4 =
                       new G4Tubs("tube_4",
                                    innerRadius_tube_del_4,
                                    outerRadius_tube_del_4,
                                             hz_tube_del_4,
                                       startAngle_HI_STORM,
                                   spanningAngle_HI_STORM);

 //______________________________________________________Object_tube_subtract_4//

 G4VSolid* tube_subtract_4 =
         new G4SubtractionSolid("tube_subtract_4", //G4IntersectionSolid G4SubtractionSolid
                                solidtube_4,
                                solidtube_del_4,
                                Rot_HI_STORM,
                                G4ThreeVector (0. *cm, 0. *cm, 10.0 *cm)
                                );



 //Logical volume
              G4LogicalVolume* logictube_4 =
                      new G4LogicalVolume(tube_subtract_4,  //its solid
                                                    steel,  //its material
                                                 "tube_4");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_4,  //at position
                             logictube_4,  //its logical volume
                                "tube_4",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //______________________________________________This is the bottom of HI-STORM//
 //############################################################################//
 //_______________________________________________________________Object_tube_5//

 G4ThreeVector Object_tube_5 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO -201.5 *cm));

              G4double innerRadius_tube_5 = 0. *cm;
              G4double outerRadius_tube_5 = 176.53 *cm;
              G4double hz_tube_5 = (1. *cm)/2;

              G4Tubs* solidtube_5 =
                      new G4Tubs("tube_5",
                       innerRadius_tube_5,
                       outerRadius_tube_5,
                                hz_tube_5,
                      startAngle_HI_STORM,
                  spanningAngle_HI_STORM);

 //Logical volume
              G4LogicalVolume* logictube_5 =
                      new G4LogicalVolume(solidtube_5,  //its solid
                                                steel,  //its material
                                             "tube_5");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_5,  //at position
                             logictube_5,  //its logical volume
                                "tube_5",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking
 //############################################################################//

 //________________________________________________This is the volume of helium//
 //############################################################################//
 //_______________________________________________________________Object_tube_6//

 G4ThreeVector Object_tube_6 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO -166.5 *cm));

              G4double innerRadius_tube_6 = 0.0 *cm;
              G4double outerRadius_tube_6 = 94.5 *cm;
              G4double hz_tube_6 = (29. *cm)/2;

              G4Tubs* solidtube_6 =
                      new G4Tubs("tube_6",
                       innerRadius_tube_6,
                       outerRadius_tube_6,
                                hz_tube_6,
                      startAngle_HI_STORM,
                  spanningAngle_HI_STORM);

 //Logical volume
              G4LogicalVolume* logictube_6 =
                      new G4LogicalVolume(solidtube_6,  //its solid
                                                helium,  //its material
                                             "tube_6");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_6,  //at position
                             logictube_6,  //its logical volume
                                "tube_6",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //_________________These are steel walls and bottom, to save radioactive waste//
 //############################################################################//
 //_______________________________________________________________Object_tube_7//

 G4ThreeVector Object_tube_7 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO +24.57 *cm));

              G4double innerRadius_tube_7 = 0.0 *cm;
              G4double outerRadius_tube_7 = 96.2 *cm;
              G4double hz_tube_7 = (353. *cm)/2;

              G4VSolid* solidtube_7 =
                      new G4Tubs("tube_7",
                               innerRadius_tube_7,
                               outerRadius_tube_7,
                                        hz_tube_7,
                              startAngle_HI_STORM,
                          spanningAngle_HI_STORM);

 //___________________________________________________________Object_tube_del_7//


              G4double innerRadius_tube_del_7 = 0.0 *cm;
              G4double outerRadius_tube_del_7 = 94.78 *cm;
              G4double hz_tube_del_7 = (351.8 *cm)/2;

              G4VSolid* solidtube_del_7 =
                       new G4Tubs("tube_7",
                                    innerRadius_tube_del_7,
                                    outerRadius_tube_del_7,
                                             hz_tube_del_7,
                                       startAngle_HI_STORM,
                                   spanningAngle_HI_STORM);

 //______________________________________________________Object_tube_subtract_7//

 G4VSolid* tube_subtract_7 =
         new G4SubtractionSolid("tube_7", //G4IntersectionSolid G4SubtractionSolid
                                solidtube_7,
                                solidtube_del_7,
                                Rot_HI_STORM,
                                G4ThreeVector (0. *cm, 0. *cm, 1.42 *cm)
                                );



 //Logical volume
              G4LogicalVolume* logictube_7 =
                      new G4LogicalVolume(tube_subtract_7,  //its solid
                                                    steel,  //its material
                                                 "tube_7");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_7,  //at position
                             logictube_7,  //its logical volume
                                "tube_7",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //____________________________These are steel walls and bottom, HI-STORM cover//
 //############################################################################//
 //_______________________________________________________________Object_tube_8//

 G4ThreeVector Object_tube_8 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO +219.5 *cm));

              G4double innerRadius_tube_8 = 0.0 *cm;
              G4double outerRadius_tube_8 = 176.53 *cm;
              G4double hz_tube_8 = (36.83 *cm)/2;

              G4VSolid* solidtube_8 =
                      new G4Tubs("tube_8",
                               innerRadius_tube_8,
                               outerRadius_tube_8,
                                        hz_tube_8,
                              startAngle_HI_STORM,
                          spanningAngle_HI_STORM);

 //___________________________________________________________Object_tube_del_8//


              G4double innerRadius_tube_del_8 = 0.0 *cm;
              G4double outerRadius_tube_del_8 = 174.62 *cm;
              G4double hz_tube_del_8 = (36.83 *cm)/2;

              G4VSolid* solidtube_del_8 =
                       new G4Tubs("tube_8",
                                    innerRadius_tube_del_8,
                                    outerRadius_tube_del_8,
                                             hz_tube_del_8,
                                       startAngle_HI_STORM,
                                   spanningAngle_HI_STORM);

 //______________________________________________________Object_tube_subtract_8//

 G4VSolid* tube_subtract_8 =
         new G4SubtractionSolid("tube_8", //G4IntersectionSolid G4SubtractionSolid
                                solidtube_8,
                                solidtube_del_8,
                                Rot_HI_STORM,
                                G4ThreeVector (0. *cm, 0. *cm, 1.42 *cm)
                                );



 //Logical volume
              G4LogicalVolume* logictube_8 =
                      new G4LogicalVolume(tube_subtract_8,  //its solid
                                                    steel,  //its material
                                                 "tube_8");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_8,  //at position
                             logictube_8,  //its logical volume
                                "tube_8",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //______________________________This is the volume of concrete, cover HI-STORM//
 //############################################################################//
 //_______________________________________________________________Object_tube_9//

 G4ThreeVector Object_tube_9 =
         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
                       (Y_HI_STORM_ZERO +0. *cm),
                       (Z_HI_STORM_ZERO +220.92 *cm)); //220.92

              G4double innerRadius_tube_9 = 0 *cm;
              G4double outerRadius_tube_9 = 174.6 *cm;
              G4double hz_tube_9 = (36.83 *cm)/2;

              G4Tubs* solidtube_9 =
                      new G4Tubs("tube_9",
                       innerRadius_tube_9,
                       outerRadius_tube_9,
                                hz_tube_9,
                      startAngle_HI_STORM,
                  spanningAngle_HI_STORM);

 //Logical volume
              G4LogicalVolume* logictube_9 =
                      new G4LogicalVolume(solidtube_9,  //its solid
                                                concrete,  //its material
                                             "tube_9");  //its name

 // Physical volume
          new G4PVPlacement(Rot_HI_STORM,  //no rotation
                           Object_tube_9,  //at position
                             logictube_9,  //its logical volume
                                "tube_9",  //its name
                            worldLogical,  //its mother  volume
                                   false,  //no boolean operation
                                       0,  //copy number
                          checkOverlaps);  //overlaps checking

 //############################################################################//

 //_______________________________This is the object that is being investigated//
 //############################################################################//
 //_______________________________________________________________Object_tube_10//

// G4ThreeVector Object_tube_10 =
//         G4ThreeVector((X_HI_STORM_ZERO +0. *cm),
//                       (Y_HI_STORM_ZERO +0. *cm),
//                       (Z_HI_STORM_ZERO +23.5 *cm)); //24.57

//              G4double innerRadius_tube_10 = 0.0 *cm;
//              G4double outerRadius_tube_10 = 80.0 *cm;
//              G4double hz_tube_10 = (345. *cm)/2;

//              G4Tubs* solidtube_10 =
//                      new G4Tubs("tube_10",
//                       innerRadius_tube_10,
//                       outerRadius_tube_10,
//                                hz_tube_10,
//                      startAngle_HI_STORM,
//                  spanningAngle_HI_STORM);

// //Logical volume
//              G4LogicalVolume* logictube_10 =
//                      new G4LogicalVolume(solidtube_10,  //its solid
//                                                    Pb,  //its material
//                                            "tube_10");  //its name

// // Physical volume
//          new G4PVPlacement(Rot_HI_STORM,  //no rotation
//                           Object_tube_10,  //at position
//                             logictube_10,  //its logical volume
//                                "tube_10",  //its name
//                            worldLogical,  //its mother  volume
//                                   false,  //no boolean operation
//                                       0,  //copy number
//                          checkOverlaps);  //overlaps checking

 //############################################################################//





   G4double dz1 =300*cm;
   G4int nsect1 =6;
   G4double dphi1=360*deg;
   G4double sphi1=60*deg;

   G4double dR = 13.51 * cm;


   std::vector<G4TwoVector> polygon1(nsect1);
  G4double ang1 = dphi1/nsect1;
  for (G4int i=0; i<nsect1; ++i)
  {
    G4double phi = i*ang1 + sphi1;
    G4double cosphi = std::cos(phi);
    G4double sinphi = std::sin(phi);
    polygon1[i].set(dR*cosphi,dR*sinphi);
  }



   G4RotationMatrix* Rot_prism= new G4RotationMatrix();
  Rot_prism->rotateZ(90*deg);

   G4TwoVector offsetA(0,0), offsetB(0,0);
   G4double scaleA = 1, scaleB = 1;
   G4VSolid* xtru = new G4ExtrudedSolid("Extru1", polygon1, dz1/2, offsetA, scaleA, offsetB, scaleB );


 auto detectorB
  = new G4LogicalVolume(xtru,
  uran,
 "Prisma");

 for (G4int copyNo=0; copyNo<2; copyNo++) {

      G4double firstPosition = -14*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(70.5*cm, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }

 for (G4int copyNo=0; copyNo<5; copyNo++) {

      G4double firstPosition = -55*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(47*cm, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }

 for (G4int copyNo=0; copyNo<5; copyNo++) {

      G4double firstPosition = -55*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(0, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }

 for (G4int copyNo=0; copyNo<6; copyNo++) {

      G4double firstPosition = -68.5*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(23.5*cm, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }

 for (G4int copyNo=0; copyNo<6; copyNo++) {

      G4double firstPosition = -68.5*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(-23.5*cm, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }

 for (G4int copyNo=0; copyNo<5; copyNo++) {

      G4double firstPosition = -55*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(-47*cm, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }

 for (G4int copyNo=0; copyNo<2; copyNo++) {

      G4double firstPosition = -14*cm;
      G4double gab = 27*cm;
      G4double Yposition = firstPosition + copyNo*gab;

            new G4PVPlacement(Rot_prism,
            G4ThreeVector(-70.5*cm, Yposition, 0.),
            detectorB,
            "Prisma",
            worldLogical,
            false,
            copyNo,
            checkOverlaps);
  }





   return worldPhysical;
  // G4cout << "Used material: "<<plateBoxLog->GetMaterial()->GetName()<<G4endl;
 }

void DetectorConstruction::ConstructSDandField()
{
  auto sdManager = G4SDManager::GetSDMpointer();
  G4String SDname;

  auto hodoscope1 = new HodoscopeSD(SDname="/hodoscope1");
  sdManager->AddNewDetector(hodoscope1);
  SetSensitiveDetector("worldBox", hodoscope1);

}
