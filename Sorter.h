/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 6
*/

#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

//A class that takes in an array of doubles and returns sorted copies of the array, using the specified sorting algorithms.
class Sorter {
  public:
    //Constructors/Destructor
    Sorter();
    Sorter(double* tempArray, int arraySize);
    ~Sorter();

    //Main sorting algorithms.
    double* BubbleSort();
    double* SelectionSort();
    double* InsertionSort();
    double* MergeSort();
    double* QuickSort();

    //Getters for arrSize and a deep copy of originalArray.
    double* getCopyOfOriginalArray();
    int getLengthOfArray();

  private:
    //Helper methods for QuickSort
    int partition(double* tempArray, int lowIndex, int highIndex);
    double* QuickSortRec(double* tempArray, int lowIndex, int highIndex);

    //Helper methods for MergeSort
    double* Merge(double* tempArray, int lowIndex, int midpoint, int highIndex);
    double* MergeSortRec(double* tempArray, int lowIndex, int highIndex);

    //The original, unsorted array data is stored in originalArray while the array's size is stored in arrSize.
    double* originalArray;
    int arrSize;
};
