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
	int i = 0;
	token_line = 0;

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
	make_objectcode(NULL);
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
			int flag = 0;//No Label
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
	char* temp = (char*)malloc(sizeof(char) * 128);
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

	char* token = (char*)malloc(sizeof(char) * 64);
	token = strtok(temp, "\t");

	while (token != NULL) {
		int i = 0;
		int operandNumber = -1;//Check operand Number in op code table, initialize is No operator
		int realOperandNumber = 0;//Count input operand
		int opTableIndex = 0;
		char* operandToken = (char*)malloc(sizeof(char) * 10);

		switch (flag) {
		case 0:
			token_table[token_line]->label = (char*)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(token_table[token_line]->label, token);
			flag++;
			break;
		case 1:
			token_table[token_line]->operator_ = (char*)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(token_table[token_line]->operator_, token);
			flag++;
			break;
		case 2:
			//
			//instruction set�� ã�Ƽ� operand�� ��� �˾Ƴ���
			//operand ������ŭ token_table�� �ִ� operand�� �Է¹޴´�
			//operand ������ŭ �Է��� ���ٸ� ��� �Է� ���� �� break;
			//
			for (i = 0; i < 3; i++) {
				token_table[token_line]->operand[i] = NULL;
			}
			
			opTableIndex = search_opcode(token_table[token_line]->operator_);
			if (opTableIndex == -1) {
				//No operator and No operand
				operandNumber = -1;
			}
			else {
				//operator exist and store operand Number
				operandNumber = inst[opTableIndex]->ops;
			}

			if (operandNumber == -1) {
				token_table[token_line]->operand[0] = (char*)malloc(sizeof(char) * strlen(token) + 1);
				if (token[strlen(token) - 1] == '\n') {
					token[strlen(token) - 1] = '\0';
				}
				strcpy(token_table[token_line]->operand[0], token);
			}
			else if(operandNumber == 0) {
				flag++;
				break;
			}
			else {
				int tokenIndex = 0;
				for (i = 0; i < strlen(token); i++) {
					if (token[i] == ',') {
						token_table[token_line]->operand[operandNumber] = (char*)malloc(sizeof(char) * strlen(operandToken) + 1);
						strncpy(token_table[token_line]->operand[operandNumber], operandToken, tokenIndex);
						token_table[token_line]->operand[operandNumber][tokenIndex] = '\0';
						tokenIndex = 0;
						operandNumber++;
					}
					else if (i == strlen(token) - 1) {
						operandToken[tokenIndex++] = token[i];
						token_table[token_line]->operand[operandNumber] = (char*)malloc(sizeof(char) * strlen(token) + 1);
						strncpy(token_table[token_line]->operand[operandNumber], operandToken, tokenIndex);
						token_table[token_line]->operand[operandNumber][tokenIndex] = '\0';
					}
					else {
						operandToken[tokenIndex++] = token[i];
					}
				}
			}

			flag++;
			break;
		case 3:
			token_table[token_line]->comment = (char*)malloc(sizeof(char) * strlen(token) + 1);
			strcpy(token_table[token_line]->comment, token);
			flag++;
			break;
		default:
			break;
		}

		token = strtok(NULL, "\t");
	}

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

int search_opcode(char *str){
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

	if (file_name != NULL) {
		FILE* fp;
		if ((fp = freopen(file_name, "w", stdout)) == NULL) {
			return;
		}
	}

	int i = 0;
	for (i = 0; i < token_line - 1; i++) {
		int j = 0;
		int operandNumber = 0;

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

		for (j = 0; j < inst_index; j++) {
			if (strcmp(token_table[i]->operator_, inst[j]->str) == 0) {
				printf("%02X", inst[j]->op);
			}
		}

		printf("\n");
	}

}


