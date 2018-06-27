#include <iostream>
#include <fstream>
using namespace std;

ifstream inFile; 
ofstream outFile; 
ofstream outFiletwo;
ofstream outFilethree;

class boundaryPt{

	public:
		int x;
		int y;
		double curvature;
		int localMax;
		int corner;
		
		boundaryPt(){
		}
};
class image{
	
	public:
		
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
			
		int** imgAry;
		
		int rows; // numRows +2 
		int cols; // numCols +2
	
		image(string in, string out1, string out2, string out3){
			
			// opens input and output files
  			inFile.open(in.c_str());
  			
			outFile.open(out1.c_str());
  			
			outFiletwo.open(out2.c_str());
			
			outFiletwo.open(out3.c_str());
  
  			// stores the values 
		    
			inFile >> numRows;
		
		    inFile >> numCols;
		
		    inFile >> minVal;
		
		    inFile >> maxVal;
  
		    rows = numRows + 2;
			
			cols = numCols +2;
			  
			outFile << numRows;
  			outFile << " ";
  			outFile << numCols;
  			outFile << " ";
  			outFile << minVal;
  			outFile << " "; 
  			outFile << maxVal;
  			outFile << endl;
  			
  			outFiletwo << numRows;
  			outFiletwo << " ";
  			outFiletwo << numCols;
  			outFiletwo << " ";
  			outFiletwo << minVal;
  			outFiletwo << " "; 
  			outFiletwo << maxVal;
  			outFiletwo << endl;
  			
			//  initializes the image array 
			imgAry = new int*[rows];
			for(int i = 0; i < rows; i++)
			    imgAry[i] = new int[cols];
		}
				

};
	
class kCurvature {
	
	public:
		int K;
		int numPts;
		
		int beginIndex = 0;
		int Q = 0;
		int P = K;
		int R = 2*K;
		
		
		void countPts(){
			
		}
		
		void PtAry(boundaryPt *){
			
		}
		
		void printPtAry(){
			
		}
		
		void storePt(x, y, index){
			
		}
		
		void computeCurvature(Q, P, R){
			
		}
		
		void computeLocalMaxima(PtAry){
			
		}
		
		void setCorner(PtAry){
			
		}
			
};

int main(int argc, char *argv[]){
  	
  	// this will create an object, loads image and zeroframes.
	image img(argv[1], argv[2], argv[3], argv[4]);
	
	return 0;
}

