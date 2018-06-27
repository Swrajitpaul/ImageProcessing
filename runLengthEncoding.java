import java.io.*;
import java.util.Scanner;

public class runLengthEncoding {
	
	public static FileInputStream infile;
	public static FileOutputStream outfile;
	private static int numRow;
	private static int numCol;
	private static int[][] array;
	
	public static void methodOne(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		array = new int[numRow][numCol];
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				array[i][j] = scan.nextInt();
			}
			scan.nextLine();
		}
		
		int row = 0;
		int nextValue = 0;
		print.println(1);
		
		while (row < numRow) {
			
			int col = 0;
			int count = 0; 
			boolean found = false;
			int currentValue = 0;
			
			while (col < numCol) {
				if(found == false && array[row][col] > 0) {
					currentValue = array[row][col];

					print.print(row);
					print.print(" ");
					print.print(col);
					print.print(" ");
					print.print(currentValue);
					print.print(" ");
					count= 1;
					found = true;
				}
				else if (found == true && array[row][col] > 0) {
					nextValue = array[row][col];
					if(nextValue == currentValue) {
						count++;
						if(col == numCol-1) {
							print.println(count);
							found = false;
						}
					}
					else {
						print.println(count);
						currentValue = nextValue;
						count = 1;
						print.print(row);
						print.print(" ");
						print.print(col);
						print.print(" ");
						print.print(currentValue);
						print.print(" ");
					}
				}
				else if(found == true ) {
					found = false;
					print.println(count);
					count = 0;
				}
				col++;
			}
			row++;
		}
	}
	
	public static void methodTwo(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		array = new int[numRow][numCol];
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				array[i][j] = scan.nextInt();
			}
			scan.nextLine();
		}
		
		int row = 0;
		int nextValue = 0;
		print.println(2);
		
		while (row < numRow) {
			
			int col = 0;
			int count = 0; 
			boolean found = false;
			int currentValue = 0;
			
			while (col < numCol) {
				if(found == false && array[row][col] > 0) {
					currentValue = array[row][col];

					print.print(row);
					print.print(" ");
					print.print(col);
					print.print(" ");
					print.print(currentValue);
					print.print(" ");
					count= 1;
					found = true;
				}
				else if (found == true && array[row][col] > 0) {
					nextValue = array[row][col];
					if(nextValue == currentValue) {
						count++;
						if(col == numCol-1) {
							col = -1;
							row++;
							if(row == numRow)
								break;
						}
					}
					else {
						print.println(count);
						currentValue = nextValue;
						count = 1;
						print.print(row);
						print.print(" ");
						print.print(col);
						print.print(" ");
						print.print(currentValue);
						print.print(" ");
					}
				}
				else if(found == true ) {
					found = false;
					print.println(count);
					count = 0;
				}
				col++;
			}
			row++;
		}
	
	}
	
	public static void methodThree(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		array = new int[numRow][numCol];
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				array[i][j] = scan.nextInt();
			}
			scan.nextLine();
		}
		
		int row = 0;
		int nextValue = 0;
		print.println(3);
		
		while (row < numRow) {
			int col = 0;
			int count = 0; 
			int currentValue = array[row][col];

			print.print(row);
			print.print(" ");
			print.print(col);
			print.print(" ");
			print.print(currentValue);
			print.print(" ");
			col++;
			count++; 
			
			while (col < numCol) {
				nextValue = array[row][col];
				if(nextValue == currentValue) {
					count++;
					if(col == numCol-1)
						print.println(count);
				}
				
				else {
					print.println(count);
					currentValue = nextValue;
					count = 1;
					print.print(row);
					print.print(" ");
					print.print(col);
					print.print(" ");
					print.print(currentValue);
					print.print(" ");
					
				}
				col++;
			}
			row++;
		}
	}
	
	public static void methodFour(Scanner scan) {
		PrintStream print = new PrintStream(outfile);
		array = new int[numRow][numCol];
		
		for(int i = 0; i < numRow; i++) {
			for(int j = 0; j < numCol; j++) {
				array[i][j] = scan.nextInt();
			}
			scan.nextLine();
		}
		
		int row = 0;
		int nextValue = 0;
		print.println(4);
		int currentValue = array[row][0];

		print.print(row);
		print.print(" ");
		print.print(0);
		print.print(" ");
		print.print(currentValue);
		print.print(" ");
		
		int count = 0;
		
		while (row < numRow) {
			int col = 0;
			while (col < numCol) {
				nextValue = array[row][col];
				if(nextValue == currentValue) {
					count++;
				}
				
				else {
					print.println(count);
					currentValue = nextValue;
					count = 1;
					print.print(row);
					print.print(" ");
					print.print(col);
					print.print(" ");
					print.print(currentValue);
					print.print(" ");
					
				}
				col++;
			}
			row++;
			if(row == numRow)
				print.println(count);
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

		
		System.out.println("Method 1) Encode without zero and no wrap-around.");
		System.out.println("Method 2) Encode without zero and wrap-around.");
		System.out.println("Method 3) Encode with zero and no wrap-around.");
		System.out.println("Method 4) Encode with zero and wrap-around.");
		System.out.println("Enter the method number (1, 2, 3, or 4)");
		
		int methodNumber = 0;
		try {
			Scanner user = new Scanner(System.in);
			methodNumber = user.nextInt();
			
			if(methodNumber != 1 && methodNumber != 2 && methodNumber != 3 && methodNumber != 4) {
				System.out.println("the value is not between 1 and 4");
				System.exit(0);
			}
			user.close();
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
