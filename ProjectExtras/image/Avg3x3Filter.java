import java.io.*;
import java.util.Scanner;


public class Avg3x3Filter {
	private static int numRows;
	private static int numCols;
	private static int minVal;
	private static int maxVal;
	private static int newMin;
	private static int newMax;
	
	private static int[][] mirrorFramaedAry;
	private static int[][] tempAry;
	private static int[] neighborAry = new int[9];
	
	private static FileInputStream infile;
	private static FileOutputStream outfile;
	
	public static void main(String args[]) {
		String one = args[0];
		String two = args[1];
		Avg3x3Filter first = new Avg3x3Filter(one, two);
		
		try {
			outfile = new FileOutputStream(two);
			PrintStream printStream = new PrintStream(outfile);
			String line = numRows + " " + numCols + " " + newMin + " " + newMax;
			printStream.print(line);
			printStream.println();
			
			for (int i = 1; i < tempAry.length-1; i++) {
				for (int j = 1; j < tempAry[0].length-1; j++) {
					printStream.print(tempAry[i][j]);
				}
				printStream.println();
			}

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public Avg3x3Filter(String in, String out) {
		try {
			infile = new FileInputStream(in);
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
		
	
		mirrorFramaedAry = new int[numRows+2][numCols+2];
		tempAry = new int[numRows+2][numCols+2];
		
		loadImage(file);
		mirrorFramed();
		
	}
	
	public void loadImage(Scanner f) {
		for (int i = 1; i < mirrorFramaedAry.length-1; i++) {
			for (int j = 1; j < mirrorFramaedAry[0].length-1; j++) {
				mirrorFramaedAry[i][j] = f.nextInt();
			}	
		}
	}
	
	public void mirrorFramed() {
		for (int i = 1; i < mirrorFramaedAry[0].length-1; i++) {
			mirrorFramaedAry[0][i] = mirrorFramaedAry[1][i];
			mirrorFramaedAry[numRows+1][i]= mirrorFramaedAry[numRows][i];
		}
		for (int i = 0; i < mirrorFramaedAry.length; i++) {
			mirrorFramaedAry[i][0] = mirrorFramaedAry[i][1];
			mirrorFramaedAry[i][numCols+1]= mirrorFramaedAry[i][numCols];
		}
		
		for (int i = 1; i < mirrorFramaedAry.length-1; i++) {
			for (int j = 1; j < mirrorFramaedAry[0].length-1; j++) {
				loadNeighbors(i, j);
				tempAry[i][j] = AVG3X3();
			}
		}
	}
	
	public void loadNeighbors(int row, int col) {
		neighborAry[0] = mirrorFramaedAry[row-1][col-1];
		neighborAry[1] = mirrorFramaedAry[row-1][col];
		neighborAry[2] = mirrorFramaedAry[row-1][col+1];
		neighborAry[3] = mirrorFramaedAry[row][col-1];
		neighborAry[4] = mirrorFramaedAry[row][col];
		neighborAry[5] = mirrorFramaedAry[row][col+1];
		neighborAry[6] = mirrorFramaedAry[row+1][col-1];
		neighborAry[7] = mirrorFramaedAry[row+1][col];
		neighborAry[8] = mirrorFramaedAry[row+1][col+1];
	}
	
	public static int AVG3X3() {
		int average= 0;
		for (int i = 0; i < neighborAry.length; i++) {
			average += neighborAry[i]; 
		}
		average = average/9;
		if (average <= minVal) {
			newMin = average;
		}
		if (average >= maxVal) {
			newMax = average;
		}
		return average;
	} 
}
