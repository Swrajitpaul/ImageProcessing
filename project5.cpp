#include <iostream>
#include <fstream>
using namespace std;

class ThinningSkeleton {
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	bool changeflag;
	int cycleCount;
		
	int** firstAry;
	int** secondAry;
	
	int rows; // numRows +2 
	int cols; // numCols +2
	
	ifstream inFile;
  	ofstream outFile;
  	ofstream outFiletwo;
	
	public:
		ThinningSkeleton(string in, string out1, string out2){

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
			  
			//  initializes the first and second array 
			firstAry = new int*[rows];
			for(int i = 0; i < rows; i++)
			    firstAry[i] = new int[cols];
			
			secondAry = new int*[rows];
			for(int i = 0; i < rows; i++)
			    secondAry[i] = new int[cols];
			    
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		      		secondAry[i][j] = 0;
		    	}
		  	}
			    
			// zero frame the arrays
			zeroFramed(1);
			zeroFramed(2);
			
			// load image
			loadImage();
			
			cycleCount = 0;
			
			changeflag = true;
			
			// inside the loop, north, south, east and west thinning functions are called
			while(changeflag == true){
				if(cycleCount == 0){
					prettyPrint(cycleCount, " ");
				}
				
				changeflag = false;
				cycleCount++;
				
				NorthThinning();
				copyAry();
				if(cycleCount == 2 || cycleCount == 4){
					prettyPrint(cycleCount, "North Thinning");
				}
			
				SouthThinning();
				copyAry();
				if(cycleCount == 2 || cycleCount == 4){
					prettyPrint(cycleCount, "South Thinning");
				}
			
				WestThinning();
				copyAry();
				if(cycleCount == 2 || cycleCount == 4){
					prettyPrint(cycleCount, "West Thinning");
				}
			
				EastThinning();
				copyAry();
				if(cycleCount == 2 || cycleCount == 4){
					prettyPrint(cycleCount, "East Thinning");
				}
				
			}
			
			prettyPrint(cycleCount, "Final");
			
			outFile << numRows;
			outFile << " ";
			outFile << numCols;
			outFile << " ";
			outFile << minVal;
			outFile << " ";
			outFile << maxVal;
			outFile << endl;
			
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		    		if (firstAry[i][j] == 0)
		    			outFile << " ";
		    		else 
						outFile << firstAry[i][j];
		    	}
		    	outFile << endl;
		  	} 
		  	
			// closing the input and output files
		  	inFile.close();
			outFile.close();
			outFiletwo.close();    
			 
		}
				
		void loadImage(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		      		int temp;
		      		inFile >> temp;
		      		firstAry[i][j] = temp;
		    	}
		  	}
		  
		} // loads the img into the array
		
		void zeroFramed(int arrayNumber){
			if(arrayNumber ==1){
				for(int i= 1; i < numCols + 1; i++) {
		   			firstAry[0][i] = 0;
		   			firstAry[numRows+1][i] = 0;
		  		}
		  		for(int i= 0; i < numRows + 2; i++) {
		    		firstAry[i][0] = 0;
		   			firstAry[i][numCols+1] = 0;
		  		}
		  	}
			else if(arrayNumber ==2){
				for(int i= 1; i < numCols + 1; i++) {
		   			secondAry[0][i] = 0;
		   			secondAry[numRows+1][i] = 0;
		  		}
		  		for(int i= 0; i < numRows + 2; i++) {
		    		secondAry[i][0] = 0;
		   			secondAry[i][numCols+1] = 0;
		  		}
		  	}
		  
		} // zeroFrame the arrays
		
		void copyAry(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		      		firstAry[i][j] = secondAry[i][j];
		    	}
		  	}
		}
		
		void DoThinning(int i, int j){
			int counter = 0; // how many are greater than 0
			int connected = 0; // how many connected components will be created
			bool cc = false; // connected component check
			
			if (counter == 0 &&  connected == 0){
				if(firstAry[i-1][j-1] > 0){
				counter++;
				}
				if(firstAry[i-1][j] > 0){
					counter++;
				}
				if(firstAry[i-1][j+1] > 0){
					counter++;
				}
				if(firstAry[i][j-1] > 0){
					counter++;
				}
				if(firstAry[i][j+1] > 0){
					counter++;
				}
				if(firstAry[i+1][j-1] > 0){
					counter++;
				}
				if(firstAry[i+1][j] > 0){
					counter++;
				}
				if(firstAry[i+1][j+1] > 0){
					counter++;
				} 
					
				if(firstAry[i-1][j] == 0){
					connected++;
				}
				if(firstAry[i+1][j] == 0){
					connected++;
				}
				if(firstAry[i][j+1] == 0){
					connected++;
				}
				if(firstAry[i][j-1] == 0){
					connected++;
				}
				
			}
			
			if(firstAry[i][j-1] == 1 && firstAry[i-1][j-1] == 1 && firstAry[i-1][j] == 1 && firstAry[i+1][j+1] != 1){
				cc = true;
			}
			
			if(firstAry[i][j+1] == 1 && firstAry[i-1][j] == 1 && firstAry[i-1][j+1] == 1 && firstAry[i+1][j-1] != 1){
				cc = true;
			}
			
			if(firstAry[i][j-1] == 1 && firstAry[i+1][j-1] == 1 && firstAry[i+1][j] == 1 && firstAry[i-1][j+1] != 1){
				cc = true;
			}
			
			if(firstAry[i][j+1] == 1 && firstAry[i+1][j] == 1 && firstAry[i+1][j+1] == 1 && firstAry[i-1][j-1] != 1){
				cc = true;
			}
			
			if ((counter >= 4 && connected < 2) ||	(counter >=4 && connected >= 2 && cc )) {
				secondAry[i][j] = 0;
				changeflag = true;
			}
			
			else {
				secondAry[i][j] = 1;
			}
			
		}
		
		void NorthThinning(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
					if ((firstAry[i][j] > 0 ) && ( firstAry[i-1][j] == 0)){
						DoThinning(i, j);
					}
					else 
						secondAry[i][j] = firstAry[i][j];
						
		    	}
		  	} 
		}
		
		void SouthThinning(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		    		if ((firstAry[i][j] > 0) && (firstAry[i+1][j] == 0)){
						DoThinning(i, j);
					} 
					else 
						secondAry[i][j] = firstAry[i][j];
		    	}
			} 
		}
		
		void WestThinning(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		    		if ((firstAry[i][j] > 0) && (firstAry[i][j-1] == 0)){
		    			DoThinning(i, j);
					} 
					else 
						secondAry[i][j] = firstAry[i][j];
		    	}
		  	} 
		}
		
		void EastThinning(){
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		    		if (firstAry[i][j] > 0 && firstAry[i][j+1] == 0){
		    			DoThinning(i, j);
					} 
					else 
						secondAry[i][j] = firstAry[i][j];
		    	}
		  	} 
		}
		
		void prettyPrint(int cycleCount, string direction){
			
			if(direction == "Final"){
				outFiletwo << "The result of " + direction + " cycle:";
			}
			if (cycleCount == 0) {
				outFiletwo << "The result of 0'th cycle or the input image:";
			}
			
			else if (cycleCount == 2){
				outFiletwo << "The result of 2'nd'cycle of " + direction + ":";
			}
			
			else if (cycleCount == 4 && direction != "Final"){
				outFiletwo << "The result of 4'th cycle of " + direction + ":";
			}
			
			
			outFiletwo << endl;
			// print into the output file 
			for(int i= 1; i < rows-1; i++) {
		    	for(int j = 1; j < cols-1; j++){
		    		if (firstAry[i][j] == 0)
		    			outFiletwo << " ";
		    		else 
						outFiletwo << firstAry[i][j];
		    	}
		    	outFiletwo << endl;
		  	} 
		}
};

int main(int argc, char *argv[]){
  	ThinningSkeleton file(argv[1], argv[2], argv[3]);
	
	return 0;
}

