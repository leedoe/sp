package project3;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.StringTokenizer;

import sp.interfacepack.XEToyAssemler1;

public class TokenList implements XEToyAssemler1{
	private static ArrayList<Token> tokenList;

	TokenList(){
		tokenList = new ArrayList<>();
	}
	
	@Override
	public void initialize() {
		// TODO Auto-generated method stub
		tokenList = new ArrayList<>();
	}

	/*
	 * @pre-condition : exist file
	 * @post-condition : parse file data
	 * @param : File arg0
	 * @return : void
	 * @activate : parse Data
	 * 
	 */
	@Override
	public void parseData(File arg0) {
		// TODO Auto-generated method stub
		if(arg0.exists()){
			BufferedReader br = null;
			InputStreamReader isr = null;
			FileInputStream fis = null;
			
			SymbolTable symbolTable = new SymbolTable();
			LiteralTable literalTable = new LiteralTable();
			
			try {
				fis = new FileInputStream(arg0);
				isr = new InputStreamReader(fis, "UTF-8");
				br = new BufferedReader(isr);
				
				String temp = new String();
				int section = 0;
				while((temp = br.readLine()) != null){
					if(temp.charAt(0) == '.'){
						continue;
					}

					String[] st = temp.split("\t");
					
					int flag = 0;
					String label = "";
					String operator = "";
					String operand = "";
					String command = "";

					for(int i = 0; i < st.length; i++){
						switch(i){
						case 0:
							label = st[0];
							break;
						case 1:
							operator = st[1];
							break;
						case 2:
							operand = st[2];
							break;
						case 3:
							command = st[3];
							break;
						}
					}
					
					
					if(operator.equals("START") || operator.equals("CSECT")){
						section++;
					}
					
					Token token = new Token(label, operator, operand, command, section);
					
					tokenList.add(token);
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

	@Override
	public void printOPCODE() {
		// TODO Auto-generated method stub
		for(int i = 0; i < tokenList.size(); i++){
			System.out.println(tokenList.get(i).toString());
		}
	}
	
	public static ArrayList<Token> getTokenList(){
		return tokenList;
	}
	
}
