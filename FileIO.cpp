/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 3
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

    //If the file input reader works/sees the file exists, it will end the loop.
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

bool FileIO::checkIfStringIsNumber(string tempString) {
  for(int i = 0; i < tempString.length(); ++i) {
    if(!isdigit(tempString[i])) {
      return false;
    }
  }
  return true;
}

//Checks if file is a valid file for this assignment.
bool FileIO::checkFileValidity() {
  if(!checkIfStringIsNumber(readNextLine())) {
    return false;
  }
  while(inputHasDataLeft()) {
    if(!checkIfStringIsDecimalNumber(readNextLine())) {
      return false;
    }
  }
  //All file values are doubles. Reset file reader and return TRUE.
  input.clear();
  input.seekg(0);
  return true;
}
