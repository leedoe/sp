package project3;

public class Instruction {
	private String name;
	private int op;
	private int format;
	private int ops;
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getOp() {
		return op;
	}

	public void setOp(int op) {
		this.op = op;
	}

	public int getFormat() {
		return format;
	}

	public void setFormat(int format) {
		this.format = format;
	}

	public int getOps() {
		return ops;
	}

	public void setOps(int ops) {
		this.ops = ops;
	}

	Instruction(String inputName, int inputOp, int inputFormat, int inputOps){
		this.name = inputName;
		this.op = inputOp;
		this.format = inputFormat;
		this.ops = inputOps;
	}
}
