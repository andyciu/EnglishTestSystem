struct worddatanumstruct{
	int datanum;
};
typedef struct worddatanumstruct WORDDATANUM;
//======================== 
struct wordt{
	char eng[30];
	char chi[99];
};
typedef struct wordt WORDTR;
struct wordtnode{
	char eng[30];
	char chi[99];
	char databasename[255];
	int datanum;
	struct wordtnode *next;
};
typedef struct wordtnode WORDTRNODE;
struct wordtnodeEx{
	char useranswer[100];
	int useranswercheck;
	int useranstruefalse;
	struct wordtnode *nodeptr;
	struct wordtnodeEx *next;
};
typedef struct wordtnodeEx WORDTRNODEEX;
//========================
struct wordt2{
	char mainstr[100];
	char ans[30];
};
typedef struct wordt2 WORDTR2;
struct wordt2node{
	char mainstr[100];
	char ans[30];
	char databasename[255];
	int datanum;
	struct wordt2node *next;
};
typedef struct wordt2node WORDTR2NODE;
struct wordt2nodeEx{
	char useranswer[100];
	int useranswercheck;
	int useranstruefalse;
	struct wordt2node *nodeptr;
	struct wordt2nodeEx *next;
};
typedef struct wordt2nodeEx WORDTR2NODEEX;
//========================
struct wordt3{
	char question[200];
	char a1[50];
	char a2[50];
	char a3[50];
	char a4[50];
	int answer;
};
typedef struct wordt3 WORDTR3;
struct wordt3node{
	char question[200];
	char a1[50];
	char a2[50];
	char a3[50];
	char a4[50];
	int answer;
	char databasename[255];
	int datanum;
	struct wordt3node *next;
};
typedef struct wordt3node WORDTR3NODE;
struct wordt3nodeEx{
	int useranswer;
	int useranswercheck;
	int useranstruefalse;
	struct wordt3node *nodeptr;
	struct wordt3nodeEx *next;
};
typedef struct wordt3nodeEx WORDTR3NODEEX;
//========================
struct wordt4b{
	char filename[255];
	int questionnum;
};
struct wordt4a{
	char question[200];
	char a1[50];
	char a2[50];
	char a3[50];
	char a4[50];
	int answer;
};
struct wordt4anode{
	char question[200];
	char a1[50];
	char a2[50];
	char a3[50];
	char a4[50];
	int answer;
	int useranswer;
	int useranswercheck;
	int useranstruefalse;
	struct wordt4anode *next;
};
struct wordt4c{
	char filename[255];
	int questionnum;
	char databasefilename[255];
	struct wordt4c *next;
};
struct wordt4cEx{
	struct wordt4c *nodeptr;
	struct wordt4cEx *next;
};
typedef struct wordt4a WORDTR4;
typedef struct wordt4b WORDTR4MAIN;
typedef struct wordt4anode WORDTR4NODE;
typedef struct wordt4c WORDTR4NORMAL;
typedef struct wordt4cEx WORDTR4NORMALEX;
//========================使用者記錄檔 
struct persontest{
	char username[999];
	char testtime[100];
	int mode;
	int testtotnum;
	int score;
};
typedef struct persontest PERSONTESTHISTORY;

struct persontestnode{
	char username[999];
	char testtime[100];
	int mode;
	int testtotnum;
	int score;
	char dataname[255];
	struct persontestnode *next;
};
typedef struct persontestnode PERSONTESTHISTORYNODE;

struct testrecordstruct{
	int modenum;
	char databasename[255];
	int datanum;
	char answer[30];
	int useranstruefalse;
};
typedef struct testrecordstruct PERSONTESTRECORD;
//===============================


