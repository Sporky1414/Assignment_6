/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 6
*/

#include "FileIO.h"

//Default constructor: takes in user input itself.
FileIO::FileIO() {
  //Gets preliminary file path from user.
  inputFilePath = getInputFilePathFromUser();

  //Loops until the inputFilePath is valid.
  while(true) {
    //Attempts to setup the file reader.
    input.open(inputFilePath);

    //If the file input reader works/sees the file exists, it will then check if the file found is in the correct format.
    if(!input.fail()) {
      if(checkFileValidity()) {
        //File is valid, end loop.
        break;
      } else {
        //File is not in correct format. Reset input and try again.
        input.close();
        cout << "ERROR: File is in wrong format. Please try again." << endl;
        inputFilePath = getInputFilePathFromUser();
      }
    } else {
      //The file path entered by the user is not a valid file path. User is alerted of this and has to try again.
      input.close();
      cout << "ERROR: Invalid file path. Please try again." << endl;
      inputFilePath = getInputFilePathFromUser();
    }
  }

  counter = 1;
}

//Constructor: takes in string, then user input if string invalid.
FileIO::FileIO(string tempInputFilePath) {
  //Sets inputFilePath to the string passed in through constructor
  inputFilePath = tempInputFilePath;

  //Loops until the inputFilePath is valid.
  while(true) {
    //Attempts to setup the file reader.
    input.open(inputFilePath);

    //If the file input reader works/sees the file exists, it will then check if file is valid. If the file does not, the loop will continue until a valid filePath is entered.
    if(!input.fail()) {
      if(checkFileValidity()) {
        //File is valid, end loop.
        break;
      } else {
        //File is not in correct format. Reset input and try again.
        input.close();
        cout << "ERROR: File is in wrong format. Please try again." << endl;
        inputFilePath = getInputFilePathFromUser();
      }
    } else {
      //The file path entered by the user is not a valid file path. User is alerted of this and has to try again.
      input.close();
      cout << "ERROR: Invalid file path. Please try again." << endl;
      inputFilePath = getInputFilePathFromUser();
    }
  }

  counter = 1;
}

//Destructor: Closes the input stream
FileIO::~FileIO() {
  if(input.is_open()) {
    input.close();
  }
}

//Reads the next line of the input file.
string FileIO::readNextLine() {
  string tempString = "";
  getline(input, tempString);
  ++counter;
  return tempString;
}

//Returns if there is more data in the file to read.
bool FileIO::inputHasDataLeft() {
  return !input.eof();
}

//Takes in the input file path from the user. It is not error checked in this method.
string FileIO::getInputFilePathFromUser() {
  cout << "Enter File Path for Input." << endl;
  string tempPath = "";
  cin >> tempPath;
  return tempPath;
}

//Returns the line number of the file
int FileIO::getLineNumber() {
  return counter;
}

//Checks if the argument string can be converted to a decimal.
bool FileIO::checkIfStringIsDecimalNumber(string tempString) {
  //Bools for if a decimal point has been found or if the string is a num. Both set to false to start.
  bool decimalFound = false;
  bool isNum = false;
  //Iterates through each character of the string.
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      //Character is not a digit.
      if(!decimalFound && tempString[i] == '.') {
        //But it is a decimal point, and we still can have one of those. Set decimalFound to true. If a decimal point is found again, this if statement will be skipped for the else.
        decimalFound = true;
      } else {
        //Not a number so set isNum to false.
        isNum = false;
        break;
      }
    } else {
      //Digit found, so benefit of the doubt can be given that this will be a number. Set isNum to true (this can be reverse if later characters are not digits).
      isNum = true;
    }
  }
  return isNum;
}

//Checks if the argument string can be converted to an integer.
bool FileIO::checkIfStringIsNumber(string tempString) {
  //Iterates through string to make sure each character can be converted to a digit. If any character is not a digit, false is returned.
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      return false;
    }
  }
  //All characters in the string are digits, so return true.
  return true;
}

//Checks if file is a valid file for this assignment.
bool FileIO::checkFileValidity() {
  //First line must be the length of the array containing the data, so it must be an integer. Otherwise, the file is invalid.
  string tempString = readNextLine();
  if(!checkIfStringIsNumber(tempString)) {
    return false;
  }
  //Store the number of doubles into a temporary int. Create a counter to count the number of doubles found.
  int counter = 0;
  int numOfDoubles = 0;
  stringstream numOfDoublesConverter(tempString);
  numOfDoublesConverter >> numOfDoubles;
  numOfDoublesConverter.clear();
  //Remaining data must be doubles, so each line is check to ensure they are doubles and not something else. Otherwise, the file is invalid. Counter is incremented for every double found.
  while(inputHasDataLeft()) {
    if(!checkIfStringIsDecimalNumber(readNextLine())) {
      return false;
    } else {
      ++counter;
    }
  }
  //The counter, after checking each line, should be the same as numOfDoubles if the file is valid. If this is not the case, the user is alerted of the discreptancy and false is returned.
  if(counter != numOfDoubles) {
    cout << "Expected Entries: " << numOfDoubles << endl;
    cout << "Doubles Found: " << counter << endl;
    return false;
  }
  //File is valid if this point is reached. Reset file reader and return TRUE.
  input.clear();
  input.seekg(0);
  return true;
}
