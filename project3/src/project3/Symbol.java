package project3;

public class Symbol {
	private int addr;
	private String symbol;
	private int section;
	
	Symbol(int loc, String symbol, int section){
		this.addr = loc;
		this.symbol = symbol;
		this.section = section;
	}
	
	public int getSection() {
		return section;
	}

	public void setSection(int section) {
		this.section = section;
	}

	public int getAddr() {
		return addr;
	}
	public void setAddr(int addr) {
		this.addr = addr;
	}
	public String getSymbol() {
		return symbol;
	}
	public void setSymbol(String symbol) {
		this.symbol = symbol;
	}	
}
