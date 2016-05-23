package project3;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Set;
import java.util.StringTokenizer;


/*
 * @pre-condition : exist InstructionTable, LiteralTable, SymbleTable, TokenList
 * @post-condition : set locationCounter
 * @param : 
 * @return : void
 * @activate : set LocationCounter, and store Literal, compute EQU
 * 
 */
public class Passer {
	public static void Pass1(){
		int loc = 0;
		int section = 0;
		ArrayList<Token> token = TokenList.getTokenList();
		
		
		for(int i = 0; i < TokenList.getTokenList().size(); i++){
			Token tok = token.get(i);
			
			//set start address
			if(tok.getOperator() != null && tok.getOperator().equals("START")){
				loc = Integer.parseInt(token.get(i).getOperand());
				section++;
			}else if(tok.getOperator() != null && tok.getOperator().equals("CSECT")){
				loc = 0;
				section++;
			}
			
			//set locationCounter
			tok.setLocationCounter(loc);
			
			//store symbol at SymbolTable
			if(tok.getLabel() != null){
				SymbolTable.add(new Symbol(loc, token.get(i).getLabel(), section));
			}
			
			//set PC
			int instructionSize = 0;
			int opcode;
			if(tok.getOperator() != null){
				opcode = InstTable.searchOpcode(tok.getOperator());
			}else{
				opcode = -1;
			}
			
			if(opcode != -1){
				int format = InstTable.searchFormat(tok.getOperator());
				if(format != -1){
					switch(format){
					case 1:
						instructionSize = 1;
						break;
					case 2:
						instructionSize = 2;
						break;
					case 34:
						instructionSize = 3;
						break;
					}
				}
			}else{
				if(tok.getOperator() != null && tok.getOperator().charAt(0) == '+'){
					instructionSize = 4;
				}else if(tok.getOperator() != null && tok.getOperator().equals("WORD")){
					instructionSize = 3;
				}else if(tok.getOperator() != null && tok.getOperator().equals("BYTE")){
					instructionSize = 1;
				}else if(tok.getOperator() != null && tok.getOperator().equals("RESW")){
					instructionSize = 3 * Integer.parseInt(tok.getOperand());
				}else if(tok.getOperator() != null && tok.getOperator().equals("RESB")){
					instructionSize = Integer.parseInt(tok.getOperand());
				}
			}
			
			//store literal at literalTable
			if(!tok.getOperand().equals("") && tok.getOperand().charAt(0) == '='){
				LiteralTable.add(new Literal(tok.getOperand()));
			}
			
			//assign literals
			if(tok.getOperator().equals("LTORG") || tok.getOperator().equals("END")){
				Enumeration<Literal> enumKey = LiteralTable.getLiteralTable().elements();
				
				while(enumKey.hasMoreElements()){
					Literal lit = enumKey.nextElement();
					Token tempToken = new Token("*", lit.getName(), "", "", section);
					tempToken.setObjectCode(lit.getOperand());
					tempToken.setLocationCounter(loc);
					
					instructionSize = lit.getLength();
					loc += instructionSize;
					
					TokenList.getTokenList().add(i+1, tempToken);
					SymbolTable.add(new Symbol(loc - instructionSize, lit.getName(), section));
					i++;
				}
				
				LiteralTable.reset();
				instructionSize = 0;
			}
			
			//compute EQU operand
			if(!tok.getOperand().equals("") && tok.getOperator().equals("EQU")){
				String opr = tok.getOperand();
				if(opr.equals("*")){
					
				}else if(opr.contains("-") || opr.contains("+")){
					int location = 0;
					int startIndex = 0;
					for(int j = 0; j < opr.length(); j++){
						char character = opr.charAt(j);
						if(character == '-' || character == '+'){
							Symbol temp;
							String sym = opr.substring(startIndex, j);
							String real = new String();
							if(sym.charAt(0) == '-' || sym.charAt(0) == '+'){
								real = sym.substring(1);
							}else{
								real = sym;
							}
							
							
							if((temp = SymbolTable.get(real)) != null){
								if(temp.getSection() == tok.getSection()){
									if(sym.charAt(0) != '-'){
										location += temp.getAddr();
									}else{
										location -= temp.getAddr();
									}
								}
							}
							
							
							startIndex = j;
						}else if(j == opr.length() - 1){
							Symbol temp;
							String sym = opr.substring(startIndex);
							String real = new String();
							if(sym.charAt(0) == '-' || sym.charAt(0) == '+'){
								real = sym.substring(1);
							}else{
								real = sym;
							}
							
							
							if((temp = SymbolTable.get(real)) != null){
								if(temp.getSection() == tok.getSection()){
									if(sym.charAt(0) != '-'){
										location += temp.getAddr();
									}else{
										location -= temp.getAddr();
									}
								}
							}
						}
					}
					tok.setLocationCounter(location);
				}
			}
			
			
			loc += instructionSize;
		}
	}
	
	
	/*
	 * @pre-condition : executed Pass1
	 * @post-condition : print tokens
	 * @param : 
	 * @return : void
	 * @activate : set ObjectCode and print Tokens
	 * 
	 */
	public static void Pass2(){
		ArrayList<Token> token = TokenList.getTokenList();
		
		for(int i = 0; i < token.size(); i++){
			Token tok = token.get(i);
			
			//operator is not null
			if(tok.getOperator() != null){
				String operator;
				String oc = new String();
				
				if(tok.getOperator().charAt(0) == '+'){
					operator = tok.getOperator().substring(1);
				}else{
					operator = tok.getOperator();
				}
				
				int opcode = InstTable.searchOpcode(operator);
				int format = InstTable.searchFormat(operator);
				int disp = 0;
				int addr = 0;
				int firstTwo = 0;
				int xbpe = 0;
				
				//instructionSet
				if(opcode != -1){
					disp = 0;
					firstTwo = 0;
					xbpe = 0;
					
					firstTwo = opcode;
					
					if(format == 2){
						oc += String.format("%02X",  firstTwo);
						
						if(tok.getOperand().contains(",")){
							StringTokenizer st = new StringTokenizer(tok.getOperand(), ",");
							
							while(st.hasMoreTokens()){
								switch(st.nextToken()){
								case "A":
									oc += "0";
									break;
								case "X":
									oc += "1";
									break;
								case "L":
									oc+="2";
									break;
								case "B":
									oc+="3";
									break;
								case "S":
									oc+="4";
									break;
								case "T":
									oc+="5";
									break;
								case "F":
									oc+="6";
									break;
								}
							}
						}else{
							switch(tok.getOperand()){
							case "A":
								oc += "0";
								break;
							case "X":
								oc += "1";
								break;
							case "L":
								oc+="2";
								break;
							case "B":
								oc+="3";
								break;
							case "S":
								oc+="4";
								break;
							case "T":
								oc+="5";
								break;
							case "F":
								oc+="6";
								break;
							}
							oc+="0";
						}
						
						tok.setObjectCode(oc);
					}else if(format == 34){
						if(!tok.getOperand().equals("") && tok.getOperand().charAt(0) == '@'){
							//indirect
							firstTwo += 2;
							
							String tTok = tok.getOperand().substring(1);
							if(tTok.contains(",")){
								//indexed
								xbpe += 8;
							}
							
							StringTokenizer st = new StringTokenizer(tTok, ",");
							
							while(st.hasMoreTokens()){
								Symbol sTemp = SymbolTable.get(st.nextToken());
								if(sTemp != null){
									if(sTemp.getSection() == tok.getSection()){
										//PC relative
										xbpe += 2;
										
										disp = sTemp.getAddr() - (tok.getLocationCounter() + 3);
									}else{
										disp = 0;
									}
								}
							}
						}else if(!tok.getOperand().equals("") && tok.getOperand().charAt(0) == '#'){
							//immediate
							firstTwo += 1;
							disp = Integer.parseInt(tok.getOperand().substring(1));
						}else{
							//normal one SIC/XE
							firstTwo += 3;
							
							if(tok.getOperand().contains(",")){
								//indexed
								xbpe += 8;
							}
							
							String temp = tok.getOperand();
							StringTokenizer st = new StringTokenizer(temp, ",");
							
							while(st.hasMoreTokens()){
								Symbol sTemp = SymbolTable.get(st.nextToken());
								if(sTemp != null){
									if(sTemp.getSection() == tok.getSection()){
										//PC relative
										xbpe += 2;
										
										if(tok.getOperator().charAt(0) == '+'){
											disp = sTemp.getAddr() - (tok.getLocationCounter() + 4);
										}else{
											disp = sTemp.getAddr() - (tok.getLocationCounter() + 3);
										}
									}else{
										disp = 0;
									}
								}
							}
						}

						
						
						if(tok.getOperator().charAt(0) == '+'){
							//format 4
							xbpe += 1;
						}
						
						if(disp < 0){
							int tempNumber = 0xFFF;
							tempNumber += disp;
							disp = tempNumber + 1;
						}
						
						if(tok.getOperator().charAt(0) == '+'){
							oc += String.format("%02X%01X%06X", firstTwo, xbpe, disp);
						}else{
							oc += String.format("%02X%01X%03X", firstTwo, xbpe, disp);
						}
						
						tok.setObjectCode(oc);
					}
				}else{
					//no instruction
					if(tok.getOperator().equals("WORD")){
						if(tok.getOperand().contains("-") || tok.getOperand().contains("+")){
							disp = 0;
							int startIndex = 0;
							for(int j = 0; j < tok.getOperand().length(); j++){
								char character = tok.getOperand().charAt(j);
								if(character == '-' || character == '+'){
									Symbol temp;
									String sym = tok.getOperand().substring(startIndex, j);
									String real = new String();
									if(sym.charAt(0) == '-' || sym.charAt(0) == '+'){
										real = sym.substring(1);
									}else{
										real = sym;
									}
									
									
									if((temp = SymbolTable.get(real)) != null){
										if(temp.getSection() == tok.getSection()){
											if(sym.charAt(0) != '-'){
												disp += temp.getAddr();
											}else{
												disp -= temp.getAddr();
											}
										}
									}
									
									
									startIndex = j;
								}else if(j == tok.getOperand().length() - 1){
									Symbol temp;
									String sym = tok.getOperand().substring(startIndex);
									String real = new String();
									if(sym.charAt(0) == '-' || sym.charAt(0) == '+'){
										real = sym.substring(1);
									}else{
										real = sym;
									}
									
									
									if((temp = SymbolTable.get(real)) != null){
										if(temp.getSection() == tok.getSection()){
											if(sym.charAt(0) != '-'){
												disp += temp.getAddr();
											}else{
												disp -= temp.getAddr();
											}
										}
									}
								}
							}
						}
						
						tok.setObjectCode(String.format("%06d", disp));
					}else if(tok.getOperator().equals("BYTE")){
						String sub = tok.getOperand().substring(2, tok.getOperand().length()-1);
						tok.setObjectCode(sub);
					}
				}
			}
		}
	}
	
	/*
	 * @pre-condition : executed Pass2
	 * @post-condition : print ObjectProgram
	 * @param :
	 * @return : void
	 * @activate : print ObjectProgram
	 * 
	 */
	public static void PrintObjectProgram(){
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter("./output.txt", false));
			ArrayList<Token> list = TokenList.getTokenList();
			
			for(int i = 0; i < list.size(); i++){
				Token token = list.get(i);
				StringBuffer sb = new StringBuffer();
				if(token.getOperator().equals("START")){
					sb.append("H");
					sb.append(String.format("%-6S", token.getLabel()));
					sb.append(String.format("%06X", Integer.parseInt(token.getOperand())));
					
					int ml = 0;
					for(int j = i; j < list.size(); j++){
						if(ml < list.get(j).getLocationCounter()){
							ml = list.get(j).getLocationCounter();
						}
						
						if(list.get(j).getOperator().equals("CSECT") || list.get(j).equals("END")){
							sb.append(String.format("%06X", ml));
							break;
						}
					}
					
					bw.write(sb.toString());
					bw.newLine();
				}else if(token.getOperator().equals("EXTDEF")){
					sb = new StringBuffer();
					sb.append("D");
					
					StringTokenizer st = new StringTokenizer(token.getOperand(), ",");
					
					while(st.hasMoreTokens()){
						String temp = st.nextToken();
						sb.append(temp);
						sb.append(String.format("%06X", SymbolTable.get(temp).getAddr()));
					}
					
					bw.write(sb.toString());
					bw.newLine();
				}else if(token.getOperator().equals("EXTREF")){
					sb = new StringBuffer();
					sb.append("R");
					
					StringTokenizer st = new StringTokenizer(token.getOperand(), ",");
					while(st.hasMoreTokens()){
						String temp = st.nextToken();
						sb.append(String.format("%-6S",temp));
					}
					bw.write(sb.toString());
					bw.newLine();
					
					
				}else if(token.getOperator().equals("CSECT")){
					sb = new StringBuffer();
					sb.append("E");
					
					for(int j = i-1; j > -1; j--){
						if(list.get(j).getOperator().equals("START")){
							sb.append(String.format("%06X", Integer.parseInt(list.get(j).getOperand())));
							break;
						}else if(list.get(j).getOperator().equals("CSECT")){
							break;
						}
					}
					
					bw.write(sb.toString());
					bw.newLine();
					bw.newLine();
					
					
					sb = new StringBuffer();
					sb.append("H");
					sb.append(String.format("%-6S", token.getLabel()));
					
					int ml = 0;
					for(int j = i; j < list.size(); j++){
						if(ml < list.get(j).getLocationCounter()){
							ml = list.get(j).getLocationCounter();
						}
						
						if(list.get(j).getOperator().equals("CSECT") || list.get(j).equals("END")){
							sb.append(String.format("%06X", ml));
							break;
						}
					}
					
					bw.write(sb.toString());
					bw.newLine();
					
				}else if(token.getOperator().equals("END")){
					sb = new StringBuffer();
					sb.append("E");
					
					for(int j = i-1; j > -1; j--){
						if(list.get(j).getOperator().equals("START")){
							sb.append(String.format("%06X", Integer.parseInt(list.get(j).getOperand())));
							break;
						}else if(list.get(j).getOperator().equals("CSECT")){
							break;
						}
					}
					
					bw.write(sb.toString());
					break;
				}else if(token.getOperator().equals("RESW") || token.getOperator().equals("RESB") || token.getOperator().equals("EQU")){
					
				}else{
					sb = new StringBuffer();
					int total = 0;
					sb.append("T");
					sb.append(String.format("%06X", token.getLocationCounter()));
					
					StringBuffer obcode = new StringBuffer();
					for(int j = i; j < list.size(); j++){
						String oper = list.get(j).getOperator();
						if(!list.get(j).getObjectCode().equals("")){
							if(total+list.get(j).getObjectCode().length() > 60){
								break;
							}
							obcode.append(list.get(j).getObjectCode());
							total += list.get(j).getObjectCode().length();
						}else if(oper.equals("RESW") || oper.equals("RESB") || oper.equals("CSECT") || oper.equals("END")){
							i--;
							break;
						}
						i++;
					}
					
					sb.append(String.format("%02X", obcode.length()/2));
					sb.append(obcode);
					
					bw.write(sb.toString());
					bw.newLine();
					
				}
			}
			bw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
}
