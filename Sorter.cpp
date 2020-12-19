/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 6
*/

#include "Sorter.h"

using namespace std;

//Default Constructor: Builds the array using 100000 random integers.
Sorter::Sorter() {
  //Initializes the array with 100000 spots.
  originalArray = new double[100000];
  //Seeds the random number generator.
  srand(time(NULL));
  //Randomly generates 100000 integers (up to 100) for the array and stores them.
  for(int i = 0; i < 100000; ++i) {
    int temp = 1 + rand()/((RAND_MAX)/100);
    originalArray[i] = temp;
  }
  //Sets the array length to temp.
  arrSize = 100000;
}

//Constructor: Sets originalArray to point to tempArray. arrSize is set to the value of arraySize.
Sorter::Sorter(double* tempArray, int arraySize) {
  originalArray = tempArray;
  arrSize = arraySize;
}

//Deletes the original array.
Sorter::~Sorter() {
  delete originalArray;
}

//Executes the Bubble Sort sorting algorithm on a copy of originalArray
double* Sorter::BubbleSort() {
  //Copies the original array.
  double* tempArray = getCopyOfOriginalArray();
  //Main sorting loop: First loop runs through the algorithm the same number of times as there are data points in the array.
  for(int i = 0; i < arrSize; ++i) {
    double temp = 0;
    //Second sorting loop: Iterates through each number in the array, except those on top that have already been sorted (found by subtracting i from the array length)
    for(int j = 0; j < arrSize - i - 1; ++j) {
      //Checks if the item one index above j is less than the item stored at j. If so, they are swapped. At the end of this loop, the largest number still not sorted will have been "bubbled" to the correct spot in the array.
      if(tempArray[j] > tempArray[j + 1]) {
        temp = tempArray[j+1];
        tempArray[j+1] = tempArray[j];
        tempArray[j] = temp;
      }
    }
  }
  //Array is sorted, so return the finished array.
  return tempArray;
}

//Executes the Selection Sort sorting algorithm on a copy of originalArray
double* Sorter::SelectionSort() {
  //Copies the original array.
  double* tempArray = getCopyOfOriginalArray();
  //Initializes two values, one  to hold where the index of the next smallest item in the array, and one used for swapping.
  int indexSmallest = 0;
  double temp = 0;
  //Main sorting loop: Must loop through the array as many times as there are numbers in array minus 1 (that last one is not needed, since that last number must be sorted if everything else is already). I is also noted as where the next smallest element must go.
  for(int i = 0; i < arrSize - 1; ++i) {
    //Sets the current indexSmallest to whatever i is (which is where the next smallest element must go)
    indexSmallest = i;
    //Second sorting loop: Checks each element above i (including the final element) to see if it is smaller than whatever is currently stored in indexSmallest.
    for(int j = i + 1; j < arrSize; ++j) {
      if(tempArray[j] < tempArray[indexSmallest]) {
        //If a new smallest is found, indexSmallest is updated to reflect the index where it was found (j)
        indexSmallest = j;
      }
    }
    //Swap the item in i (where the next smallest should be) for whatever is stored at indexSmallest (where the actual next smallest is)
    temp = tempArray[i];
    tempArray[i] = tempArray[indexSmallest];
    tempArray[indexSmallest] = temp;
  }
  //Sorting complete, return sorted array.
  return tempArray;
}

//Executes the Insertion Sort sorting algorithm on a copy of originalArray
double* Sorter::InsertionSort() {
  //Copies the original array.
  double* tempArray = getCopyOfOriginalArray();
  //Temp value is used for swapping. J holds the second loop counter (which is not a for loop due to the need for two conditions)
  double temp = 0;
  int j = 0;
  //Iterates through whole loop with the main loop (except first element)
  for(int i = 1; i < arrSize; ++i) {
    //j is set to i, since everything before i is already in order amongst itself (this includes index 0 when i = 1, since a one index partion of an array is sorted already)
    j = i;
    //Second loop: Iterates through in-order section (or partition) of array (which is before i) to insert whatever is stored at index i into its correct position in the sorted partition.
    while(j > 0 && tempArray[j] < tempArray[j-1]) {
      //The item stored at j is bubbled down the sorted partition from the top until the correct spot in the array is found (which is when one of the two while loop conditions return false).
      temp = tempArray[j];
      tempArray[j] = tempArray[j - 1];
      tempArray[j-1] = temp;
      --j;
    }
  }
  //Return the now sorted array.
  return tempArray;
}

//Executes the Quick Sort algorithm.
double* Sorter::QuickSort() {
  //Copies the original array.
  double* tempArray = getCopyOfOriginalArray();
  //Calls recursive helper method QuickSortRec to sort the actual array.
  return QuickSortRec(tempArray, 0, arrSize - 1);
}

//Quick Sort Helper Recursive Method: Takes in the array, the low index of the partition to be sorted, and the high index of the partition of tempArray to be sorted.
double* Sorter::QuickSortRec(double* tempArray, int lowIndex, int highIndex) {
  if(lowIndex >= highIndex) {
    //If lowIndex >= highIndex, then the array is already sorted and nothing needs to be done.
    return tempArray;
  }
  //LowEndIndex is found by the partition method. It is used to split tempArray into it's partitions.
  int lowEndIndex = partition(tempArray, lowIndex, highIndex);
  //Recursively calls QuickSortRec on the two partitions, using lowEndIndex as the midpoint to split the two partitions.
  QuickSortRec(tempArray, lowIndex, lowEndIndex);
  QuickSortRec(tempArray, lowEndIndex + 1, highIndex);
  //The partition found by the partition() method is sorted at this point, so the sorted array is returned.
  return tempArray;
}

//Quick Sort Helper Method: Determines the partitions to be used for the Quick Sort by finding the midpoint to split the array at.
int Sorter::partition(double* tempArray, int lowIndex, int highIndex) {
  //Finds the current midpoint of the array partition being partitioned (low index and high index note this partition in the main array)
  int midpoint = lowIndex + (highIndex-lowIndex)/2;
  //The pivot point (what value determines which items will go in the partition) is found at the midpoint.
  double pivot = tempArray[midpoint];
  //Loops until the correct partition points are found.
  while(true) {
    //Goes through the array until it finds the earliest point before the pivot point (but after whatever lowIndex originally was) that is less than pivot. That becomes lowIndex.
    while(tempArray[lowIndex] < pivot) {
      ++lowIndex;
    }
    //Goes through the array until it finds the latest point after pivot (but before whatever highIndex originally was) that contains a value higher than the pivot value. This becomes highIndex.
    while(tempArray[highIndex] > pivot) {
      highIndex--;
    }
    //If the lowIndex is found to be higher than the highIndex, we can return highIndex, since that becomes the midpoint of the new partitions to use in QuickSortRec (and through the else statement below, we know that all the data before/after the highIndex is less than/greater than pivot (respectively))
    if(lowIndex >= highIndex) {
      return highIndex;
    } else {
      //LowIndex is smaller than highIndex, so we have to keep going. But first, we swap the values stored at high/low index so that the new partitions will indeed have values greater than/less than the pivot point in the respective partitions.
      double temp = tempArray[lowIndex];
      tempArray[lowIndex] = tempArray[highIndex];
      tempArray[highIndex] = temp;
      ++lowIndex;
      highIndex--;
    }
  }
}

//Executes the Merge Sort sorting algorithm on a copy of originalArray
double* Sorter::MergeSort() {
  //Copies originalArray to tempArray.
  double* tempArray = getCopyOfOriginalArray();
  //Calls the recursive MergeSortRec helper function on the entire array and returns the result.
  return MergeSortRec(tempArray, 0, arrSize - 1);
}

//Merge Sort Recursive Helper Method: Main job of this recursive method is to break apart the original array into smaller copies until each datapoint of the array is stored in its own array.
double* Sorter::MergeSortRec(double* tempArray, int lowIndex, int highIndex) {
  int midpoint = 0;
  //Checks that the partitioning mentioned with lowIndex/highIndex is correct (and a partition can be made from the section of tempArray between lowIndex and highIndex)
  if(lowIndex < highIndex) {
    //The midpoint of the partition is found
    midpoint = (lowIndex + highIndex)/2;
    //Recursively split the array into smaller segments with these two calls to MergeSortRec on the right and left sides of the array at midpoint.
    MergeSortRec(tempArray, lowIndex, midpoint);
    MergeSortRec(tempArray, midpoint+1, highIndex);
    //Merges the partitions found above with Merge.
    Merge(tempArray, lowIndex, midpoint, highIndex);
  }
  //Returns the now sorted array (or at least tempArray with the partitions mentioned in the ifStatement sorted)
  return tempArray;
}

//Helper Method that recombines two partitions, denoted by the indexes passed as arguments.
double* Sorter::Merge(double* tempArray, int lowIndex, int midpoint, int highIndex) {
  //Finds the size of the array partition.
  int mergedSize = highIndex - lowIndex + 1;
  //Sets up counters for use in merging.
  int mergePos = 0;
  int leftPos = lowIndex;
  int rightPos = midpoint + 1;
  //Creates the mergedArray to store the merged partition.
  double* mergedArray = new double[mergedSize];
  //Main sorting loop: Loops through the tempArray parition until either the partition on the left of midpoint or the partition on right of midpoint has been entirely added to mergedArray.
  while(leftPos <= midpoint && rightPos <= highIndex) {
    //Checks if the array item stored at leftPos (which is the next smallest item of the partition) is less than/equal to the next smallest item of the right partition (noted by rightPos). These partitions, if they get here, are sorted already.
    if(tempArray[leftPos] <= tempArray[rightPos]) {
      //The data stored at leftPos in tempArray is stored in the merged array at mergePos (which holds where the next smallest element between the right/left paritions is to be stored in mergedArray). LeftPos is incremented to move to the next smallest value of the left partition (if one exists)
      mergedArray[mergePos] = tempArray[leftPos];
      ++leftPos;
    } else {
      //The data stored at rightPos in tempArray is stored in the merged array array at mergePos (which holds where the next smallest element between the right/left paritions is to be stored in mergedArray). RightPos is incremented to move to the next smallest value of the right partition (if one exists)
      mergedArray[mergePos] = tempArray[rightPos];
      ++rightPos;
    }
    //Merge pos is incremented.
    ++mergePos;
  }
  //If the right partition of tempArray has been fully added to mergedArray before the left partition finishes, the rest of the left partition is added to merged array (The remaining data is in order and greater than the biggest value in the original right partition)
  while(leftPos <= midpoint) {
    mergedArray[mergePos] = tempArray[leftPos];
    ++leftPos;
    ++mergePos;
  }
  //If the left partition of tempArray has been fully added to mergedArray before the right partition finishes, the rest of the right partition is added to merged array (The remaining data is in order and greater than the biggest value in the original left partition)
  while(rightPos <= highIndex) {
    mergedArray[mergePos] = tempArray[rightPos];
    ++rightPos;
    ++mergePos;
  }
  //The sorted data of merged array replaces the unsorted data in the partition of tempArray that contains the original right/left partitions.
  for(mergePos = 0; mergePos < mergedSize; ++ mergePos) {
    tempArray[lowIndex + mergePos] = mergedArray[mergePos];
  }
  //Temp array is returned with the newly sorted partition included.
  return tempArray;
}

//Copies originalArray into a new array and returns it.
double* Sorter::getCopyOfOriginalArray() {
  //Creates the new array for the new data.
  double* tempArray = new double[arrSize];
  //Copies the data of originalArray into tempArray.
  for(int i = 0; i < arrSize; ++i) {
    tempArray[i] = originalArray[i];
  }
  //Returns the new copy.
  return tempArray;
}

//Getter for arrSize;
int Sorter::getLengthOfArray() {
  return arrSize;
}
