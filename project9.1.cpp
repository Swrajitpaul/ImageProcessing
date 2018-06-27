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
int** tempAry;
int temp;

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

	for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
		for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
			if(structElemAry[r][c]	== 1) {
				morphAry[m][n] = 1;
			}
		}
	}
}
void erosion (int i, int j){ 
	
	for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
		for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
			if(structElemAry[r][c]	== 1){
			   if(imgAry[m][n] != 1){
			   		goto done;	
			   } 
			   else {
			   		continue;
			   }
			}
					
		}
	}
	
	morphAry[i][j] = 1;	
	done: ;	
}

void closing (int i, int j){
	if(temp ==1){
		for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
			for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
				if(structElemAry[r][c]	== 1) {
					tempAry[m][n] = 1;
				}
			}
		}
	}
	if(temp ==2){
		for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
			for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
				if(structElemAry[r][c]	== 1){
				   if(tempAry[m][n] != 1){
				   		goto done;	
				   } 
				   else {
				   		continue;
				   }
				}
						
			}
		}
	
		morphAry[i][j] = 1;		
	}
	done: ;
}

void opening (int i,int j){ 
	if(temp ==1){
		for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
			for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
				if(structElemAry[r][c]	== 1){
				   if(imgAry[m][n] != 1){
				   		goto done;	
				   } 
				   else {
				   		continue;
				   }
				}
						
			}
		}
	
		tempAry[i][j] = 1;		
	}
	
	if(temp ==2){
		for(int r = 0, m = i-1; r < 3 , m < i+2; r++, m++){
			for(int c = 0, n = j-1; c < 3, n < j+2; c++, n++){
				if(structElemAry[r][c]	== 1) {
					morphAry[m][n] = 1;
				}
			}
		}
	}
	done: ;
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
	        for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					cout <<  morphAry[i][j]; 
				}
				cout << endl;
			}
			cout << endl;
			break;
	    case 3: 
	    	for(int i =0; i < numRowsStructElem; i++){
				for(int j =0; j < numColsStructElem; j++){
					cout << structElemAry[i][j]; 
				}
				cout << endl;
			}
			cout << endl;
	        break;
	    default: 
			cout << "incorrect";
	    	break;
	}
}

void outputResult (int n){
	switch (n){
	    case 3:
	    	outFileone << numRowsImg << " " << numColsImg << " " << minImg << " " << maxImg << endl;
	    	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					outFileone <<  morphAry[i][j]; 
				}
				outFileone << endl;
			}
			outFileone << endl;
	        break;
	    case 4:
	    	outFiletwo << numRowsImg << " " << numColsImg << " " << minImg << " " << maxImg << endl;
	        for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					outFiletwo <<  morphAry[i][j]; 
				}
				outFiletwo << endl;
			}
			outFiletwo << endl;
			break;
	   	case 5:
	   		outFilethree << numRowsImg << " " << numColsImg << " " << minImg << " " << maxImg << endl;
	    	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					outFilethree <<  morphAry[i][j]; 
				}
				outFilethree << endl;
			}
			outFilethree << endl;
	        break;
	    case 6: 
	    	outFilefour << numRowsImg << " " << numColsImg << " " << minImg << " " << maxImg << endl;
	        for(int i =0; i < (numRowsImg + rowFrameSize); i++){
				for(int j =0; j < (numColsImg + colFrameSize); j++){
					outFilefour <<  morphAry[i][j]; 
				}
				outFilefour << endl;
			}
			outFilefour << endl;
			break;
	    default: 
			cout << "incorrect";
	    	break;
	}
}   

int main(int argc, char* argv[]){
	inFileone.open(argv[1]);
	inFiletwo.open(argv[2]);
	outFileone.open(argv[3]);
	outFiletwo.open(argv[4]);
	outFilethree.open(argv[5]);
	outFilefour.open(argv[6]);
	
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
			if(imgAry[i][j] == 0){
				continue;
			}
			dilation(i,j); 
		}
	}

	cout << "The result of dilation" << endl;
	
	prettyPrint(2);
	
	outputResult(3);
	
	initMorphAry();
	
	for(int i =rowFrameSize/2; i < (numRowsImg+rowFrameSize/2); i++){
		for(int j =colFrameSize/2; j < (numColsImg+colFrameSize/2); j++){
			if(imgAry[i][j] == 0){
				continue;
			}
			erosion(i,j); 
		}
	}

	cout << "The result of erosion" << endl;
	
	prettyPrint(2);
	
	outputResult(4);
	
	initMorphAry();
	
	tempAry = new int* [numRowsImg + rowFrameSize];
	for(int i =0; i < (numRowsImg + colFrameSize); i++){
		tempAry[i] = new int[numColsImg + colFrameSize];
	}
	
	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
		for(int j =0; j < (numColsImg + colFrameSize); j++){
			tempAry[i][j] = 0; 
		}
	}
	
	for(int h = 1; h < 3; h++){
		temp = h;
		for(int i =rowFrameSize/2; i < (numRowsImg+rowFrameSize/2); i++){
			for(int j =colFrameSize/2; j < (numColsImg+colFrameSize/2); j++){
				if(imgAry[i][j] == 0 && h ==1){
					continue;
				}
				if(tempAry[i][j] == 0 && h ==2){
					continue;
				}
				closing(i,j); 
			}
		}	
		
	}

	cout << "The result of closing" << endl;
	
	prettyPrint(2);
	
	outputResult(5);
	
	initMorphAry();
	
	for(int i =0; i < (numRowsImg + rowFrameSize); i++){
		for(int j =0; j < (numColsImg + colFrameSize); j++){
			tempAry[i][j] = 0; 
		}
	}
	
	for(int h = 1; h < 3; h++){
		temp = h;
		for(int i =rowFrameSize/2; i < (numRowsImg+rowFrameSize/2); i++){
			for(int j =colFrameSize/2; j < (numColsImg+colFrameSize/2); j++){
				if(imgAry[i][j] == 0 && h ==1){
					continue;
				}
				if(tempAry[i][j] == 0 && h ==2){
					continue;
				}
				opening(i,j); 
			}
		}
	}

	cout << "The result of opening" << endl;
	
	prettyPrint(2);
	
	outputResult(6);
	
	inFileone.close();
	inFiletwo.close();
	outFileone.close();
	outFiletwo.close();
	outFilethree.close();
	outFilefour.close();
}
	
