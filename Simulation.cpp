/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 6
*/

#include "Simulation.h"

//Default Constructor: Creates the inputFile object from the default FileIO constructor and runs setupSimulation()
Simulation::Simulation() {
  inputFile = new FileIO();
  setupSimulation();
}

//Constructor: Creates the inputFile object from the FileIO constructor that takes in the input file path. Then runs setupSimulation() to finish constructing the class.
Simulation::Simulation(string filePath) {
  inputFile = new FileIO(filePath);
  setupSimulation();
}

//Destructor: Deletes the sorter object and the inputFile object.
Simulation::~Simulation() {
  delete inputFile;
  delete sorter;
}

//Runs the actual simulation.
void Simulation::run() {
  //Prints the number of items being sorted.
  cout << "NUM OF ITEMS BEING SORTED: " << sorter->getLengthOfArray() << endl;
  //The actual sorting is done in this loop.
  for(int i = 4; i >= 0; i--) {
    //Prints the name of the sort based on which loop iteration this is (from 4-0 inclusive).
    cout << "Name of Sort: " ;
    switch(i) {
      case 0:
        cout << "Bubble Sort" << endl;
        break;
      case 1:
        cout << "Selection Sort" << endl;
        break;
      case 2:
        cout << "Insertion Sort" << endl;
        break;
      case 3:
        cout << "Quick Sort" << endl;
        break;
      default:
        cout << "Merge Sort" << endl;
        break;
    }
    //Gets the starting time of the given sort and prints it.
    time_t sortTimerStart;
    double sortSecondsStart = time(&sortTimerStart);
    cout << "Time Sort Started: " << time(&sortTimerStart) << endl;
    //Calls the sortData method, based on the loop iteration number, to execute the specified sort.
    double* tempArray = sortData(i);
    //Gets the end time of the given sort and prints it.
    time_t sortTimerEnd;
    double sortSecondsEnd = time(&sortTimerEnd);
    cout << "Time Sort Ended: " << time(&sortTimerStart) << endl;
    //Temp array, which holds the results of the sort, is deleted to clear out memory.
    delete tempArray;
    //Difference between the start and end times is printed in seconds.
    cout << "Time Spent On Sort: " << (sortSecondsEnd - sortSecondsStart) << " seconds" << endl;
    cout << "\n\n" << endl;
  }
  //All sorting is completed.
  cout <<"Sorting simulation complete." << endl;
}

//Sorts a copy of the data stored in sorter using the specified sorting algorithm.
double* Simulation::sortData(int numOfSort) {
  //Using the same key as in run(), the function calls the corresponding sort method in sorter and returns the results.
  switch(numOfSort) {
    case 0:
      return sorter->BubbleSort();
      break;
    case 1:
      return sorter->SelectionSort();
      break;
    case 2:
      return sorter->InsertionSort();
      break;
    case 3:
      return sorter->QuickSort();
      break;
    default:
      return sorter->MergeSort();
      break;
  }
}

//Sets up the simulation class (used in conjunction with the constructors)
void Simulation::setupSimulation() {
  //Takes in the number of items to be sorted from the file (file validity has been checked during the creation of the inputFile object, so this first line will be an integer)
  string tempString = inputFile->readNextLine();
  stringstream stringToNumConverter(tempString);
  int lengthOfArray = 0;
  stringToNumConverter >> lengthOfArray;
  stringToNumConverter.clear();
  //Creates the array to store the data using the length found before.
  double* tempArray = new double[lengthOfArray];
  for(int i = 0; i < lengthOfArray; ++i) {
    //Copies all data from the file into the array using this loop.
    tempString = inputFile->readNextLine();
    stringToNumConverter.str(tempString);
    double tempDouble = 0.0;
    stringToNumConverter >> tempDouble;
    tempArray[i] = tempDouble;
    stringToNumConverter.clear();
  }
  //Creates the sorter object from the new array and the length of said array.
  sorter = new Sorter(tempArray, lengthOfArray);
}
