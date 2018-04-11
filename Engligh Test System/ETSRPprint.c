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
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.瀏覽測驗結果紀錄檔\n");
		printf("2.檢視之前測驗歷史作答紀錄\n");
		//=================
		printf("0.回到主選單\n");
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
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}

char* ETSRPtestmodechinese(int testmode){
	switch(testmode){
		case 1:
			return "綜合測驗";
			break;
		case 2:
			return "單字測驗";
			break;
		case 3:
			return "填充測驗";
			break;
		case 4:
			return "選擇測驗";
			break;
		case 5:
			return "閱\讀測驗";
			break;
	}
}

char* QuestionTrueFalseChinese(int num){
	switch(num){
		case 0:
			return "答錯";
			break;
		case 1:
			return "答對";
			break;
	}
}

void ETSRPrecordmenu1(char *testtime){
	char modestr[10];
	extern char ETSLoginUserName[999];
	system("cls");
	printf("英文測驗系統>>測驗紀錄管理>>觀看紀錄\t    測驗時間:%s\n",testtime);
	printf("使用者:%s\n\n",ETSLoginUserName);
}
