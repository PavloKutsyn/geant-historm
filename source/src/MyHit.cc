#include "MyHit.hh"

MyHit::MyHit(G4int id)
    :G4VHit(), fId(id), fLocalPos(G4ThreeVector()),
      fWorldPos(G4ThreeVector())
{

}
MyHit::~MyHit()
{

}

// ? right.fPos
 MyHit::MyHit (const MyHit &right)
    : G4VHit(), fLocalPos(right.fLocalPos),
      fWorldPos(right.fWorldPos)
{}

 const MyHit& MyHit::operator=(const MyHit &right)

 {
     fLocalPos = right.fLocalPos;
     fWorldPos = right.fWorldPos;
return *this;
 }

 int MyHit::operator==(const MyHit &/*right*/) const
 {
   return 0;
 }


void MyHit::Print()
{}
