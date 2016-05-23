package project3;

public class Literal {
	private String name;
	private String operand;
	private int length;
	private int loc;
	
	Literal(String name){
		this.name = name;
		
		if(name.charAt(1) == 'C'){
			this.length = (name.length() - 4);
		}else{
			this.length = (name.length() - 4) / 2;
		}
		
		String op = new String();
		if(name.charAt(1) == 'X'){
			op = name.substring(3, name.length()-1);
		}else{
			for(int i = 3; i < name.length() - 1; i++){
				op += String.format("%02X", (int)name.charAt(i));
			}
		}
		
		operand = op;
		
		this.loc = 0;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getOperand() {
		return operand;
	}
	public void setOperand(String operand) {
		this.operand = operand;
	}
	public int getLength() {
		return length;
	}
	public void setLength(int length) {
		this.length = length;
	}
	public int getLoc() {
		return loc;
	}
	public void setLoc(int loc) {
		this.loc = loc;
	}
	
	
}
