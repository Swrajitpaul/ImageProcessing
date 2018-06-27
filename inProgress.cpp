#include <iostream>
#include <fstream>
using namespace std;

ifstream inFile; 
ofstream outFile; 
ofstream outFiletwo;

class image{
	
	public:
		
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
			
		int** imgAry;
		
		int rows; // numRows +2 
		int cols; // numCols +2
	
		image(string in, string out1, string out2){
			
			// opens input and output files
  			inFile.open(in.c_str());
  			
			outFile.open(out1.c_str());
  			
			outFiletwo.open(out2.c_str());
  
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
				
		void loadImage(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		      		int temp;
		      		inFile >> temp;
		      		imgAry[i][j] = temp;
		    	}
		  	}
		} // loads the img into the array
		
		void zeroFramed(){
			for(int i= 1; i < numCols + 1; i++) {
		   		imgAry[0][i] = 0;
		   		imgAry[numRows+1][i] = 0;
		  	}
		  	
		  	for(int i= 0; i < numRows + 2; i++) {
		    	imgAry[i][0] = 0;
		   		imgAry[i][numCols+1] = 0;
		  	}
		} // zeroFrame the arrays

};
	
class chainCode{
	
	struct point{
		int row;
		int col;
	};
		
	public:
		point neighborCoord[8];
		point startP;
		point currentP;
		point nextP;
		int lastQ;	
		int nextQ;
		int nextDirTable[8] = {6, 0, 0, 2, 2, 4, 4, 6};
		int nextDir;
		int PchainDir;
			
		int** imgAry;
		int rows; // numRows +2 
		int cols; // numCols +2
	  	
		chainCode(int** ary, int r, int c){ 
			imgAry = ary;
			rows = r;
			cols = c;
		} // constructor
		
		void getChainCode(){
			
			bool flag = false;
			
			for(int i= 1; i < rows-1; i++) {
		    	
				for(int j = 1; j < cols-1; j++){
		      		
					if(imgAry[i][j] > 0){
		      			
						flag = true;
						
						prettyPrint(1, 0, i, j);
						
						// set starting point
		      			startP.row = i;
		      			startP.col = j;
		      			
		      			// set current point
		      			currentP.row = i;
		      			currentP.col = j;
		      			
		      			lastQ = 4;
		      			
		      			int count = 0;
		      			
						while (true){
							
							nextQ = (lastQ+1) % 8;
							
							PchainDir = findNextP(currentP, nextQ, nextP);
							
							count++;
							
							prettyPrint(2, count, PchainDir, 0);
							
							if(count == 15){
				      			count = 0;
							}
				      		
							nextQ = PchainDir -1;
				      		
							if(nextQ < 0){
				      			nextQ += 8;	
							}
				      		
							lastQ = nextDirTable[nextQ];
				      		
							currentP.row = nextP.row;
				      		currentP.col = nextP.col;
				      		
				      		if((currentP.row == startP.row) && (currentP.col == startP.col)){
								break;
							}
						}
						if(flag == true){
							break;
						}
					}
		    	}
		    	if(flag == true){
					break;
				}
		  	}	
		}
		
		void loadNeighborsCoord(point current){
			neighborCoord[0].row = current.row;
			neighborCoord[0].col = current.col+1;
			
			neighborCoord[1].row = current.row-1;
			neighborCoord[1].col = current.col+1;
			
			neighborCoord[2].row = current.row-1;
			neighborCoord[2].col = current.col;
			
			neighborCoord[3].row = current.row-1;
			neighborCoord[3].col = current.col-1;
			
			neighborCoord[4].row = current.row;
			neighborCoord[4].col = current.col-1;
			
			neighborCoord[5].row = current.row+1;
			neighborCoord[5].col = current.col-1;
			
			neighborCoord[6].row = current.row+1;
			neighborCoord[6].col = current.col;
			
			neighborCoord[7].row = current.row+1;
			neighborCoord[7].col = current.col+1;
			
		}
		
		int findNextP(point currentP, int nextQ, point p){
			int chainDir;
			loadNeighborsCoord(currentP);
			chainDir = getChainDir(currentP, nextQ);
			nextP.row = neighborCoord[chainDir].row;
			nextP.col = neighborCoord[chainDir].col;
			return chainDir;
		}
		
		int getChainDir(point current, int nextQ){
			int chainDir;
			int counter = nextQ;
			while(true){
				int i = neighborCoord[counter].row;
				int j = neighborCoord[counter].col;
				
				if( imgAry[i][j]> 0){
					chainDir = counter;
					break;
				}
				counter++;
				counter = counter % 8;
			} 
			return chainDir;
		}
		
		void prettyPrint(int printWhichPart, int count, int numOne, int numTwo){
			if(printWhichPart == 1){
				outFile << numOne;
      			outFile << " ";
      			outFile << numTwo;
      			outFile << " ";
      			
      			outFiletwo << numOne;
      			outFiletwo << " ";
      			outFiletwo << numTwo;
      			outFiletwo << " ";
      			outFiletwo << endl;
			}
			if(printWhichPart == 2){
				outFile << numOne;
	      		outFile << " ";
	      		
				outFiletwo << numOne;
	      		outFiletwo << " ";	
	      		if(count == 15){
					outFiletwo << endl;	
				}
			}
			
		}
}; // end of class

int main(int argc, char *argv[]){
  	
  	// this will create an object, loads image and zeroframes.
	image img(argv[1], argv[2], argv[3]);
	img.loadImage();
	img.zeroFramed();
	
	chainCode cc(img.imgAry, img.rows, img.cols);
	cc.getChainCode();
	
	return 0;
}

