package project3;

import java.io.File;

public class main {
	public static void main(String args[]){
		InstTable table = new InstTable();
		File file = new File("./inst.txt");
		System.out.println(file.exists());
		table.parseData(file);
		
		File file2 = new File("./input.txt");
		TokenList tl = new TokenList();
		tl.parseData(file2);
		
		
		Passer.Pass1();
		
		tl.printOPCODE();
	}
}
