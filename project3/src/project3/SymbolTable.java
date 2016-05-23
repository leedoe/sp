package project3;

import java.util.Hashtable;

public class SymbolTable {
	private static Hashtable<String ,Symbol> symbolList;
	
	SymbolTable(){
		symbolList = new Hashtable<String, Symbol>();
	}
	
	/*
	 * @pre-condition : exist Symbol
	 * @post-condition : put symbol in symbolList
	 * @param String input : Symbol
	 * @return : void
	 * @activate : use put method at Hashtable 
	 */
	public static void add(Symbol input){
		symbolList.put(input.getSymbol(), input);
	}
	
	/*
	 * @pre-condition : exist Symbol in SymbolTable
	 * @post-condition : delete symbol in symbolList
	 * @param String input : Symbol
	 * @return : void
	 * @activate : use remove method at Hashtable 
	 */
	public void delete(String input){
		symbolList.remove(input);
	}
	
	/*
	 * @pre-condition : exist Symbol
	 * @post-condition : get symbol in symbolList
	 * @param String input : Symbol
	 * @return : void
	 * @activate : use get method at Hashtable 
	 */
	public static Symbol get(String input){
		return symbolList.get(input);
	}
}
