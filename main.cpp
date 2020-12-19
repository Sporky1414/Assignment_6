#include "Simulation.h"


using namespace std;

int main (int argc, char** argv) {
  Simulation* simulation;
  if(argc < 2) {
    cout << "You did not enter a command line argument. Please enter the file path when prompted." << endl;
    simulation = new Simulation();
  } else {
    simulation = new Simulation(argv[1]);
  }
  simulation->run();
  delete simulation;
  return 0;
}
