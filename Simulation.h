/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 6
*/

#include "Sorter.h"
#include "FileIO.h"


using namespace std;

//A class that runs the sorting simulation for this program.
class Simulation {
  public:
    //Constructors/Destructor
    Simulation();
    Simulation(string filePath);
    ~Simulation();

    //Main run method that handles the actual simulation of the program.
    void run();

  private:
    //Private method to call on the correct sorting algorithm during each iteration of the loop in run()
    double* sortData(int numOfSort);

    //Helper method for the Simulation constructors to setup sorter.
    void setupSimulation();

    //FileIO object to read the file with the data and a sorter object to sort through said data.
    FileIO* inputFile;
    Sorter* sorter;
};
