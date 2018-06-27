#include <iostream>
#include <fstream>
using namespace std;

int numRowsImg;
int numColsImg;
int minImg;
int maxImg;

int numRowsStructElem;
int numColsStructElem;
int minStrctElem;
int maxStrctElem;
int rowOrigin;
int colOrigin;
int rowFrameSize; 
int colFrameSize;

int** imgAry;
int** morphAry;
int** structElemAry;

ifstream inFileone; 
ifstream inFiletwo; 
ofstream outFileone; 
ofstream outFiletwo;
ofstream outFilethree;
ofstream outFilefour;


void computeFrameSize(){
	rowFrameSize = numRowsStructElem;
	colFrameSize = numColsStructElem;
}

void loadImage(){
	
	for(int i =rowFrameSize/2; i < (numRowsImg+rowFrameSize/2); i++){
		for(int j =colFrameSize/2; j < (numColsImg+colFrameSize/2); j++){
			inFileone >> imgAry[i][j]; 
		}
	}
}

void loadstruct(){
  	
  	for(int i =0; i < numRowsStructElem; i++){
		for(int j =0; j < numColsStructElem; j++){
			inFiletwo >> structElemAry[i][j]; 
		}
	}
}    	

void zeroFrameImg(){
	
	// set it to 0
	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
		for(int j =0; j < (numColsImg + colFrameSize); j++){
			imgAry[i][j] = 0;	
		}
	}	
}

void initMorphAry( ){
	
	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
		for(int j =0; j < (numColsImg + colFrameSize); j++){
			morphAry[i][j] = 0; 
		}
	}
}

void dilation (int i, int j){ 

	bool done = false;
	for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
		for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
			if(structElemAry[r][c]	== 1 && imgAry[m][n] == 1){
				morphAry[i][j] = 1;
				done = true;
				break;
			}
		}
		if (done == true){
			break;
		}
	}
}
void erosion (int i, int j){ // as above

}

void closing (int i, int j){
 // as above
}
void opening (int i,int j){ // as above
}

void prettyPrint (int n){
	switch (n){
	    case 1:
	    	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					cout <<  imgAry[i][j]; 
				}
				cout << endl;
			}
			cout << endl;
	        break;
	    case 2: 
	        for(int i =0; i < (numRowsImg + 2); i++){
				for(int j =0; j < (numColsImg + 2); j++){
					cout <<  imgAry[i][j]; 
				}
				cout << endl;
			}
			break;
	    case 3: 
	    	for(int i =0; i < numRowsStructElem; i++){
				for(int j =0; j < numColsStructElem; j++){
					cout << structElemAry[i][j]; 
				}
				cout << endl;
			}
	        break;
	    default: 
			cout << "incorrect";
	    	break;
	}
}

void outputResult (){
	
}   

int main(int argc, char* argv[]){
	inFileone.open(argv[1]);
	inFiletwo.open(argv[2]);
	//outFile.open(argv[3]);
	//outFiletwo.open(argv[4]);
	//outFilethree.open(argv[5]);
	//outFilethree.open(argv[6]);
	
	inFileone >> numRowsImg >> numColsImg >> minImg >>maxImg;
	inFiletwo >> numRowsStructElem >> numColsStructElem >> minStrctElem >> maxStrctElem >> rowOrigin >> colOrigin;
	
	computeFrameSize();
	
	// initailize the array 
	imgAry = new int* [numRowsImg + rowFrameSize];
	for(int i =0; i < (numRowsImg + colFrameSize); i++){
		imgAry[i] = new int[numColsImg + colFrameSize];
	}
	
	zeroFrameImg ();
  	
  	loadImage();
  	
	cout << "Input Image" << endl;
	
	prettyPrint (1);

	morphAry = new int* [numRowsImg + rowFrameSize];
	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
		morphAry[i] = new int[numColsImg + colFrameSize];
	}
	
	structElemAry = new int* [numRowsStructElem];
	for(int i =0; i < (numRowsStructElem); i++){
		structElemAry[i] = new int[numColsStructElem];
	}
	
	loadstruct();

	cout << "Structuring Element" << endl;
		
	prettyPrint (3);
	
	initMorphAry();
	
	for(int i =rowFrameSize/2; i < (numRowsImg+rowFrameSize/2); i++){
		for(int j =colFrameSize/2; j < (numColsImg+colFrameSize/2); j++){
			if(imgAry[i][j] >= 1){
				morphAry[i][j] = imgAry[i][j];
				continue;
			}
			dilation(i,j); 
		}
	}
	
	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					cout <<  morphAry[i][j]; 
				}
				cout << endl;
			}
	/** 
	   - call dilation // see your lecture note
- prettyPrint (morphAry) // pretty print to the *console* the result of dilation
        		- outputResult //write the delation result to Output1 (argv[3])

step 5:  - initMorphAry( ) // initialize morphAry to zero 
	   - call erosion // see your lecture note
- prettyPrint (morphAry) // pretty print to the *console* the result of erosion
        		- outputResult //write the delation result to Output2 (argv[4]) 

step 6: - initMorphAry( ) // initialize morphAry to zero 
- call closing // By call those two morphological ops one after the other
	- prettyPrint (morphAry) // pretty print to the *console*  the result of  closing
             - outputResult //write the closing result to Output3 (argv[5])

step 7: - initMorphAry( ) // initialize morphAry to zero 
- call opening // By call those two morphological ops one after the other
- prettyPrint (morphAry) // pretty print to the *console* with "Opening Result"
       	 - outputResult //write the opening result to Output4 (argv[6])
**/
		
	
}
	
