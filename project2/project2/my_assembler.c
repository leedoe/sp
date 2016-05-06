/*
* ȭ�ϸ� : my_assembler.c
* ��  �� : �� ���α׷��� SIC/XE �ӽ��� ���� ������ Assembler ���α׷��� ���η�ƾ����,
* �Էµ� ������ �ڵ� ��, ��ɾ �ش��ϴ� OPCODE�� ã�� ����Ѵ�.
*
*/

/*
*
* ���α׷��� ����� �����Ѵ�.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* my_assembler ���α׷��� �������� �����͵��� ���ǵ� ���̴�.
*/

#include "my_assembler.h"

/* -----------------------------------------------------------------------------------
* ���� : ����ڷ� ���� ����� ������ �޾Ƽ� ��ɾ��� OPCODE�� ã�� ����Ѵ�.
* �Ű� : ���� ����, ����� ����
* ��ȯ : ���� = 0, ���� = < 0
* ���� : ���� ����� ���α׷��� ����Ʈ ������ �����ϴ� ��ƾ�� ������ �ʾҴ�.
*		   ���� �߰������� �������� �ʴ´�.
* -----------------------------------------------------------------------------------
*/


int main(int args, char *arg[])
{
	if (init_my_assembler()< 0)
	{
		printf("init_my_assembler: ���α׷� �ʱ�ȭ�� ���� �߽��ϴ�.\n");
		return -1;
	}

	if (assem_pass1() < 0) {
		printf("assem_pass1: �н�1 �������� �����Ͽ����ϴ�.  \n");
		return -1;
	}
	if (assem_pass2() < 0) {
		printf(" assem_pass2: �н�2 �������� �����Ͽ����ϴ�.  \n");
		return -1;
	}

	//make_output("output") ; 
}
/* -----------------------------------------------------------------------------------
* ���� : ���α׷� �ʱ�ȭ�� ���� �ڷᱸ�� ���� �� ������ �д� �Լ��̴�.
* �Ű� : ����
* ��ȯ : �������� = 0 , ���� �߻� = -1
* ���� : ������ ��ɾ� ���̺��� ���ο� �������� �ʰ� ������ �����ϰ� �ϱ�
*		   ���ؼ� ���� ������ �����Ͽ� ���α׷� �ʱ�ȭ�� ���� ������ �о� �� �� �ֵ���
*		   �����Ͽ���.
* -----------------------------------------------------------------------------------
*/

int init_my_assembler(void)
{
	int result;

	if ((result = init_inst_file("inst.data")) < 0)
		return -1;
	if ((result = init_input_file("input")) < 0)
		return -1;
	return result;
}

/* -----------------------------------------------------------------------------------
* ���� : ����� �ڵ带 ���� �н�1������ �����ϴ� �Լ��̴�.
*		   �н�1������..
*		   1. ���α׷� �ҽ��� ��ĵ�Ͽ� �ش��ϴ� ��ū������ �и��Ͽ� ���α׷� ���κ� ��ū
*		   ���̺��� �����Ѵ�.
*
* �Ű� : ����
* ��ȯ : ���� ���� = 0 , ���� = < 0
* ���� : ���� �ʱ� ���������� ������ ���� �˻縦 ���� �ʰ� �Ѿ �����̴�.
*	  ���� ������ ���� �˻� ��ƾ�� �߰��ؾ� �Ѵ�.
*
* -----------------------------------------------------------------------------------
*/

static int assem_pass1(void)
{
	/* add your code here */
	int i = 0;
	token_line = 0;
	locctr = 0;

	for (i = 0; i < line_num; i++) {
		if (token_parsing(i) < 0) {
			return -1;
		}
	}
	return 0;
}

/* -----------------------------------------------------------------------------------
* ���� : ����� �ڵ带 ���� �ڵ�� �ٲٱ� ���� �н�2 ������ �����ϴ� �Լ��̴�.
*		   �н� 2������ ���α׷��� ����� �ٲٴ� �۾��� ���� ������ ����ȴ�.
*		   ������ ���� �۾��� ����Ǿ� ����.
*		   1. ������ �ش� ����� ��ɾ ����� �ٲٴ� �۾��� �����Ѵ�.
* �Ű� : ����
* ��ȯ : �������� = 0, �����߻� = < 0
* ���� :
* -----------------------------------------------------------------------------------
*/

static int assem_pass2(void)
{
	make_objectcode("output.txt");
	return 0;
}
/* -----------------------------------------------------------------------------------
* ���� : �ӽ��� ���� ��� �ڵ��� ������ �о� ���� ��� ���̺�(inst_table)��
*        �����ϴ� �Լ��̴�.
* �Ű� : ���� ��� ����
* ��ȯ : �������� = 0 , ���� < 0
* ���� : ���� ������� ������ ������ ����.
*
*	===============================================================================
*		   | �̸� | ���� | ���� �ڵ� | ���۷����� ���� | NULL|
*	===============================================================================
*
* -----------------------------------------------------------------------------------
*/

int init_inst_file(char *inst_file)
{
	FILE* fp;
	char filePath[12];
	sprintf(filePath, "%s%s", "./", inst_file);
	int index = 0;

	if (fp = fopen(filePath, "r")) {
		while (!feof(fp)) {
			inst[index] = (inst_struct*)malloc(sizeof(inst_struct));
			inst[index]->str = (char*)malloc(sizeof(char) * 5);
			fscanf(fp, "%s %d %x %d \n", inst[index]->str, &inst[index]->format, &inst[index]->op, &inst[index]->ops);

			index++;
		}
	}
	else {
		return -1;
	}

	fclose(fp);
	inst_index = index;

	return 0;
}

/* -----------------------------------------------------------------------------------
* ���� : ����� �� �ҽ��ڵ带 �о���� �Լ��̴�.
* �Ű� : ������� �ҽ����ϸ�
* ��ȯ : �������� = 0 , ���� < 0
* ���� :
*
* -----------------------------------------------------------------------------------
*/


int init_input_file(char *input_file)
{
	FILE* fp;
	char filePath[12];
	sprintf(filePath, "%s%s%s", "./", input_file, ".txt");
	line_num = 0;

	if (fp = fopen(filePath, "r")) {
		while (!feof(fp)) {
			input_data[line_num] = (char*)malloc(sizeof(char) * 128);
			fgets(input_data[line_num], 128, fp);

			line_num++;
		}
	}
	else {
		return -1;
	}

	return 0;
}

/* -----------------------------------------------------------------------------------
* ���� : �ҽ� �ڵ带 �о�� ��ū������ �м��ϰ� ��ū ���̺��� �ۼ��ϴ� �Լ��̴�.
*        �н� 1�� ���� ȣ��ȴ�.
* �Ű� : �ҽ��ڵ��� ���ι�ȣ
* ��ȯ : �������� = 0 , ���� < 0
* ���� : my_assembler ���α׷������� ���δ����� ��ū �� ������Ʈ ������ �ϰ� �ִ�.
* -----------------------------------------------------------------------------------
*/

int token_parsing(int index)
{
	int flag = 0;
	int i, j;
	char* temp = (char*)malloc(sizeof(char) * 128);
	int format = 0;
	strcpy(temp, input_data[index]);

	if (temp[0] == '.') {
		return 0;
	}
	else if (temp[0] == '\t') {
		flag = 1;
	}
	else {
		label_num++;
	}

	token_table[token_line] = (token*)malloc(sizeof(token));

	if (flag == 1) {
		token_table[token_line]->label = (char*)malloc(sizeof(char) * 2);
		strcpy(token_table[token_line]->label, "");
	}

	for (i = 0; i < 3; i++) {
		token_table[token_line]->operand[i] = NULL;
	}

	char* tokenizer = (char*)malloc(sizeof(char) * 64);
	tokenizer = strtok(temp, "\t");

	while (tokenizer != NULL) {
		int i = 0;
		int operandNumber = -1;//Check operand Number in op code table, initialize is No operator
		int operandIndex = 0;
		int realOperandNumber = 0;//Count input operand
		int opTableIndex = 0;
		char* operandToken = (char*)malloc(sizeof(char) * 10);

		switch (flag) {
		case 0:
			token_table[token_line]->label = (char*)malloc(sizeof(char) * strlen(tokenizer) + 1);
			strcpy(token_table[token_line]->label, tokenizer);

			flag++;
			break;
		case 1:
			token_table[token_line]->operator_ = (char*)malloc(sizeof(char) * strlen(tokenizer) + 1);

			if (tokenizer[strlen(tokenizer) - 1] == '\n') {
				tokenizer[strlen(tokenizer) - 1] = '\0';
				strcpy(token_table[token_line]->operator_, tokenizer);
			}
			else {
				tokenizer[strlen(tokenizer)] = '\0';
				strcpy(token_table[token_line]->operator_, tokenizer);
			}
			
			flag++;
			break;
		case 2:
			//
			//instruction set�� ã�Ƽ� operand�� ��� �˾Ƴ���
			//operand ������ŭ token_table�� �ִ� operand�� �Է¹޴´�
			//operand ������ŭ �Է��� ���ٸ� ��� �Է� ���� �� break;
			//
			if (token_table[token_line]->operator_[0] == '+') {
				char* temp = &token_table[token_line]->operator_[1];
				opTableIndex = search_opcode(temp);
			}
			else {
				opTableIndex = search_opcode(token_table[token_line]->operator_);
			}

			if (opTableIndex == -1) {
				//No operator and No operand
				operandNumber = -1;
			}
			else {
				//operator exist and store operand Number
				operandNumber = inst[opTableIndex]->ops;
			}

			//no operand
			if (operandNumber == -1) {
				token_table[token_line]->operand[0] = (char*)malloc(sizeof(char) * strlen(tokenizer) + 1);
				if (tokenizer[strlen(tokenizer) - 1] == '\n') {
					tokenizer[strlen(tokenizer) - 1] = '\0';
				}
				strcpy(token_table[token_line]->operand[0], tokenizer);
				
			}
			else if (operandNumber == 0) {
				flag++;
				break;
			}
			else {
				int tokenIndex = 0;
				for (i = 0; i < strlen(tokenizer); i++) {
					if (tokenizer[i] == ',' || tokenizer[i] == '-') {
						token_table[token_line]->operand[operandIndex] = (char*)malloc(sizeof(char) * strlen(operandToken) + 1);
						strncpy(token_table[token_line]->operand[operandIndex], operandToken, tokenIndex);
						token_table[token_line]->operand[operandIndex][tokenIndex] = '\0';
						tokenIndex = 0;
						operandIndex++;
					}
					else if (i == strlen(tokenizer) - 1) {
						operandToken[tokenIndex++] = tokenizer[i];
						token_table[token_line]->operand[operandIndex] = (char*)malloc(sizeof(char) * strlen(tokenizer) + 1);
						
						if (tokenizer[strlen(tokenizer) - 1] == '\n') {
							operandToken[tokenIndex - 1] = '\0';
							strcpy(token_table[token_line]->operand[operandIndex], operandToken);
						}
						else {
							operandToken[tokenIndex] = '\0';
							strcpy(token_table[token_line]->operand[operandIndex], operandToken);
						}
					}
					else {
						operandToken[tokenIndex++] = tokenizer[i];
					}
				}
			}

			flag++;
			break;
		case 3:
			token_table[token_line]->comment = (char*)malloc(sizeof(char) * strlen(tokenizer) + 1);
			strcpy(token_table[token_line]->comment, tokenizer);
			flag++;
			break;
		default:
			break;
		}

		tokenizer = strtok(NULL, "\t");
	}

	//if label exist, input symbol table
	if (strcmp(token_table[token_line]->label, "") != 0) {
		strcpy(sym_table[sym_line].symbol, token_table[token_line]->label);
		sym_table[sym_line].addr = locctr;
		sym_line++;
	}

	//set locctr
	token_table[token_line]->locctr = locctr;


	int add = 0;
	char* operator_ = token_table[token_line]->operator_;
	int literal_flag = 0;

	//set locctr, set add value, literal, EQU
	if (strcmp(operator_, "START") == 0) {
		locctr = atoi(token_table[token_line]->operand[0]);
		token_table[token_line]->locctr = locctr;
		
		sym_table[sym_line - 1].addr = locctr;
	}
	else if (strcmp(operator_, "CSECT") == 0) {
		locctr = 0;
		token_table[token_line]->locctr = 0;

		sym_table[sym_line - 1].addr = 0;
	}
	else if (strcmp(operator_, "EQU") == 0) {
		int currentLoc = 0;
		char temp[100];
		char temp2[100];
		int result = 0;
		int operToken = 0;
		int idx = 0;
		int idx2 = 0;


		//expression check
		int tempOperator = -1;//0: -, 1: +
		int operandLength = strlen(token_table[token_line]->operand[0]);
		for (i = 0; i <= operandLength; i++) {
			char tempCharacter = token_table[token_line]->operand[0][i];
			temp[idx++] = token_table[token_line]->operand[0][i];
			if (tempCharacter == '-' || tempCharacter == '+' || tempCharacter == '\0'){
				temp[idx-1] = '\0';

				if (strcmp(temp, "*") == 0) {
					operToken = token_table[token_line]->locctr;
				}
				else {
					for (j = 0; j < sym_line; j++) {
						if (strcmp(sym_table[j].symbol, temp) == 0) {
							operToken = sym_table[j].addr;
							break;
						}
					}
				}

				if (tempOperator == -1) {
					result = operToken;
					idx = 0;
				}
				else if (tempOperator == 0) {
					result -= operToken;
					idx = 0;
				}
				else if (tempOperator == 1) {
					result += operToken;
					idx = 0;
				}

				if (tempCharacter == '-') {
					tempOperator = 0;
				}
				else if (tempCharacter == '+') {
					tempOperator = 1;
				}
				else {
					tempOperator = -1;
				}
			}
			
		}

		token_table[token_line]->locctr = result;
	}
	else if (strcmp(operator_, "LTORG") == 0 || strcmp(operator_, "END") == 0) {
		token_table[token_line]->locctr = -1;

		//assign literal on memory
		for (j = 0; j < literal_num; j++) {
			int k;
			token_line++;
			token_table[token_line] = (token*)malloc(sizeof(token));
			token_table[token_line]->operator_ = (char*)malloc(sizeof(char) * 2);
			strcpy(token_table[token_line]->operator_, "\0");
			for (k = 0; k < 3; k++) {
				token_table[token_line]->operand[k] = NULL;
			}

			//label = "*"
			token_table[token_line]->label = (char*)malloc(sizeof(char) * 3);
			strcpy(token_table[token_line]->label, "*\0");

			//loc
			token_table[token_line]->locctr = locctr;

			//operand
			token_table[token_line]->operand[0] = (char*)malloc(sizeof(char) * strlen(lit_table[j].name) + 1);
			strcpy(token_table[token_line]->operand[0], lit_table[j].name);

			if (lit_table[j].name[1] == 'C') {
				add = strlen(lit_table[j].name) - 4;
			}
			else if (lit_table[j].name[1] == 'X') {
				add = (strlen(lit_table[j].name) - 4) / 2;
			}

			locctr += add;

			//copy value to comment column
			token_table[token_line]->comment = (char*)malloc(sizeof(char) * strlen(lit_table[j].operandValue) + 2);
			strcpy(token_table[token_line]->comment, lit_table[j].operandValue);
		}

		//initial literal pool
		for (j = 0; j < literal_num; j++) {
			lit_table[j].address = 0;
			lit_table[j].length = 0;
			memset(lit_table[j].name, 0, sizeof(char) * 10);
			free(lit_table[j].operandValue);
		}

		literal_num = 0;
		literal_flag = 1;
		add = 0;
	}
	else if (strcmp(operator_, "EXTDEF") == 0) {
		token_table[token_line]->locctr = -1;
	}
	else if (strcmp(operator_, "EXTREF") == 0) {
		token_table[token_line]->locctr = -1;
	}
	else {
		//set add(format)
		int index = search_opcode(operator_);

		if (index == -1) {
			if (strcmp(operator_, "RESW") == 0) {
				add = atoi(token_table[token_line]->operand[0]) * 3;
			}
			else if (strcmp(operator_, "RESB") == 0) {
				add = atoi(token_table[token_line]->operand[0]);
			}
			else if (strcmp(operator_, "WORD") == 0) {
				add = 3;
			}
			else if (strcmp(operator_, "BYTE") == 0) {
				add = 1;
			}
			else if (operator_[0] == '+') {
				add = 4;
			}
		}
		else {
			int format = inst[index]->format;
			if (format == 1) {
				add = 1;
			}
			else if (format == 2) {
				add = 2;
			}
			else if (format == 34) {
				add = 3;
			}
		}
	}

	
	//literal pool(there are no LTORG, END)
	if (literal_flag == 0) {
		for (i = 0; i < 3; i++) {
			if (token_table[token_line]->operand[i] != NULL && token_table[token_line]->operand[i][0] == '=') {
				for (j = 0; j < literal_num; j++) {
					if (strcmp(lit_table[j].name, token_table[token_line]->operand[i]) == 0) {
						literal_flag = 1;
						break;
					}
				}

				if (literal_flag == 0) {
					strcpy(lit_table[literal_num].name, token_table[token_line]->operand[i]);
					lit_table[literal_num].address = locctr;

					//literal hex or character
					if (token_table[token_line]->operand[i][1] == 'X') {
						lit_table[literal_num].operandValue = (char*)malloc(sizeof(char) * (strlen(token_table[token_line]->operand[i]) - 4) + 1);

						for (j = 3; j < strlen(token_table[token_line]->operand[i]) - 1; j++) {
							lit_table[literal_num].operandValue[(j - 3)] = token_table[token_line]->operand[i][j];
						}
						lit_table[literal_num].operandValue[strlen(token_table[token_line]->operand[i]) - 4] = '\0';
					}
					else if (token_table[token_line]->operand[i][1] == 'C') {
						lit_table[literal_num].operandValue = (char*)malloc(sizeof(char) * (strlen(token_table[token_line]->operand[i]) - 4) * 2 + 1);

						for (j = 3; j < strlen(token_table[token_line]->operand[i]) - 1; j++) {
							sprintf(&lit_table[literal_num].operandValue[(j - 3) * 2], "%X", token_table[token_line]->operand[i][j]);
						}
					}

					lit_table[literal_num].length = strlen(token_table[token_line]->operand[i]) - 4;
					literal_num++;
				}
			}
		}
	}



	locctr += add;
	token_line++;


	free(temp);

return 0;
}
/* -----------------------------------------------------------------------------------
* ���� : �Է� ���ڿ��� ���� �ڵ������� �˻��ϴ� �Լ��̴�.
* �Ű� : ��ū ������ ���е� ���ڿ�
* ��ȯ : �������� = ���� ���̺� �ε���, ���� < 0
* ���� :
*
* -----------------------------------------------------------------------------------
*/

int search_opcode(char *str)
{
	int i = 0;

	for (i = 0; i < inst_index; i++) {
		if (strcmp(inst[i]->str, str) == 0) {
			return i;
		}
	}

	return -1;
}
/* -----------------------------------------------------------------------------------
* ���� : �Էµ� ���ڿ��� �̸��� ���� ���Ͽ� ���α׷��� ����� �����ϴ� �Լ��̴�.
* �Ű� : ������ ������Ʈ ���ϸ�
* ��ȯ : ����
* ���� : ���� ���ڷ� NULL���� ���´ٸ� ���α׷��� ����� ǥ��������� ������
*        ȭ�鿡 ������ش�.
*
* -----------------------------------------------------------------------------------
*/

void make_objectcode(char *file_name)
{
	FILE* fp;
	if (file_name != NULL) {
		if ((fp = fopen(file_name, "w")) == NULL) {
			return;
		}
	}

	int i = 0;
	
	objectProgramLine[objectProgramIndex] = (char*)malloc(sizeof(char) * 70);
	for (i = 0; i < token_line; i++) {
		char OC[8] = {0, };
		int j = 0;
		int operandNumber = 0;

		if (token_table[i]->locctr != -1) {
			printf("%06X\t", token_table[i]->locctr);
		}
		else {
			printf("\t");
		}

		printf("%s\t", token_table[i]->label);
		printf("%s\t", token_table[i]->operator_);

		for (operandNumber = 0; operandNumber < 3; operandNumber++) {
			if (token_table[i]->operand[operandNumber] != NULL && operandNumber != 0) {
				printf(",%s", token_table[i]->operand[operandNumber]);
			}
			else if (token_table[i]->operand[operandNumber] != NULL) {
				printf("%s", token_table[i]->operand[operandNumber]);
			}
			else {
				break;
			}
		}
		printf("\t");

		//search and set opcode
		int opcode = -1;
		int xbpe = 0;
		int disp = 0;
		int addr = 0;
		int format = 0;
		for (j = 0; j < inst_index; j++) {
			if (strcmp(token_table[i]->operator_, inst[j]->str) == 0) {
				opcode = inst[j]->op;
				format = inst[j]->format;
				break;
			}
			else if (token_table[i]->operator_[0] == '+') {
				if (strcmp(&token_table[i]->operator_[1], inst[j]->str) == 0) {
					opcode = inst[j]->op;
					format = inst[j]->format;
					break;
				}
			}
		}

		if (opcode == -1) {
			token_table[i]->objectCode = (char*)malloc(sizeof(char) * 6 + 2);

			//BYTE, WORD, LITERAL
			if (strcmp(token_table[i]->operator_, "WORD") == 0) {
				if (token_table[i]->operand[0][1] >= '0' && token_table[i]->operand[0][1] <= '9') {
					//digit
					printf("%06X", atoi(token_table[i]->operand[0]));
					sprintf(OC, "%06X", atoi(token_table[i]->operand[0]));
				}
				else {
					//EXT
					char* temp = (char*)malloc(sizeof(char) * 256);
					char* tok;
					int extFlag = 0;


					//search extref going up line
					for (j = i; j >= 0; j--) {
						if (strcmp(token_table[j]->operator_, "EXTREF") == 0) {
							strcpy(temp, token_table[i]->operand[0]);

							tok = strtok(temp, ",");
							while (tok != NULL) {
								if (strcmp(tok, token_table[i]->operand[0]) == 0) {
									extFlag = 1;
									break;
								}
							}

							if (extFlag == 1) {
								break;
							}
						}
					}

					if (extFlag == 1) {
						printf("000000");
						sprintf(OC, "000000");
					}
					else {
						strcpy(temp, token_table[i]->operand[0]);

						int currentLoc = 0;
						char temp[100];
						char temp2[100];
						int result = 0;
						int operToken = 0;
						int idx = 0;
						int idx2 = 0;

						int tempOperator = -1;//0: -, 1: +
						int operandLength = strlen(token_table[i]->operand[0]);
						for (j = 0; j <= operandLength; j++) {
							char tempCharacter = token_table[i]->operand[0][j];
							temp[idx++] = token_table[i]->operand[0][j];
							if (tempCharacter == '-' || tempCharacter == '+' || tempCharacter == '\0') {
								temp[idx - 1] = '\0';

								for (int k = 0; k < sym_line; k++) {
									if (strcmp(sym_table[j].symbol, temp) == 0) {
										operToken = sym_table[j].addr;
										break;
									}
								}

								if (tempOperator == -1) {
									result = operToken;
									idx = 0;
								}
								else if (tempOperator == 0) {
									result -= operToken;
									idx = 0;
								}
								else if (tempOperator == 1) {
									result += operToken;
									idx = 0;
								}

								if (tempCharacter == '-') {
									tempOperator = 0;
								}
								else if (tempCharacter == '+') {
									tempOperator = 1;
								}
								else {
									tempOperator = -1;
								}
							}
						}

						printf("%06X", result);
						sprintf(OC, "%06X", result);
					}
				}
			}
			else if (strcmp(token_table[i]->operator_, "BYTE") == 0) {
				if (token_table[i]->operand[0][0] == 'C') {
					unsigned char temp = token_table[i]->operand[0][2];
					printf("%02X", temp);
					sprintf(OC, "%02X", temp);
				}
				else if (token_table[i]->operand[0][0] == 'X') {
					char temp[4];
					for (j = 2; j < 4; j++) {
						temp[j - 2] = token_table[i]->operand[0][j];
					}
					temp[2] = '\0';

					printf("%s", temp);
					sprintf(OC, "%s", temp);
				}
			}
			else if (strcmp(token_table[i]->label, "*") == 0) {
				printf("%s", token_table[i]->comment);
				sprintf(OC, "%s", token_table[i]->comment);
			}
			else if (strcmp(token_table[i]->operator_, "START") == 0) {
				//objectProgram
				sprintf(objectProgramLine, "H%-6s%06X", token_table[i]->label, atoi(token_table[i]->operand[0]));
			}
		}
		else {
			int xFlag = 0;
			if (format == 1) {
				token_table[i]->objectCode = (char*)malloc(sizeof(char) * 2 + 2);

				printf("%02X", opcode);
				sprintf(OC, "%02X", opcode);
			}
			else if (format == 2) {
				token_table[i]->objectCode = (char*)malloc(sizeof(char) * 4 + 2);
				int k;
				printf("%02X", opcode);
				sprintf(OC, "%02X", opcode);
				for (k = 0; k < 2; k++) {
					if (token_table[i]->operand[k] != NULL) {
						switch (token_table[i]->operand[k][0]) {
							case 'A':
								printf("0");
								sprintf(OC + 2, "0");
								break;
							case 'X':
								printf("1");
								sprintf(OC + 2, "1");
								break;
							case 'L':
								printf("2");
								sprintf(OC + 2, "2");
								break;
							case 'B':
								printf("3");
								sprintf(OC + 2, "3");
								break;
							case 'S':
								printf("4");
								sprintf(OC + 2, "4");
								break;
							case 'T':
								printf("5");
								sprintf(OC + 2, "5");
								break;
							case 'F':
								printf("6");
								sprintf(OC + 2, "6");
								break;
							default:
								break;
						}
					}
					else {
						printf("0");
						sprintf(OC + 2 + k, "0");
					}
				}
			}
			else if (format != 2) {
				if (token_table[i]->operator_[0] != '+') {
					//format 3
					token_table[i]->objectCode = (char*)malloc(sizeof(char) * 6 + 2);

					//indexed
					for (j = 0; j < 3; j++) {
						if (token_table[i]->operand[j] != NULL) {
							if (j != 0) {
								xbpe += 8;
								break;
							}
						}
					}

					//set BP, this case have no base relative
					if (token_table[i]->operand[0] == NULL) {
						xbpe = 0;
						disp = 0;

						//SIC/XE
						opcode += 3;
					}
					else if (token_table[i]->operand[0][0] == '#') {
						//immediate
						opcode += 1;

						if (token_table[i]->operand[0][1] >= '0' && token_table[i]->operand[0][1] <= '9') {
							//digit
							disp = atoi(&token_table[i]->operand[0][1]);
						}
						else {
							//label
							
						}
					}
					else if (token_table[i]->operand[0][0] == '@') {
						//indirect
						opcode += 2;

						//PC
						xbpe += 2;

						int PC;
						int addi = 1;
						while (1) {
							if (token_table[i + addi]->locctr != -1) {
								PC = token_table[i + addi]->locctr;
								break;
							}
							else {
								addi++;
							}
						}


						//target
						int target;
						for (j = 0; j < token_line; j++) {
							if (strcmp(token_table[j]->label, &token_table[i]->operand[0][1]) == 0) {
								target = token_table[j]->locctr;
							}
						}

						disp = target - PC;
						if (disp < 0) {
							disp += 0xFFF;
							disp += 1;
						}
					}
					else if (token_table[i]->operand[0][0] == '=') {
						//literal
						xbpe += 2;

						//SIC/XE
						opcode += 3;

						//PC
						int PC;
						int addi = 1;
						while (1) {
							if (token_table[i + addi]->locctr != -1) {
								PC = token_table[i + addi]->locctr;
								break;
							}
							else {
								addi++;
							}
						}


						//target
						int target;
						for (j = 0; j < token_line; j++) {
							if (strcmp(token_table[j]->label, "*") == 0 && strcmp(token_table[j]->operand[0], token_table[i]->operand[0]) == 0) {
								target = token_table[j]->locctr;
							}
						}

						disp = target - PC;
						if (disp < 0) {
							disp += 0xFFF;
							disp += 1;
						}
					}
					else {
						//PC relative
						xbpe += 2;


						//PC
						int PC;
						int addi = 1;
						while (1) {
							if (token_table[i + addi]->locctr != -1) {
								PC = token_table[i + addi]->locctr;
								break;
							}
							else {
								addi++;
							}
						}


						//target
						int target;
						for (j = 0; j < sym_line; j++) {
							if (strcmp(sym_table[j].symbol, token_table[i]->operand[0]) == 0) {
								target = sym_table[j].addr;
							}
						}

						disp = target - PC;
						if (disp < 0) {
							disp += 0xFFF;
							disp += 1;
						}

						//SIC/XE
						opcode += 3;
					}

					printf("%02X", opcode);
					printf("%0X", xbpe);
					printf("%03X", disp);

					sprintf(OC, "%02X%0X%03X", opcode, xbpe, disp);
				}
				else {
					//format 4
					token_table[i]->objectCode = (char*)malloc(sizeof(char) * 8 + 2);

					//EXT
					char* temp = (char*)malloc(sizeof(char) * 256);
					char* tok;
					int extFlag = 0;


					//searching extref going up line
					for (j = i; j >= 0; j--) {
						if (strcmp(token_table[j]->operator_, "EXTREF") == 0) {
							strcpy(temp, token_table[i]->operand[0]);
							
							tok = strtok(temp, ",");
							while (tok != NULL) {
								if (strcmp(tok, token_table[i]->operand[0]) == 0) {
									extFlag = 1;
									break;
								}
							}

							if (extFlag == 1) {
								break;
							}
						}
					}

					//indexed
					for (j = 0; j < 3; j++) {
						if (token_table[i]->operand[j] != NULL) {
							if (j != 0) {
								xbpe += 8;
								break;
							}
						}
					}

					//set BP, this case have no base relative
					if (token_table[i]->operand[0] == NULL) {
						xbpe = 0;
						addr = 0;
					}
					else if (token_table[i]->operand[0][0] == '#') {
						//immediate
						opcode += 1;

						addr = atoi(&token_table[i]->operand[0][1]);
					}
					else if (token_table[i]->operand[0][0] == '@') {
						//indirect
						opcode += 2;
					}
					else if (token_table[i]->operand[0][0] == '=') {
						//literal
						xbpe += 2;

						//SIC/XE
						opcode += 3;

						//PC
						int PC;
						int addi = 1;
						while (1) {
							if (token_table[i + addi]->locctr != -1) {
								PC = token_table[i + addi]->locctr;
								break;
							}
							else {
								addi++;
							}
						}


						//target
						int target;
						for (j = 0; j < token_line; j++) {
							if (strcmp(token_table[j]->label, "*") == 0 && strcmp(token_table[j]->operand[0], token_table[i]->operand[0]) == 0) {
								target = token_table[j]->locctr;
							}
						}

						disp = target - PC;
						if (disp < 0) {
							//addr += 0xFFF;
							addr += 1;
						}
					}
					else if(extFlag != 1) {
						//NO EXTREF OPERAND
						//PC relative
						xbpe += 2;


						//PC
						int PC;
						int addi = 1;
						while (1) {
							if (token_table[i + addi]->locctr != -1) {
								PC = token_table[i + addi]->locctr;
								break;
							}
							else {
								addi++;
							}
						}


						//target
						int target;
						for (j = 0; j < sym_line; j++) {
							if (strcmp(sym_table[j].symbol, token_table[i]->operand[0]) == 0) {
								target = sym_table[j].addr;
							}
						}

						addr = target - PC;
						if (addr < 0) {
							//addr += 0xFFF;
							addr += 1;
						}

						//SIC/XE
						opcode += 3;
					}
					else if (extFlag == 1) {
						//FORMAT4 E:1
						xbpe += 1;
						//EXTREF
						addr = 0;
						//SIC/XE
						opcode += 3;
					}

					printf("%02X", opcode);
					printf("%0X", xbpe);
					printf("%06X", addr);

					sprintf(OC, "%02X%0X%03X", opcode, xbpe, disp);
				}
			}
		}



		printf("\n");
		token_table[i]->objectCode[0] = 0;
		strcpy(token_table[i]->objectCode, OC);
	}


	/*
	make object programming
	*/
	int startSection = -1;
	char* extref[10];
	int extrefIndex = 0;
	int modify[50];
	int modifyIndex = 0;
	for (i = 0; i < token_line; i++) {
		if (strcmp(token_table[i]->operator_, "START") == 0 || strcmp(token_table[i]->operator_, "CSECT") == 0) {
			if (startSection != -1) {
				//modification field
				for (int j = 0; j < modifyIndex; j++) {
					int index = modify[j];
					int addr = 0;
					int modiLength = 0;
					if (search_opcode(token_table[index]->operator_) > 0) {
						addr = token_table[index]->locctr + 1;
						modiLength = 05;
					}
					else {
						if (search_opcode(&token_table[index]->operator_[1]) > 0) {
							addr = token_table[index]->locctr + 1;
							modiLength = 5;
						}
						else {
							addr = token_table[index]->locctr;
							modiLength = 6;
						}
					}
					
					//search extref and check +,-
					char tokenTemp[100] = { 0 };
					int tempIndex = 0;
					int extrefFlag = 0;
					char oper = '+';
					if (token_table[index]->operand[0] != NULL) {
						int len = strlen(token_table[index]->operand[0]);
						for (int j = 0; j < strlen(token_table[index]->operand[0]); j++) {
							tokenTemp[tempIndex++] = token_table[index]->operand[0][j];
							if (token_table[index]->operand[0][j] == '-' || token_table[index]->operand[0][j] == '+' || j == len - 1) {
								if (j != len - 1) {
									tokenTemp[tempIndex - 1] = '\0';
								}
								
								if (token_table[index]->operand[0][j] == '-') {
									oper = '-';
								}
								else {
									oper = '+';
								}

								for (int k = 0; k < extrefIndex; k++) {
									if (strcmp(tokenTemp, extref[k]) == 0) {
										fprintf(fp, "M%06X%02X%c%s\n", addr, modiLength, oper, tokenTemp);
										extrefFlag = 1;
									}
								}
								tempIndex = 0;
							}
						}
					}

					if (extrefFlag != 1) {
						for (int j = 0; j < extrefIndex; j++) {
							for (int k = 0; k < 3; k++) {
								if (token_table[index]->operand[k] != NULL) {
									if (strcmp(token_table[index]->operand[k], extref[j]) == 0) {
										fprintf(fp, "M%06X%02X+%s\n", addr, modiLength, token_table[index]->operand[k]);
									}
								}
								else {
									break;
								}
							}
						}
					}


				}

				//initial
				memset(modify, -1, sizeof(int) * 50);
				memset(extref, NULL, sizeof(char*) * 10);
				extrefIndex = 0;
				modifyIndex = 0;
				
				//if operator is START, add start address at End Field 
				if (strcmp(token_table[startSection]->operator_, "START") == 0) {
					fprintf(fp, "E%06X\n\n", atoi(token_table[startSection]->operand[0]));
				}
				else {
					fprintf(fp, "E\n\n");
				}
		
			}

			//compute Program length
			int totalLength = 0;
			startSection = i;
			for (int j = i+1; j < token_line; j++) {
				if (search_opcode(token_table[j]->operator_) > 0) {
					totalLength += strlen(token_table[j]->objectCode) / 2;
				}
				else {
					if (strcmp(token_table[j]->operator_, "RESW") == 0) {
						totalLength += atoi(token_table[j]->operand[0]) * 3;
					}
					else if (strcmp(token_table[j]->operator_, "RESB") == 0) {
						totalLength += atoi(token_table[j]->operand[0]);
					}
					else if (strcmp(token_table[j]->operator_, "BYTE") == 0) {
						totalLength += 1;
					}
					else if (strcmp(token_table[j]->operator_, "WORD") == 0) {
						
						totalLength += 3;
					}
					else if (strcmp(token_table[j]->label, "*") == 0) {
						totalLength += strlen(token_table[j]->comment) / 2;
					}
					else if (token_table[j]->operator_[0] == '+') {
						totalLength += 4;
					}
					else if (strcmp(token_table[j]->operator_, "CSECT") == 0) {
						break;
					}
				}
			}

			fprintf(fp, "H%-6s%06X%06X\n", token_table[i]->label, token_table[i]->locctr, totalLength);
		}
		else if (strcmp(token_table[i]->operator_, "EXTDEF") == 0) {
			char* temp = (char*)malloc(sizeof(char) * strlen(token_table[i]->operand[0]) + 2);
			char* token;
			strcpy(temp, token_table[i]->operand[0]);

			token = strtok(temp, ",");
			fprintf(fp, "R");
			while (token != NULL) {
				fprintf(fp, "%-6s", token);
				
				for (int j = 0; j < sym_line; j++) {
					if (strcmp(sym_table[j].symbol, token) == 0) {
						fprintf(fp, "%06X", sym_table[j].addr);
						break;
					}
				}
				
				token = strtok(NULL, ",");
			}

			fprintf(fp, "\n");

		}
		else if (strcmp(token_table[i]->operator_, "EXTREF") == 0) {
			char* temp = (char*)malloc(sizeof(char) * strlen(token_table[i]->operand[0]) + 2);
			char* token;
			strcpy(temp, token_table[i]->operand[0]);
			
			token = strtok(temp, ",");
			fprintf(fp, "R");
			while(token != NULL) {
				//store extref
				extref[extrefIndex++] = token;


				fprintf(fp, "%-6s", token);
				token = strtok(NULL, ",");
			}

			fprintf(fp, "\n");
		}
		else {
			char string[71];
			int totalLength = 0;
			int index = 9;
			

			if (strcmp(token_table[i]->objectCode, "") != 0) {
				sprintf(string, "T%06X", token_table[i]->locctr);
				//totalLength += strlen(token_table[i]->objectCode)/2;

				while (1) {
					if (i == token_line) {
						char temp = string[9];
						sprintf(&string[7], "%02X", totalLength / 2);
						string[9] = temp;
						sprintf(string + index, "\n");

						fprintf(fp, "%s", string);

						//modification field
						for (int j = 0; j < modifyIndex; j++) {
							int index = modify[j];
							int addr = 0;
							int modiLength = 0;
							if (search_opcode(token_table[index]->operator_) > 0) {
								addr = token_table[index]->locctr + 1;
								modiLength = 05;
							}
							else {
								if (search_opcode(&token_table[index]->operator_[1]) > 0) {
									addr = token_table[index]->locctr + 1;
									modiLength = 05;
								}
								else {
									addr = token_table[index]->locctr;
									modiLength = 6;
								}
							}


							char tokenTemp[100] = { 0 };
							int tempIndex = 0;
							int extrefFlag = 0;
							char oper = '+';
							if (token_table[index]->operand[0] != NULL) {
								int len = strlen(token_table[index]->operand[0]);
								for (int j = 0; j < strlen(token_table[index]->operand[0]); j++) {
									tokenTemp[tempIndex++] = token_table[index]->operand[0][j];
									if (token_table[index]->operand[0][j] == '-' || token_table[index]->operand[0][j] == '+' || j == len - 1) {
										if (j != len - 1) {
											tokenTemp[tempIndex - 1] = '\0';
										}

										if (token_table[index]->operand[0][j] == '-') {
											oper = '-';
										}
										else {
											oper = '+';
										}

										for (int k = 0; k < extrefIndex; k++) {
											if (strcmp(tokenTemp, extref[k]) == 0) {
												fprintf(fp, "M%06X%02X%c%s\n", addr, modiLength, oper, tokenTemp);
												extrefFlag = 1;
											}
										}
										tempIndex = 0;
									}
								}
							}

							if (extrefFlag != 1) {
								for (int j = 0; j < extrefIndex; j++) {
									for (int k = 0; k < 3; k++) {
										if (token_table[index]->operand[k] != NULL) {
											if (strcmp(token_table[index]->operand[k], extref[j]) == 0) {
												fprintf(fp, "M%06X%02X+%s\n", addr, modiLength, token_table[index]->operand[k]);
											}
										}
										else {
											break;
										}
									}
								}
							}

						}

						memset(modify, -1, sizeof(int) * 50);
						memset(extref, NULL, sizeof(char*) * 10);
						extrefIndex = 0;
						modifyIndex = 0;

						if (startSection != -1) {
							fprintf(fp, "E\n\n");
						}

						break;
					}

					if (strcmp(token_table[i]->operator_, "RESW") == 0 ||
						strcmp(token_table[i]->operator_, "RESB") == 0 ||
						strcmp(token_table[i]->operator_, "CSECT") == 0) {
						char temp = string[9];
						sprintf(&string[7], "%02X", totalLength / 2);
						string[9] = temp;
						sprintf(string + index, "\n");
						i--;

						fprintf(fp, "%s", string);
						break;
					}
					
					if (strcmp(token_table[i]->objectCode, "") != 0) {
						if (totalLength + strlen(token_table[i]->objectCode) > 60) {
							i--;
							char temp = string[9];
							sprintf(&string[7], "%02X", totalLength / 2);
							string[9] = temp;
							sprintf(string + index, "\n");

							fprintf(fp, "%s", string);
							break;
						}else{
							sprintf(string + index, "%s", token_table[i]->objectCode);
							index += strlen(token_table[i]->objectCode);
							totalLength += strlen(token_table[i]->objectCode);
						}
					}


					//store extref operand
					char tokenTemp[100] = { 0 };
					int tempIndex = 0;
					int extrefFlag = 0;
					if (token_table[i]->operand[0] != NULL) {
						for (int j = 0; j < strlen(token_table[i]->operand[0]); j++) {
							tokenTemp[tempIndex++] = token_table[i]->operand[0][j];
							if (token_table[i]->operand[0][j] == '-' || token_table[i]->operand[0][j] == '+') {
								tokenTemp[tempIndex - 1] = '\0';
								for (int k = 0; k < extrefIndex; k++) {
									if (strcmp(tokenTemp, extref[k]) == 0) {
										modify[modifyIndex++] = i;
										extrefFlag = 1;
										break;
									}
								}

								if (extrefFlag == 1) {
									break;
								}
							}
						}
					}

					if(extrefFlag != 1){
						for (int j = 0; j < extrefIndex; j++) {
							for (int k = 0; k < 3; k++) {
								if (token_table[i]->operand[k] != NULL) {
									if (strcmp(token_table[i]->operand[k], extref[j]) == 0) {
										modify[modifyIndex++] = i;
									}
								}
								else {
									break;
								}
							}
						}
					}
					i++;
				}

				
			}
			else {

				//store extref operand
				for (int j = 0; j < extrefIndex; j++) {
					for (int k = 0; k < 3; k++) {
						if (token_table[i]->operand[k] != NULL) {
							if (strcmp(token_table[i]->operand[k], extref[j]) == 0) {
								modify[modifyIndex++] = i;
							}
						}
						else {
							break;
						}
					}
				}
			}
		}
	}
}


