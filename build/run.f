/run/initialize
##### CRY SETUPS #####
/CRY/input returnNeutrons 0
/CRY/input returnProtons 0
/CRY/input returnGammas 0
/CRY/input returnPions 0
/CRY/input returnMuons 1
/CRY/input returnElectrons 0
/CRY/input returnKaons 0
/CRY/input date 1-24-2017
/CRY/input latitude 59.24
/CRY/input altitude 0
/CRY/input subboxLength 4
/CRY/update
/event/verbose 0
/tracking/verbose 0
/control/verbose 0
/run/printProgress 1
/process/em/verbose 0
/analysis/setFileName Histo 2d
/analysis/h2/setX 0 200 -200 200 cm
/analysis/h2/setY 0 200 -200 200 cm
/run/beamOn 1000000

