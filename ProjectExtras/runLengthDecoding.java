import java.io.*;
import java.util.Scanner;

public class runLengthDecoding {

	public static FileInputStream infile;
	public static FileOutputStream outfile;
	private static int numRow;
	private static int numCol;
	private static int[][] array;
	
	public static void methodOne(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		
		int row;
		int col;
		int color;
		int length;
		
		array = new int[numRow][numCol];
		
		while(scan.hasNextLine()) {
			row = scan.nextInt();
			col = scan.nextInt();
			color = scan.nextInt();
			length = scan.nextInt();
			
			int counter = 1;
			while(counter <= length) {
				array[row][col] = color;
				col++;
				counter++;
				if (col == numCol)
					break;
			}
			if(!scan.hasNext())
				break;
		}
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				print.print(array[i][j]+ " ");
			}
			print.println();
		}
		
	}
	
	public static void methodTwo(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		
		int row;
		int col;
		int color;
		int length;
		
		array = new int[numRow][numCol];
		
		while(scan.hasNextLine()) {
			row = scan.nextInt();
			col = scan.nextInt();
			color = scan.nextInt();
			length = scan.nextInt();
			
			int counter = 1;
			while(counter <= length) {
				array[row][col] = color;
				col++;
				counter++;
				if (col == numCol) {
					col=0;
					row++;
				}
			}
			if(!scan.hasNext())
				break;
		}
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				print.print(array[i][j]+ " ");
			}
			print.println();
		}
		
	}
	
	public static void methodThree(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		
		int row;
		int col;
		int color;
		int length;
		
		array = new int[numRow][numCol];
		
		while(scan.hasNextLine()) {
			row = scan.nextInt();
			col = scan.nextInt();
			color = scan.nextInt();
			length = scan.nextInt();
			
			int counter = 1;
			while(counter <= length) {
				array[row][col] = color;
				col++;
				counter++;
				if (col == numCol)
					break;
			}
			if(!scan.hasNext())
				break;
		}
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				print.print(array[i][j]+ " ");
			}
			print.println();
		}
	}
	
	public static void methodFour(Scanner scan) {
		
		
		PrintStream print = new PrintStream(outfile);
		
		int row;
		int col;
		int color;
		int length;
		
		array = new int[numRow][numCol];
		
		while(scan.hasNextLine()) {
			row = scan.nextInt();
			col = scan.nextInt();
			color = scan.nextInt();
			length = scan.nextInt();
			
			int counter = 1;
			while(counter <= length) {
				array[row][col] = color;
				col++;
				counter++;
				if (col == numCol) {
					col=0;
					row++;
				}
			}
			if(!scan.hasNext())
				break;
		}
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				print.print(array[i][j]+ " ");
			}
			print.println();
		}
	}
	
	public static void main(String[] args) {
		try {
			infile = new FileInputStream(args[0]);
			outfile = new FileOutputStream(args[1]);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		Scanner scan = new Scanner(infile);
		PrintStream print = new PrintStream(outfile);
		
		// reads from the input file and outputs the header to the outputfile
		numRow = scan.nextInt();
		numCol = scan.nextInt();
		print.print(numRow);
		print.print(" ");
		print.print(numCol);
		print.print(" ");
		print.print(scan.nextInt());
		print.print(" ");
		print.print(scan.nextInt());
		print.println(" ");

		int methodNumber = 0;
		
		try {
			methodNumber = scan.nextInt();
			
			if(methodNumber != 1 && methodNumber != 2 && methodNumber != 3 && methodNumber != 4) {
				System.out.println("the value is not between 1 and 4");
				System.exit(0);
			}
		}
		catch(Exception type) {
			System.out.print("the entered value was not a string");
			System.exit(0);
		}
		
		if(methodNumber == 1) {
			methodOne(scan);
		}
		if(methodNumber == 2) {
			methodTwo(scan);
		}
		if(methodNumber == 3) {
			methodThree(scan);
		}
		if(methodNumber == 4) {
			methodFour(scan);
		}
		
		
	}

}
