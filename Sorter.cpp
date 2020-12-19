#include "Sorter.h"

using namespace std;

Sorter::Sorter() {
  originalArray = new double[10];
  srand(time(NULL));
  for(int i = 0; i < 10; ++i) {
    int temp = 1 + rand()/((RAND_MAX)/100);
    originalArray[i] = temp;
  }
  arrSize = 10;
}

Sorter::Sorter(double* tempArray, int arraySize) {
  originalArray = tempArray;
  arrSize = arraySize;
}

Sorter::~Sorter() {
  delete originalArray;
}

double* Sorter::BubbleSort() {
  double* tempArray = getCopyOfOriginalArray();
  for(int i = 0; i < arrSize; ++i) {
    double temp = 0;
    for(int j = 0; j < arrSize - i - 1; ++j) {
      if(tempArray[j] > tempArray[j + 1]) {
        temp = tempArray[j+1];
        tempArray[j+1] = tempArray[j];
        tempArray[j] = temp;
      }
    }
  }
  return tempArray;
}

double* Sorter::SelectionSort() {
  double* tempArray = getCopyOfOriginalArray();
  int indexSmallest = 0;
  double temp = 0;
  for(int i = 0; i < arrSize - 1; ++i) {
    indexSmallest = i;
    for(int j = i + 1; j < arrSize; ++j) {
      if(tempArray[j] < tempArray[indexSmallest]) {
        indexSmallest = j;
      }
    }
    temp = tempArray[i];
    tempArray[i] = tempArray[indexSmallest];
    tempArray[indexSmallest] = temp;
  }
  return tempArray;
}

double* Sorter::InsertionSort() {
  double* tempArray = getCopyOfOriginalArray();
  double temp = 0;
  int j = 0;
  for(int i = 1; i < arrSize; ++i) {
    j = i;
    while(j > 0 && tempArray[j] < tempArray[j-1]) {
      temp = tempArray[j];
      tempArray[j] = tempArray[j - 1];
      tempArray[j-1] = temp;
      --j;
    }
  }
  return tempArray;
}

double* Sorter::QuickSort() {
  double* tempArray = getCopyOfOriginalArray();
  return QuickSortRec(tempArray, 0, arrSize - 1);
}

double* Sorter::QuickSortRec(double* tempArray, int lowIndex, int highIndex) {
  if(lowIndex >= highIndex) {
    return tempArray;
  }
  int lowEndIndex = partition(tempArray, lowIndex, highIndex);
  QuickSortRec(tempArray, lowIndex, lowEndIndex);
  QuickSortRec(tempArray, lowEndIndex + 1, highIndex);
  return tempArray;
}

int Sorter::partition(double* tempArray, int lowIndex, int highIndex) {
  int midpoint = lowIndex + (highIndex-lowIndex)/2;
  double pivot = tempArray[midpoint];
  while(true) {
    while(tempArray[lowIndex] < pivot) {
      ++lowIndex;
    }
    while(tempArray[highIndex] > pivot) {
      highIndex--;
    }
    if(lowIndex >= highIndex) {
      return highIndex;
    } else {
      double temp = tempArray[lowIndex];
      tempArray[lowIndex] = tempArray[highIndex];
      tempArray[highIndex] = temp;
      ++lowIndex;
      highIndex--;
    }
  }
}

double* Sorter::MergeSort() {
  double* tempArray = getCopyOfOriginalArray();
  return MergeSortRec(tempArray, 0, arrSize - 1);
}

double* Sorter::MergeSortRec(double* tempArray, int lowIndex, int highIndex) {
  int midpoint = 0;
  if(lowIndex < highIndex) {
    midpoint = (lowIndex + highIndex)/2;
    MergeSortRec(tempArray, lowIndex, midpoint);
    MergeSortRec(tempArray, midpoint+1, highIndex);
    Merge(tempArray, lowIndex, midpoint, highIndex);
  }
  return tempArray;
}

double* Sorter::Merge(double* tempArray, int lowIndex, int midpoint, int highIndex) {
  int mergedSize = highIndex - lowIndex + 1;
  int mergePos = 0;
  int leftPos = lowIndex;
  int rightPos = midpoint + 1;
  double* mergedArray = new double[mergedSize];
  while(leftPos <= midpoint && rightPos <= highIndex) {
    if(tempArray[leftPos] <= tempArray[rightPos]) {
      mergedArray[mergePos] = tempArray[leftPos];
      ++leftPos;
    } else {
      mergedArray[mergePos] = tempArray[rightPos];
      ++rightPos;
    }
    ++mergePos;
  }
  while(leftPos <= midpoint) {
    mergedArray[mergePos] = tempArray[leftPos];
    ++leftPos;
    ++mergePos;
  }
  while(rightPos <= highIndex) {
    mergedArray[mergePos] = tempArray[rightPos];
    ++rightPos;
    ++mergePos;
  }
  for(mergePos = 0; mergePos < mergedSize; ++ mergePos) {
    tempArray[lowIndex + mergePos] = mergedArray[mergePos];
  }
  return tempArray;
}

double* Sorter::getCopyOfOriginalArray() {
  double* tempArray = new double[arrSize];
  for(int i = 0; i < arrSize; ++i) {
    tempArray[i] = originalArray[i];
  }
  return tempArray;
}

int Sorter::getLengthOfArray() {
  return arrSize;
}
