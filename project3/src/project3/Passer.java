package project3;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;

public class Passer {
	public static void Pass1(){
		int loc = 0;
		int section = 0;
		ArrayList<Token> token = TokenList.getTokenList();
		
		
		for(int i = 0; i < TokenList.getTokenList().size(); i++){
			Token tok = token.get(i);
			
			//set start address
			if(tok.getOperator().equals("START")){
				loc = Integer.parseInt(token.get(i).getOperand());
				section++;
			}else if(tok.getOperator().equals("CSECT")){
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
			int opcode = InstTable.searchOpcode(tok.getOperator());
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
				if(tok.getOperator().charAt(0) == '+'){
					instructionSize = 4;
				}else if(tok.getOperator().equals("WORD")){
					instructionSize = 3;
				}else if(tok.getOperator().equals("BYTE")){
					instructionSize = 1;
				}else if(tok.getOperator().equals("RESW")){
					instructionSize = 3 * Integer.parseInt(tok.getOperand());
				}else if(tok.getOperator().equals("RESB")){
					instructionSize = Integer.parseInt(tok.getOperand());
				}
			}
			
			//store literal at literalTable
			if(tok.getOperand().charAt(0) == '='){
				LiteralTable.add(new Literal(tok.getOperand()));
			}
			
			//assign literals
			if(tok.getOperator().equals("LTORG")){
				Set<String> keys = LiteralTable.getLiteralTable().keySet();
				Iterator<String> itr = keys.iterator();
				
				while(itr.hasNext()){
					Literal lit = LiteralTable.get(itr.next());
					Token tempToken = new Token("*", lit.getName(), lit.getOperand(), null);
					tempToken.setObjectCode(lit.getOperand());
					tempToken.setLocationCounter(loc);
					
					instructionSize = lit.getLength();
					loc += instructionSize;
					
					TokenList.getTokenList().add(i, tempToken);
				}
				
				instructionSize = 0;
			}
			
			
			loc += instructionSize;
		}
	}
}
