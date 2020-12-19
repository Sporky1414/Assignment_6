#include "Simulation.h"

Simulation::Simulation() {
  inputFile = new FileIO();
  setupSimulation();
}

Simulation::Simulation(string filePath) {
  inputFile = new FileIO(filePath);
  setupSimulation();
}

Simulation::~Simulation() {
  delete inputFile;
  delete sorter;
}

void Simulation::run() {
  cout << "NUM OF ITEMS BEING SORTED: " << sorter->getLengthOfArray() << endl;
  time_t copyTimerStart;
  double copySecondsStart = time(&copyTimerStart);
  double* tempArray = sorter->getCopyOfOriginalArray();
  time_t copyTimerEnd;
  double copySecondsEnd = time(&copyTimerEnd);
  delete tempArray;
  cout << "Seconds needed to copy array for sorting: " << (copySecondsEnd - copySecondsStart) << " seconds\n" << endl;
  for(int i = 0; i < 5; ++i) {
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
    time_t sortTimerStart;
    double sortSecondsStart = time(&sortTimerStart);
    cout << "Time Sort Started: " << time(&sortTimerStart) << endl;
    tempArray = sortData(i);
    time_t sortTimerEnd;
    double sortSecondsEnd = time(&sortTimerEnd);
    cout << "Time Sort Ended: " << time(&sortTimerStart) << endl;
    delete tempArray;
    cout << "Time Spent On Sort: " << (sortSecondsEnd - sortSecondsStart) << " seconds" << endl;
    cout << "Time Spent On Sort With Copying Factored Out: " << (sortSecondsEnd - sortSecondsStart - (copySecondsEnd - copySecondsStart)) << " seconds" << endl;
    cout << "\n\n" << endl;
  }
}

double* Simulation::sortData(int numOfSort) {
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

void Simulation::setupSimulation() {
  string tempString = inputFile->readNextLine();
  stringstream stringToNumConverter(tempString);
  int lengthOfArray = 0;
  stringToNumConverter >> lengthOfArray;
  stringToNumConverter.clear();
  double* tempArray = new double[lengthOfArray];
  for(int i = 0; i < lengthOfArray; ++i) {
    tempString = inputFile->readNextLine();
    stringToNumConverter.str(tempString);
    double tempDouble = 0.0;
    stringToNumConverter >> tempDouble;
    tempArray[i] = tempDouble;
    stringToNumConverter.clear();
  }
  sorter = new Sorter(tempArray, lengthOfArray);
}
