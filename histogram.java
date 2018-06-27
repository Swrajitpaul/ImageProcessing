import java.io.*;
import java.util.Scanner;

public class histogram {
	
	public static int numRows;
	public static int numCols;
	public static int minVal;
	public static int maxVal;
	public static int hist[];

	public static FileInputStream fInput = null;
	public static FileOutputStream fOutput;
	
	public static void main(String[] args) {
		
		try {
			String input = args[0];
			String output = args[1];
			fInput = new FileInputStream(input);
			fOutput = new FileOutputStream(output);
		
		} catch (IOException e) {
			System.out.println("file does not exist");
		}
		
		Scanner inputfile = new Scanner(fInput);
		
		numRows = inputfile.nextInt();
		numCols = inputfile.nextInt();
		minVal = inputfile.nextInt();
		maxVal = inputfile.nextInt();
		
		hist = new int[maxVal+1];
		
		while(inputfile.hasNext()) {
			int temp = inputfile.nextInt();
			for(int i = 0; i < maxVal+1; i++) {
				if(temp == i) {
					hist[i]++;
				}
			}
		}
		
		inputfile.close();
		try {
			fInput.close();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
		computeHistogram();

	}
	
	public static void computeHistogram() {
		
		String line = numRows + " " + numCols + " " + minVal + " " + maxVal;
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fOutput));
		
		try {
			bw.write(line);
			bw.newLine();
		} catch (Exception e) {
			
		}
		for (int i = 0; i < hist.length; i++) {
			try {
				bw.write(i + " "  + hist[i]);
				bw.newLine();
			} catch (IOException e) {
				
				e.printStackTrace();
			}
		}
	 
		try {
			bw.close();
			fOutput.close();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}

}
