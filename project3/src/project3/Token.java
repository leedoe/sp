package project3;

public class Token {
	private int locationCounter;
	private String label;
	private String operator;
	private String operand;
	private String command;
	private String objectCode;
	
	Token(String inputLabel, String inputOperator, String inputOperand, String inputCommand){
		locationCounter = 0;
		this.label = inputLabel;
		this.operator = inputOperator;
		this.operand = inputOperand;
		this.command = inputCommand;
		objectCode = new String();
	}

	public int getLocationCounter() {
		return locationCounter;
	}

	public void setLocationCounter(int locationCounter) {
		this.locationCounter = locationCounter;
	}

	public String getLabel() {
		return label;
	}

	public void setLabel(String label) {
		this.label = label;
	}

	public String getOperator() {
		return operator;
	}

	public void setOperator(String operator) {
		this.operator = operator;
	}

	public String getOperand() {
		return operand;
	}

	public void setOperand(String operand) {
		this.operand = operand;
	}

	public String getCommand() {
		return command;
	}

	public void setCommand(String command) {
		this.command = command;
	}

	public String getObjectCode() {
		return objectCode;
	}

	public void setObjectCode(String objectCode) {
		this.objectCode = objectCode;
	}
	
	public String toString(){
		return locationCounter + "\t" +
				label + "\t" +
				operator + "\t" +
				operand + "\t" +
				command + "\t" +
				objectCode;
	}
}
