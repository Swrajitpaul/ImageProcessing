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
			
		int** img;
		
		image(int a, int b, int c, int d){
			numRows = a;
			numCols = b;
			minVal = c;
			maxVal = d;
			
			img = new int*[numRows];
			for(int i = 0; i < numRows; i++)
			    img[i] = new int[numCols];
		}
				
		void plotPt2Img(){
			
		}
		
		void prettyPrint(){
			for(int i=0; i < numRows; i++){ 
				for(int j=0; j < numCols; j++){ 
					if(img[i][j] == 1 || img[i][j] == 8)
						outFiletwo << img[i][j];
					else 
						outFiletwo << " ";
				}	
				outFiletwo << endl;
			}	
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
		
		int label;
		
		boundaryPt* PtAry;
		kCurvature (string in, string o1, string o2, string o3){
			
			inFile.open(in.c_str());
			outFile.open(o1.c_str());
			outFiletwo.open(o2.c_str());
			outFilethree.open(o3.c_str());
			
			int a, b, c, d;
			inFile >> a;
			inFile >> b;
			inFile >> c;
			inFile >> d;
			
			image img(a,b,c,d);

			inFile >> label;
			
			countPts();
			CreatePtAry();
			
			inFile.close();
			
			// open the file agoin
			inFile.open(in.c_str());
			inFile >> a;
			inFile >> b;
			inFile >> c;
			inFile >> d;
			inFile >> label;
			
			cout << "enter for K";
			cout << endl;
			cin >> K;
			
			beginIndex = 0;
			
			int x;
			int y;
			while(true){
				if(inFile.eof()){
					break;
				}
				inFile >> x;
				inFile >> y;
				
				storePt(x, y, beginIndex);
				printPtAry(1);
				outFilethree << endl;
				beginIndex++;
			}
			
			Q = 0;
			P = K;
			R = 2*K;
			while(true){	
				beginIndex = P;
				double curvature = computeCurvature(Q,P,R);
				PtAry[beginIndex].curvature = curvature;
				
				outFilethree << Q;
				outFilethree << " ";
				outFilethree << P;
				outFilethree << " ";
				outFilethree << R;
				outFilethree << " ";
				outFilethree << beginIndex;
				outFilethree << " ";
				outFilethree << PtAry[beginIndex].x;
				outFilethree << " ";
				outFilethree << PtAry[beginIndex].y;
				outFilethree << " ";
				outFilethree << PtAry[beginIndex].curvature;
				outFilethree << endl;
				
				Q =(Q+1)% numPts;
				R = (R+1) % numPts;
				P = (P+1) % numPts; 
				
				if(beginIndex == K-1){
					break;
				}
			}
			
			printPtAry(2);
			
			computeLocalMaxima();
			setCorner();
			
			
			for(int i=0; i < numPts; i++){ 
				outFile << PtAry[i].x;
				outFile << " ";
				outFile << PtAry[i].y;
				outFile << " ";
				outFile << PtAry[i].corner;
				outFile << endl;
			}
			
			
			for(int i=0; i < numPts; i++){ 
				img.img[PtAry[i].x][PtAry[i].y] = PtAry[i].corner;
			}	
			
			img.prettyPrint();
			
			
		}
		void countPts(){
			int temp =0;
			while(!inFile.eof()){
				int x;
				int y;
				inFile >> x;
				inFile >> y;
				
				temp++;
			}
			numPts = temp;
		}
		
		void CreatePtAry(){
			PtAry = new boundaryPt[numPts];
		}
		
		void printPtAry(int s){
			if(s == 1){
				for(int i=0; i < numPts; i++){ 
					outFilethree << PtAry[i].x;
					outFilethree << PtAry[i].y;
				}	
			}
			else if(s == 2){
				for(int i=0; i < numPts; i++){ 
					outFilethree << PtAry[i].x;
					outFilethree << PtAry[i].y;
					outFilethree << PtAry[i].curvature;
				}	
			}
		
		}
		
		void storePt(int x, int y, int index){
			PtAry[index].x = x;
			PtAry[index].y = y;
		}
		
		double computeCurvature(int Q, int P,int  R){
			double r1= PtAry[Q].x;
			double c1= PtAry[Q].y;
			
			double r2= PtAry[P].x;
			double c2= PtAry[P].y;
			
			double r3= PtAry[R].x;
			double c3= PtAry[R].y;
			
			double slopeOne = ((c1 - c2)/((r1 -r2)+ 0.001)) ;
			double slopeTwo = ((c2 - c3)/((r2 - r3)+ 0.001));
			
			double curvature = slopeOne - slopeTwo;
			if (curvature < 0){
				curvature = curvature * -1;
			} 
			return curvature; 
			 
		}
		
		void computeLocalMaxima(){
			for(int i=0; i < numPts-1; i++){ 
				if(PtAry[i].curvature >= PtAry[(i-1) % numPts].curvature &&
				PtAry[i].curvature >= PtAry[(i-2) % numPts].curvature && 
				PtAry[i].curvature >= PtAry[(i+1) % numPts].curvature &&
				PtAry[i].curvature >= PtAry[(i+2) % numPts].curvature){
					PtAry[i].localMax = 1;
				}
				else {
					PtAry[i].localMax = 0;
				}
			}
		}
		
		void setCorner(){
				for(int i=0; i < numPts-1; i++){ 
				if(PtAry[i].localMax == 1 && 
				PtAry[(i-2) % numPts].localMax != 1 &&
				PtAry[(i+2) % numPts].localMax != 1) {
					PtAry[i].corner = 8;
				}
				else {
					PtAry[i].corner = 1;
				}
			}
		}
			
};

int main(int argc, char *argv[]){
  	
  	// this will create an object, loads image and zeroframes.
	kCurvature k(argv[1], argv[2], argv[3], argv[4]);
	
	return 0;
}

