#include <iostream>
#include <fstream>
using namespace std;

int numRows;
int numCols; 
int minVal;
int maxVal;
int thrValue; 
string outFileName; 
         
string generateOutFileName(string tv){  
   string temp = "Proj1_data1_thr_" + tv;
   return temp;
}     

int main(int argc, char *argv[])
{
  ifstream inFile(argv[1]);
   
  inFile >> numRows; 
  
  inFile >> numCols;
    
  inFile >> minVal;
    
  inFile >> maxVal; 

  cout << "Enter the threshold value";

  cout << endl;
  
  string temp;
  cin >> temp;

  thrValue = atoi(temp.c_str());

  outFileName = generateOutFileName(temp);

  cout<< endl;

  ofstream outFile(outFileName);

  outFile << numRows;
  outFile << " ";
  outFile << numCols;
  outFile << " ";
  outFile << 0;
  outFile << " ";
  outFile << 1;
  outFile << "\n";

  for(int i = 0; i < numRows; i++) {
    for(int j=0; j < numCols; j++){
      int temp;
      inFile >> temp;
      if(temp >= thrValue){
      outFile << "1 ";
      }
      else {
      outFile << "0 ";
      }
    }
   outFile << endl;
  }
  
  inFile.close();
  outFile.close();
  
  return 0;
}



