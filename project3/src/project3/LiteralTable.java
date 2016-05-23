package project3;

import java.util.Hashtable;

public class LiteralTable {
	private static Hashtable<String, Literal> literalTable;
	
	LiteralTable(){
		literalTable = new Hashtable<>();
	}
	
	public static void add(Literal inputLiteral){
		literalTable.put(inputLiteral.getName(), inputLiteral);
	}
	
	public static Literal get(String key){
		return literalTable.get(key);
	}
	
	public static void reset(){
		literalTable.clear();
	}

	public static Hashtable<String, Literal> getLiteralTable() {
		return literalTable;
	}

	public static void setLiteralTable(Hashtable<String, Literal> literalTable) {
		LiteralTable.literalTable = literalTable;
	}
	
	
}
