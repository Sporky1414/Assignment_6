#include "Sorter.h"
#include "FileIO.h"


using namespace std;

class Simulation {
  public:
    Simulation();
    Simulation(string filePath);
    ~Simulation();

    void run();

  private:
    double* sortData(int numOfSort);
    void setupSimulation();

    FileIO* inputFile;
    Sorter* sorter;
};
