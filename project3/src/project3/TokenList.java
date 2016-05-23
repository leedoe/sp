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
				while((temp = br.readLine()) != null){
					if(temp.charAt(0) == '.'){
						continue;
					}
					StringTokenizer st = new StringTokenizer(temp, "\t");
					
					int flag = 0;
					String label = null;
					String operator = null;
					String operand = null;
					String command = null;
				
					
					char[] tempArray = temp.toCharArray();
					if(tempArray[0] == '\t'){
						flag = 1;
					}
					
					
					while(st.hasMoreTokens()){
						switch(flag){
						case 0:
							label = st.nextToken();
							flag++;
							break;
						case 1:
							operator = st.nextToken();
							flag++;
							break;
						case 2:
							operand = st.nextToken();
							flag++;
							break;
						case 3:
							command = st.nextToken();
							break;
						}
					}
					
					
					Token token = new Token(label, operator, operand, command);
					
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
