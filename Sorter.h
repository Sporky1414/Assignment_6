#include <string>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

class Sorter {
  public:
    Sorter();
    Sorter(double* tempArray, int arraySize);
    ~Sorter();

    double* BubbleSort();
    double* SelectionSort();
    double* InsertionSort();
    double* MergeSort();
    double* QuickSort();

    double* getCopyOfOriginalArray();
    int getLengthOfArray();

  private:
    int partition(double* tempArray, int lowIndex, int highIndex);
    double* QuickSortRec(double* tempArray, int lowIndex, int highIndex);

    double* Merge(double* tempArray, int lowIndex, int midpoint, int highIndex);
    double* MergeSortRec(double* tempArray, int lowIndex, int highIndex);

    double* originalArray;
    int arrSize;
};
