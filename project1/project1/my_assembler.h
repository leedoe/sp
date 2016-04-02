/*
* my_assembler �Լ��� ���� ���� ���� �� ��ũ�θ� ��� �ִ� ��� �����̴�.
*
*/
#define MAX_INST 256
#define MAX_LINES 5000

#define MAX_COLUMNS 4
#define MAX_OPERAND 3

/*
* ���� ��� ���Ϸ� ���� ������ �޾ƿ� �����ϴ� ���� ��ȯ ���̺��̴�.
* �ش� ������ ������ ��ū���� ���� ����ϰ� �ִ�.
*/
struct inst_struct {
	char *str;
	unsigned char op;
	int format;
	int ops;
};
typedef struct inst_struct inst_struct;
inst_struct *inst[MAX_INST];
int inst_index;

/*
* ����� �� �ҽ��ڵ带 ��ū ������ �����ϴ� ���̺��̴�.
* ���� ������ �ҽ� ���� ������ �����Ǿ�����.
*/
char *input_data[MAX_LINES];
static int line_num;

int label_num;

struct token_unit {
	char *label;
	char *operator_;
	char *operand[MAX_OPERAND];
	char *comment;
};

typedef struct token_unit token;
token *token_table[MAX_LINES];
static int token_line;



/*
* �ɺ��� �����ϴ� ����ü�̴�.
* �ɺ� ���̺��� �ɺ� �̸�, �ɺ��� ��ġ�� �����ȴ�.
*/
struct symbol_unit {
	char symbol[10];
	int addr;
};

typedef struct symbol_unit symbol;
symbol sym_table[MAX_LINES];

static int locctr;
//--------------

static char *input_file;
static char *output_file;

int init_my_assembler(void);
static int assem_pass1(void);
static int assem_pass2(void);
int init_inst_file(char *inst_file);
int init_input_file(char *input_file);
int search_opcode(char *str);
void make_objectcode(char *file_name);