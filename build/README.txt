-------------------------------------------------------------------

                            GScan project with parameterized source
                            --------------------

 This is an example of project with basic setups and can be used as a platform for muons simulations.
 This document discribes the geomerty, source and physics of this project and gives some tips how to run it.

 1 - GEOMETRY DEFINITION

The geometry is constructed in the DetectorConstruction class.
The setup consists of world box (11x11x11 m), four triple hodoscopes (200x100x0.4 cm) and investigating object - steel box (40x40x10 cm).  


2 - PHYSICS LIST
 
Reference physics list - QGSP_BERT. 

3 - PRIMARY GENERATOR

Parameterized source read from file musp-sl-sep2021-10mln-seed1055.dat
Source dimentions: 11.0 x 5.0 x 4.5 m.
The normalisation factor: 14093 muons per second.

4 - OUTPUT FILE

Contains ten columns:

"Event" "X" "Y" "Z" "Time" "Deposited Energy" "Track ID" "Detector plate number" "Kinetic Energy" "Particle type(PDG)".


4 - HOW TO COMPILE AND RUN

- Unpack the "GScan_parameterized";
- create the build folder (GScan_parameterized-build);
- open terminal in folder GScan_parameterized-build and type: cmake ../GScan_parameterized
- type: make 
- to run the project, type: ./execute (for visualization) or ./execute run.f (just simulation).
