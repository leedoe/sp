/*
* 화일명 : my_assembler.c
* 설  명 : 이 프로그램은 SIC/XE 머신을 위한 간단한 Assembler 프로그램의 메인루틴으로,
* 입력된 파일의 코드 중, 명령어에 해당하는 OPCODE를 찾아 출력한다.
*
*/

/*
*
* 프로그램의 헤더를 정의한다.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* my_assembler 프로그램의 의존적인 데이터들이 정의된 곳이다.
*/

#include "my_assembler.h"

/* -----------------------------------------------------------------------------------
* 설명 : 사용자로 부터 어셈블리 파일을 받아서 명령어의 OPCODE를 찾아 출력한다.
* 매계 : 실행 파일, 어셈블리 파일
* 반환 : 성공 = 0, 실패 = < 0
* 주의 : 현재 어셈블리 프로그램의 리스트 파일을 생성하는 루틴은 만들지 않았다.
*		   또한 중간파일을 생성하지 않는다.
* -----------------------------------------------------------------------------------
*/


int main(int args, char *arg[])
{
	if (init_my_assembler()< 0)
	{
		printf("init_my_assembler: 프로그램 초기화에 실패 했습니다.\n");
		return -1;
	}

	if (assem_pass1() < 0) {
		printf("assem_pass1: 패스1 과정에서 실패하였습니다.  \n");
		return -1;
	}
	if (assem_pass2() < 0) {
		printf(" assem_pass2: 패스2 과정에서 실패하였습니다.  \n");
		return -1;
	}

	//make_output("output") ; 
}
/* -----------------------------------------------------------------------------------
* 설명 : 프로그램 초기화를 위한 자료구조 생성 및 파일을 읽는 함수이다.
* 매계 : 없음
* 반환 : 정상종료 = 0 , 에러 발생 = -1
* 주의 : 각각의 명령어 테이블을 내부에 선언하지 않고 관리를 용이하게 하기
*		   위해서 파일 단위로 관리하여 프로그램 초기화를 통해 정보를 읽어 올 수 있도록
*		   구현하였다.
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
* 설명 : 어셈블리 코드를 위한 패스1과정을 수행하는 함수이다.
*		   패스1에서는..
*		   1. 프로그램 소스를 스캔하여 해당하는 토큰단위로 분리하여 프로그램 라인별 토큰
*		   테이블을 생성한다.
*
* 매계 : 없음
* 반환 : 정상 종료 = 0 , 에러 = < 0
* 주의 : 현재 초기 버전에서는 에러에 대한 검사를 하지 않고 넘어간 상태이다.
*	  따라서 에러에 대한 검사 루틴을 추가해야 한다.
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
* 설명 : 어셈블리 코드를 기계어 코드로 바꾸기 위한 패스2 과정을 수행하는 함수이다.
*		   패스 2에서는 프로그램을 기계어로 바꾸는 작업은 라인 단위로 수행된다.
*		   다음과 같은 작업이 수행되어 진다.
*		   1. 실제로 해당 어셈블리 명령어를 기계어로 바꾸는 작업을 수행한다.
* 매계 : 없음
* 반환 : 정상종료 = 0, 에러발생 = < 0
* 주의 :
* -----------------------------------------------------------------------------------
*/

static int assem_pass2(void)
{
	make_objectcode(NULL);
	return 0;
}
/* -----------------------------------------------------------------------------------
* 설명 : 머신을 위한 기계 코드목록 파일을 읽어 기계어 목록 테이블(inst_table)을
*        생성하는 함수이다.
* 매계 : 기계어 목록 파일
* 반환 : 정상종료 = 0 , 에러 < 0
* 주의 : 기계어 목록파일 형식은 다음과 같다.
*
*	===============================================================================
*		   | 이름 | 형식 | 기계어 코드 | 오퍼랜드의 갯수 | NULL|
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
* 설명 : 어셈블리 할 소스코드를 읽어오는 함수이다.
* 매계 : 어셈블리할 소스파일명
* 반환 : 정상종료 = 0 , 에러 < 0
* 주의 :
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
* 설명 : 소스 코드를 읽어와 토큰단위로 분석하고 토큰 테이블을 작성하는 함수이다.
*        패스 1로 부터 호출된다.
* 매계 : 소스코드의 라인번호
* 반환 : 정상종료 = 0 , 에러 < 0
* 주의 : my_assembler 프로그램에서는 라인단위로 토큰 및 오브젝트 관리를 하고 있다.
* -----------------------------------------------------------------------------------
*/

int token_parsing(int index)
{
	int flag = 0;
	int i;
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
			
			/*
			//symbol table
			strcpy(sym_table[sym_line].symbol, token);
			sym_table[sym_line].addr = locctr;
			*/

			flag++;
			break;
		case 1:
			token_table[token_line]->operator_ = (char*)malloc(sizeof(char) * strlen(token) + 1);

			if (token[strlen(token) - 1] == '\n') {
				token[strlen(token) - 1] = '\0';
				strcpy(token_table[token_line]->operator_, token);
			}
			else {
				token[strlen(token)] = '\0';
				strcpy(token_table[token_line]->operator_, token);
			}
			
			flag++;
			break;
		case 2:
			//
			//instruction set을 찾아서 operand가 몇갠지 알아낸다
			//operand 개수만큼 token_table에 있는 operand를 입력받는다
			//operand 개수만큼 입력이 없다면 모두 입력 받은 후 break;
			//
			for (i = 0; i < 3; i++) {
				token_table[token_line]->operand[i] = NULL;
			}
			
			/*
			if (token_table[token_line]->operator_[0] == '+') {
				char* temp = &token_table[token_line]->operator_[1];
				opTableIndex = search_opcode(temp);
				format = 4;
			}
			else {
				opTableIndex = search_opcode(token_table[token_line]->operator_);
				
				if (opTableIndex == -1) {
					format = 0;
				}
				else {
					format = inst[opTableIndex]->format;

					if (format == 34) {
						format = 3;
					}
				}
			}
			*/

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

			if (operandNumber == -1) {
				token_table[token_line]->operand[0] = (char*)malloc(sizeof(char) * strlen(token) + 1);
				if (token[strlen(token) - 1] == '\n') {
					token[strlen(token) - 1] = '\0';
				}
				strcpy(token_table[token_line]->operand[0], token);
				
				//if operator START, set locctr
				/*
				if (strcmp(token_table[token_line]->operator_, "START") == 0) {
					locctr = atoi(token);
					sym_table[sym_line].addr = locctr;
				}

				if (strcmp(token_table[token_line]->operator_, "RESW") == 0) {
					format = atoi(token) * 3;
				}
				else if (strcmp(token_table[token_line]->operator_, "RESB") == 0) {
					format = atoi(token);
				}
				else if (strcmp(token_table[token_line]->operator_, "BYTE") == 0) {
					format = 1;
				}
				else if (strcmp(token_table[token_line]->operator_, "WORD") == 0) {
					format = 3;
				}
				*/
			}
			else if (operandNumber == 0) {
				flag++;
				break;
			}
			else {
				int tokenIndex = 0;
				for (i = 0; i < strlen(token); i++) {
					if (token[i] == ',' || token[i] == '-') {
						token_table[token_line]->operand[operandNumber-1] = (char*)malloc(sizeof(char) * strlen(operandToken) + 1);
						strncpy(token_table[token_line]->operand[operandNumber - 1], operandToken, tokenIndex);
						token_table[token_line]->operand[operandNumber - 1][tokenIndex] = '\0';
						tokenIndex = 0;
						operandNumber++;
					}
					else if (i == strlen(token) - 1) {
						operandToken[tokenIndex++] = token[i];
						token_table[token_line]->operand[operandNumber - 1] = (char*)malloc(sizeof(char) * strlen(token) + 1);
						
						if (token[strlen(token) - 1] == '\n') {
							operandToken[strlen(token) - 1] = '\0';
							strcpy(token_table[token_line]->operand[operandNumber - 1], operandToken);
						}
						else {
							operandToken[strlen(token)] = '\0';
							strcpy(token_table[token_line]->operand[operandNumber - 1], operandToken);
						}

						//리터럴 테이블에 저장
						/*
						if (token[0] == '=') {
							int i = 0;
							int literal_flag = 0;
							for (i = 0; i < literal_num; i++) {
								if (strcmp(lit_table[i].name, token) == 0) {
									literal_flag = 1;
									break;
								}
							}
							
							if (literal_flag == 0) {
								int i;

								strcpy(lit_table[literal_num].name, token);

								//literal hex or character
								if (token[1] == 'X') {
									lit_table[literal_num].operandValue = (char*)malloc(sizeof(char) * (strlen(token) - 4) + 1);

									for (i = 3; i < strlen(token) - 1; i++) {
										lit_table[literal_num].operandValue[(i - 3)] = token[i];
									}
									lit_table[literal_num].operandValue[strlen(token) - 4] = '\0';
								}
								else if (token[1] == 'C') {
									lit_table[literal_num].operandValue = (char*)malloc(sizeof(char) * (strlen(token) - 4) * 2 + 1);

									for (i = 3; i < strlen(token) - 1; i++) {
										sprintf(&lit_table[literal_num].operandValue[(i - 3) * 2], "%X", token[i]);
									}
								}

								lit_table[literal_num].length = strlen(token) - 3;
								lit_table[literal_num].address = locctr;
								literal_num++;
							}
						}

						*/
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

	//locctr += format;
	token_table[token_line]->locctr = locctr;

	int add = 0;
	char* operator_ = token_table[token_line]->operator_;

	//set locctr, set add value
	if (strcmp(operator_, "START") == 0) {
		locctr = atoi(token_table[token_line]->operand[0]);
		token_table[token_line]->locctr = locctr;
	}
	else if (strcmp(operator_, "CSECT") == 0) {
		locctr = 0;
		token_table[token_line]->locctr = 0;
	}
	else if (strcmp(operator_, "EQU") == 0) {
		//LOC가 아닌 값으로 바꿔줘야함
	}
	else if (strcmp(operator_, "LTORG") == 0 || strcmp(operator_, "END") == 0) {
		//리터럴 풀에 있는 리터럴을 메모리 할당
	}
	else {
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

	//if label exist, input symbol table
	if (strcmp(token_table[token_line]->label, "") != 0) {
		strcpy(sym_table[sym_line].symbol, token_table[token_line]->label);
		sym_table[sym_line].addr = locctr;
	}



	locctr += add;
	sym_line++;
	token_line++;


	free(temp);

	return 0;
}
/* -----------------------------------------------------------------------------------
* 설명 : 입력 문자열이 기계어 코드인지를 검사하는 함수이다.
* 매계 : 토큰 단위로 구분된 문자열
* 반환 : 정상종료 = 기계어 테이블 인덱스, 에러 < 0
* 주의 :
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
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
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


