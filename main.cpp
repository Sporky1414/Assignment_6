/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 6
*/

#include "Simulation.h"


using namespace std;

//Main method to run our sorting simulation.
int main (int argc, char** argv) {
  //Simulation object runs the simulation outside the main method.
  Simulation* simulation;
  //Simulation object is created depending on if the user inputted a file path as a command line argument.
  if(argc < 2) {
    cout << "You did not enter a command line argument. Please enter the file path when prompted." << endl;
    simulation = new Simulation();
  } else {
    simulation = new Simulation(argv[1]);
  }
  //Simulation runs, then is deleted once the simulation has finished. 0 is returned and the program ends afterwards.
  simulation->run();
  delete simulation;
  return 0;
}
