#include <iostream>
#include <fstream>
using namespace std;

class distanceTransform {
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;	
	int** zeroFramedAry;
	int NeighborAry[4];
	
	int rows; // numRows +2 
	int cols; // numCols +2
	
	ifstream inFile;
  	ofstream outFile;
  	ofstream outFiletwo;
	
	public:
		distanceTransform(string in, string out1, string out2){

  			inFile.open(in);
  			outFile.open(out1);
  			outFiletwo.open(out2);
  
  			// opens input and output files
  
		    inFile >> numRows;
		
		    inFile >> numCols;
		
		    inFile >> minVal;
		
		    inFile >> maxVal;
		  
		    // stores the values 
  
		    rows = numRows + 2;
			cols = numCols +2;
			  
			//  initializes the array 
			zeroFramedAry = new int*[rows];
			for(int i = 0; i < rows; i++)
			    zeroFramedAry[i] = new int[cols];
			    
			newMin =99999;
  			newMax =0;
		}
				
		void loadImage(){
			// loads the data into the array
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		      		int temp;
		      		inFile >> temp;
		      		zeroFramedAry[i][j] = temp;
		    	}
		  	}
		} // loads the img into the array
		
		void zeroFramed(){
		  for(int i= 1; i < numCols + 1; i++) {
		    zeroFramedAry[0][i] = 0;
		    zeroFramedAry[numRows+1][i] = 0;
		  }
		  for(int i= 0; i < numRows + 2; i++) {
		    zeroFramedAry[i][0] = 0;
		    zeroFramedAry[i][numCols+1] = 0;
		  }
		} // zeroFrame
		
		void loadNeighbors(int i, int j, int pass) {
		  if(pass == 1){
		  	NeighborAry[0] = zeroFramedAry[i-1][j-1];
		  	NeighborAry[1] = zeroFramedAry[i-1][j];
		  	NeighborAry[2] = zeroFramedAry[i-1][j+1];
		  	NeighborAry[3] = zeroFramedAry[i][j-1];
		  }
		  if(pass == 2){
		  	NeighborAry[0] = zeroFramedAry[i][j+1];
		  	NeighborAry[1] = zeroFramedAry[i+1][j-1];
		  	NeighborAry[2] = zeroFramedAry[i+1][j];
		  	NeighborAry[3] = zeroFramedAry[i+1][j+1];
		  }
		} // loads the neighbor of p(i,j) depending on the pass
		
		void firstPassDistance(){
			for(int i= 1; i < numRows + 1; i++) {
		    	for(int j = 1; j < numCols + 1; j++){
					if(zeroFramedAry[i][j] > 0){
						loadNeighbors(i, j, 1);	
						int min = NeighborAry[0];
						for(int k= 0; k < 4; k++) {
							if(NeighborAry[k] <= min){
								min = NeighborAry[k];
							}
						}
						zeroFramedAry[i][j] = min+1;
					}		
				}
		    }
		} // left to right, top to bottom first pass
		
		void secondPassDistance(){
			for(int i= numRows + 1; i >= 1; i--) {
		    	for(int j = numCols + 1; j >= 1; j--){
					if(zeroFramedAry[i][j] > 0){
						loadNeighbors(i, j, 2);	
						int min = NeighborAry[0];
						for(int k= 0; k < 4; k++) {
							if(NeighborAry[k] <= min){
								min = NeighborAry[k];
							}
						}
						min = min+1;
						if(min <= zeroFramedAry[i][j])
							zeroFramedAry[i][j] = min;
						if(zeroFramedAry[i][j] <= newMin)
							newMin = zeroFramedAry[i][j];
						if(zeroFramedAry[i][j] >= newMax)
							newMax = zeroFramedAry[i][j];
					}		
				}
		    }
		} // right to left, bottom to top second pass
		
		void prettyPrint(int pass){
			if(pass == 1){
				outFiletwo << "pass-1";
				outFiletwo << endl;
			}
			
			else if(pass == 2){
				outFiletwo << endl;
  				outFiletwo << "pass-2";
  				outFiletwo << endl;
			}
			
			else {
				// outfile1 for future processing
  				outFile << numRows; 
			    outFile << " "; 
			    outFile << numCols; 
			    outFile << " "; 
			    outFile << newMin; 
			    outFile << " "; 
			    outFile << newMax;
			    outFile << endl;
			}
			
			for (int i =1; i < numRows+1; i++){
		  		for (int j = 1; j < numCols+1; j++){
					if (zeroFramedAry[i][j] > 0){
						if(zeroFramedAry[i][j] / 10 == 0 ){
							if(pass ==1 || pass == 2){
								outFiletwo << zeroFramedAry[i][j];
								outFiletwo << " ";
							}
							else {
								outFile << zeroFramedAry[i][j];
								outFile << " ";
							}
				    	}
						else {
							if(pass ==1 || pass ==2){
								outFiletwo << zeroFramedAry[i][j];
								outFiletwo << " ";
							}
							else {
								outFile << zeroFramedAry[i][j];
								outFile << " ";
							}
							
						}
					}	 
					else {
						if (pass ==1 || pass ==2 ){
							outFiletwo << "  ";
						}
						else {
							outFile << "  ";
						}
					}
			  	}
			  	if (pass ==1 || pass ==2 ){
					outFiletwo << endl;
				}
				else {
					outFile << endl;
				}
			  	
		  	}		
		} // prints depending on case 
		
};

int main(int argc, char *argv[]){
  
  distanceTransform file(argv[1], argv[2], argv[3]);

  // zeroframe the img 
  file.zeroFramed();
  
  //load the img
  file.loadImage();

  // prettyPrint pass one 
  file.firstPassDistance();
  file.prettyPrint(1);
  
  // prettyPrint pass two
  file.secondPassDistance();
  file.prettyPrint(2);
  
  // prettyPrint for future processing 
  file.prettyPrint(3);
  
  return 0;
}

