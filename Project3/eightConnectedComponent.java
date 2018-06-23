import java.io.*;
import java.util.Scanner;

	
public class eightConnectedComponent {
	private static int numRows;
	private static int numCols;
	private static int minVal;
	private static int maxVal;
	private static int newMin;
	private static int newMax;
	
	private static int newLabel = 0;
	
	private static int[][] zeroFramaedAry;
	private static int[] neighborAry = new int[5];
	private static int[] EQAry;
	
	private static FileInputStream infile;
	private static FileOutputStream outfile;
	private static FileOutputStream outfileTwo;
	private static FileOutputStream outfileThree;
	
	private static String one;
	private static String two;
	private static String three;
	private static String four;
	
	public static void main(String args[]) {
		try {
			one = args[0];
			two = args[1];
			
			/// for soft copy only two is necessary
			
			//three = args[2];
			//four = args[3];
		} catch (Exception e) {
			// TODO: handle exception
		}
		
		
	    eightConnectedComponent first = new eightConnectedComponent();
		
	   
	}
	
	public eightConnectedComponent() {
		try {
			infile = new FileInputStream(one);
			outfile = new FileOutputStream(two);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		Scanner file = new Scanner(infile);
		numRows = file.nextInt();
		numCols = file.nextInt();
		minVal = file.nextInt();
		maxVal = file.nextInt();
		
	
		zeroFramaedAry = new int[numRows+2][numCols+2];
		EQAry = new int [(numRows * numCols)/2];
		
		for (int i = 0; i < EQAry.length; i++) {
			EQAry[i] = i;
		}
		
		loadImage(file);
		zeroFramed();
		
		PrintStream print = new PrintStream(outfile);
		print.println("Pass-1");
		Eight_ConnectCC_Pass1();
		prettyPrint(outfile);
		print.println();
		print.println("EQAry");
		print.println("index" + " number");
		for (int i = 0; i < newLabel; i++) {
			print.println(i + " " +EQAry[i]);
		}
		
		print.println();
		print.println("Pass-2");
		Eight_ConnectCC_Pass2();
		prettyPrint(outfile);
		print.println();
		print.println("EQAry");
		print.println("index" + " number");
		for (int i = 0; i < newLabel; i++) {
			print.println(i + " " +EQAry[i]);
		}
		
		print.println();
		manageEQAry();
		print.println("EQAry after manageEQAry");
		print.println("index" + " number");
		for (int i = 0; i < newLabel; i++) {
			print.println(i + " " +EQAry[i]);
		}
		
		print.println();
		print.println("Pass-3");
		Eight_ConnectCC_Pass3();
		prettyPrint(outfile);
		print.println();
		print.println("EQAry");
		print.println("index" + " number");
		for (int i = 0; i < newLabel; i++) {
			print.println(i + " " +EQAry[i]);
		}
	}
	
	public static void loadImage(Scanner f) {
		
		for (int i = 1; i < zeroFramaedAry.length-1; i++) {
			for (int j = 1; j < zeroFramaedAry[0].length-1; j++) {
				zeroFramaedAry[i][j] = f.nextInt();
			}	
		}
		
		f.close();
		
	} // loads the image into the array
	
	public static void zeroFramed() {
		for (int i = 0; i < zeroFramaedAry[0].length; i++) {
			zeroFramaedAry[0][i] = 0;
			zeroFramaedAry[numRows+1][i]= 0; 
		}
		for (int i = 0; i < zeroFramaedAry.length; i++) {
			zeroFramaedAry[i][0] = 0;
			zeroFramaedAry[i][numCols+1]= 0;
		}
	}
	
	public static void loadNeighbors(int pass, int row, int col) {
		if(pass == 1) {
			neighborAry[0] = zeroFramaedAry[row-1][col-1];
			neighborAry[1] = zeroFramaedAry[row-1][col];
			neighborAry[2] = zeroFramaedAry[row-1][col+1];
			neighborAry[3] = zeroFramaedAry[row][col-1];
		}
		else if (pass == 2) {
			neighborAry[0] = zeroFramaedAry[row+1][col-1];
			neighborAry[1] = zeroFramaedAry[row+1][col];
			neighborAry[2] = zeroFramaedAry[row+1][col+1];
			neighborAry[3] = zeroFramaedAry[row][col+1];
			
		}
		
	}
	
	public static void Eight_ConnectCC_Pass1() {
		for (int i = 1; i < zeroFramaedAry.length-1; i++) {
			for (int j = 1; j < zeroFramaedAry[0].length-1; j++) {
				loadNeighbors(1, i, j);
				if(zeroFramaedAry[i][j] > 0) {
					int a = neighborAry[0];
					int b = neighborAry[1];
					int c = neighborAry[2];
					int d = neighborAry[3];
					
					if(a == b && b == c && c == d && d == 0) {
						newLabel++;
						zeroFramaedAry[i][j] = newLabel;
					} // case 1 
					
					else if (a != 0 || b !=0 || c != 0 || d != 0) {
						if(a == 0 && b == 0 && c == 0 && d != 0) {
							zeroFramaedAry[i][j] = d; 
						}
						else if(a == 0 && b == 0 && c != 0 && d == 0) {
							zeroFramaedAry[i][j] = c; 
						}
						else if(a == 0 && b == 0 && c == d ) {
							zeroFramaedAry[i][j] = c; 
						}
						else if(a == 0 && b != 0 && c == 0 && d == 0) {
							zeroFramaedAry[i][j] = b; 
						}
						else if(a == 0 && b == d && c == 0) {
							zeroFramaedAry[i][j] = b; 
						}
						else if(a == 0 && b == c && d == 0) {
							zeroFramaedAry[i][j] = b; 
						}
						else if(a == 0 && b == c && c == d ) {
							zeroFramaedAry[i][j] = b; 
						}
						else if(a != 0 && b == 0 && c == 0 && d == 0) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == d && b == 0 && c == 0 ) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == c && b == 0 && d == 0) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == c && b == 0 && c == d) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == b && c == 0 && d == 0) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == b && b == d && c == 0) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == b && b == c && d == 0) {
							zeroFramaedAry[i][j] = a; 
						}
						else if(a == b && b == c && c == d) {
							zeroFramaedAry[i][j] = a; 
						}
						else {
							int min = 10;
							for (int k = 0; k < neighborAry.length; k++) {
								if(neighborAry[k] <= min && neighborAry[k] != 0) {
									min = neighborAry[k];
								}
							}
							 zeroFramaedAry[i][j] = min;
							 updateEQAry(min);
						} // case 3
						
					} 
				}
			}
		}
	}
	

	public static void Eight_ConnectCC_Pass2() {
		for (int i = zeroFramaedAry.length-1; i == 1; i--) {
			for (int j = zeroFramaedAry[0].length-1; j == 1; j--) {
				loadNeighbors(2, i, j);
				if(zeroFramaedAry[i][j] > 0) {
					int m = neighborAry[0];
					int n = neighborAry[1];
					int o = neighborAry[2];
					int p = neighborAry[3];
					if(m == n && n == o && o == p && p == 0) {
					} // case 1
					
					else {
						if(m == n && n == o && o == p) {
							 // do nothing
						}
						else {
							int min = 50;
							for (int k = 0; k < neighborAry.length-1; k++) {
								if(neighborAry[k] <= min && neighborAry[k] != 0) {
									min = neighborAry[k];
								}
							}
							
							 zeroFramaedAry[i][j] = min;
							 updateEQAry(min);
						} // case 3
					}
					
					
				}
			}
		}
	}
		
	

	public static void Eight_ConnectCC_Pass3() {
		for (int i = 0; i < zeroFramaedAry.length; i++) {
			for (int j = 0; j < zeroFramaedAry[0].length; j++) {
				if(zeroFramaedAry[i][j] > 0) {
					zeroFramaedAry[i][j] = EQAry[zeroFramaedAry[i][j]];
				}
			}
		}
		
	}
	
	public static void updateEQAry(int min) {
		EQAry[newLabel] = min;
	}
	
	public static void manageEQAry() {
		int count = 0; 
		for (int i = 0; i <= newLabel; i++) {
			if(EQAry[i] >= i) {
				EQAry[i] = count++;
			}
			else {
				EQAry[i] = EQAry[EQAry[i]];
			}
		}
	}
	
	
	public static void prettyPrint(FileOutputStream file) {
		String line = numRows + " " + numCols + " " + minVal + " " + maxVal;
		PrintStream print = new PrintStream(file);
		print.println(line);
		for (int i =1; i < zeroFramaedAry.length-1; i++){
		  	for (int j = 1; j < zeroFramaedAry[0].length-1; j++){
		  		if(zeroFramaedAry[i][j] == 0) {
		  			print.print(" ");
		  		}
		  		else {
		  			int a = zeroFramaedAry[i][j];
		  			print.print(String.valueOf(a));
		  		}
		  	}
		  	print.println();
		  		
		}
		
	}
	
	
	
}
