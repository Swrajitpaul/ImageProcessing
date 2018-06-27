#include <iostream>
#include <fstream>
using namespace std;

int numRows;
int numCols;
int minVal;
int maxVal;

int main(int argc, char *argv[])
{
  
  string outputFile = argv[1];

  outputFile += "_PP";

  ifstream inFile(argv[1]);
 
  ofstream outFile(outputFile);
  
  inFile >> numRows;
  
  inFile >> numCols;
  
  inFile >> minVal;
  
  inFile >> maxVal;
  
  outFile << numRows;
  outFile << " ";
  outFile << numCols;
  outFile << " ";
  outFile << minVal;
  outFile << " ";
  outFile << maxVal;
  outFile << " ";

  for (int i =0; i < numRows; i++){
  	for (int j = 0; j < numCols; j++){
  		int value;
  		inFile >> value;
		if (value > 0){
			outFile << value;
		} 
		else {
			outFile << "  ";
		}
	  }
	  outFile << endl;
  }

  inFile.close();
  outFile.close();
  
  return 0;
}

