package project3;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.Collection;
import java.util.Hashtable;
import java.util.StringTokenizer;

import sp.interfacepack.XEToyAssemler1;

public class InstTable implements XEToyAssemler1{
	static Hashtable<String, Instruction> instructionTable = new Hashtable<>();

	
	@Override
	public void initialize() {
		// TODO Auto-generated method stub
		instructionTable = new Hashtable<>();
	}

	
	/*
	 * @pre-condition : exist instruction file
	 * @post-condition : make instructionTable
	 * @param File arg0 : instruction filename
	 * @return : void
	 * @activate : read File
	 * instruction	format	opcode	ops
	 */
	@Override
	public void parseData(File arg0) {
		// TODO Auto-generated method stub
		if(arg0.exists()){
			BufferedReader br = null;
			InputStreamReader isr = null;
			FileInputStream fis = null;
			
			try {
				fis = new FileInputStream(arg0);
				isr = new InputStreamReader(fis, "UTF-8");
				br = new BufferedReader(isr);
				
				String temp = new String();
				while((temp = br.readLine()) != null){
					StringTokenizer st = new StringTokenizer(temp, " ");
					
					String instr = st.nextToken();
					int format = Integer.parseInt(st.nextToken());
					int op = Integer.valueOf(st.nextToken(), 16);
					int ops = Integer.parseInt(st.nextToken());
					
					Instruction inst = new Instruction(instr, op, format, ops);
					instructionTable.put(instr, inst);
				}
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	/*
	 * @pre-condition : exist instructionTable
	 * @post-condition : print Opcode
	 * @param
	 * @return : void
	 * @activate : print all Opcode
	 * 
	 */
	@Override
	public void printOPCODE() {
		// TODO Auto-generated method stub
		Collection<Instruction> tableValues = instructionTable.values();
		for(Instruction value : tableValues){
			System.out.println(Integer.toHexString(value.getOp()));
		}
	}
	
	
	public static int searchFormat(String operator){
		if(instructionTable.get(operator) != null){
			return instructionTable.get(operator).getFormat();
		}else{
			return -1;
		}
	}
	
	public static int searchOpcode(String operator){
		if(instructionTable.get(operator) != null){
			return instructionTable.get(operator).getOp();
		}else{
			return -1;
		}
	}
}
