#include <stdio.h>
#include <stdlib.h>
//====================================
void helloworld(void);
void mainmenu(void);
void ETSRPviewfirst(int );
void ETSRPsystemNodeReset(void);
//====================================
void ETSRPmainmenu(void){
	char input;
	while(1){
		printf("\n\n�п�ܫ��O�G\n");
		//=================
		printf("1.�s�����絲�G������\n");
		printf("2.�˵����e������v�@������\n");
		//=================
		printf("0.�^��D���\n");
		//=================
		printf(">");
		fflush(stdin);
		input=getche();
		switch(input){
			case '1':
				ETSRPsystemNodeReset();
				ETSRPviewfirst(1);
				break;
			case '2':
				ETSRPsystemNodeReset();
				ETSRPviewfirst(2);
				break;
			case '0':
				helloworld();
				return;
			default:
				printf("��J���~!�Э��s��J�C\n");
		}
	}
}

char* ETSRPtestmodechinese(int testmode){
	switch(testmode){
		case 1:
			return "��X����";
			break;
		case 2:
			return "��r����";
			break;
		case 3:
			return "��R����";
			break;
		case 4:
			return "��ܴ���";
			break;
		case 5:
			return "�\\Ū����";
			break;
	}
}

char* QuestionTrueFalseChinese(int num){
	switch(num){
		case 0:
			return "����";
			break;
		case 1:
			return "����";
			break;
	}
}

void ETSRPrecordmenu1(char *testtime){
	char modestr[10];
	extern char ETSLoginUserName[999];
	system("cls");
	printf("�^�����t��>>��������޲z>>�[�ݬ���\t    ����ɶ�:%s\n",testtime);
	printf("�ϥΪ�:%s\n\n",ETSLoginUserName);
}
