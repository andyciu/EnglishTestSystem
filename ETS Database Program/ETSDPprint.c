#include <stdio.h>
#include <stdlib.h>
//====================================
void menu1(void);
void menu2(void);
void menu3(void);
void word1create(void);
void word1edit(void);
void word1del(void);
void word2create(void);
void word2edit(void);
void word2del(void);
void word3create(void);
void word3edit(void);
void word3del(void);
void word4create(void);
void word4edit(void);
void word4del(void);
void helloworld(void);
//====================================

void helloworld(void){
	system("cls");
	printf("\n\t\t\t英文測驗系統題庫管理程式\n");
	printf("\t\t English Test System Database Program V1.0\n\t\t\t\t\t\t\t     2015 By AndyCiu.\n");
}

void mainmenu(void){
	char num;
	//=================
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.新增題目\n");
		printf("2.修改題目\n");
		printf("3.刪除題目\n");
		//=================
		printf("0.離開\n");
		//=================
		printf(">");
		fflush(stdin);
		//scanf("%c",&num);
		num=getche();
		switch(num){
			case '1':
				menu1();
				break;
			case '2':
				menu2();
				break;
			case '3':
				menu3();
				break;
			case '0':
				exit(0);
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}

void menu1(void){  //新增題目類 
	char num;
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.新增單字題\n");
		printf("2.新增填充題\n");
		printf("3.新增選擇題\n");
		printf("4.新增閱\讀題\n");
		//=================
		printf("0.回到主選單\n");
		//=================
		printf(">");
		fflush(stdin);
		//scanf("%c",&num);
		num=getche();
		switch(num){
			case '1':
				word1create();
				break;
			case '2':
				word2create();
				break;
			case '3':
				word3create();
				break;
			case '4':
				word4create();
				break;
			case '0':
				helloworld();
				return;
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}
void menu2(void){  //修改題目類 
	char num;
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.修改單字題\n");
		printf("2.修改填充題\n");
		printf("3.修改選擇題\n");
		printf("4.修改閱\讀題\n");
		//=================
		printf("0.回到主選單\n");
		//=================
		printf(">");
		fflush(stdin);
		//scanf("%c",&num);
		num=getche();
		switch(num){
			case '1':
				word1edit();
				break; 
			case '2':
				word2edit();
				break;
			case '3':
				word3edit();
				break;
			case '4':
				word4edit();
				break;
			case '0':
				helloworld();
				return;
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}
void menu3(void){  //刪除題目類 
	char num;
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.刪除單字題\n");
		printf("2.刪除填充題\n");
		printf("3.刪除選擇題\n");
		printf("4.刪除閱\讀題\n");
		//=================
		printf("0.回到主選單\n");
		//=================
		printf(">");
		fflush(stdin);
		//scanf("%c",&num);
		num=getche();
		switch(num){
			case '1':
				word1del();
				break;
			case '2':
				word2del();
				break;
			case '3':
				word3del();
				break;
			case '4':
				word4del();
				break;
			case '0':
				helloworld();
				return;
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}

int wordpersoncheckyesno(char *str1){
	char input;
	printf("%s(Y/N)\n",str1);
	while(1){
		printf(">");
		fflush(stdin);
		input=getche();
		printf("\n");
		switch(input){
			case 'Y':
			case 'y':
				return 1;
			case 'N':
			case 'n':
				return 2;
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}
int wordpersoncheckabcd(char *str1){
	char answern;
	while(1){
		printf("%s",str1);
		fflush(stdin);
		scanf("%c",&answern);
		switch(answern){
			case 'A':
			case 'a':
				return 1;
			case 'B':
			case 'b':
				return 2;
			case 'C':
			case 'c':
				return 3;
			case 'D':
			case 'd':
				return 4;
			default:
				printf("輸入答案錯誤!請再試一遍:\n");
		}
	}
}

void wordpersoncheckstring(char *qns,char *str2){
	char answern[100];
	while(1){
		printf("%s",qns);
		//printf(">");
		fflush(stdin);
		//scanf("%s",answern);
		gets(answern);
		if(answern[0]=='\0'){
			printf("輸入答案錯誤!請再試一遍:\n");
		}
		else{
			sprintf(str2,"%s",answern);
			return;
		}
	}
}
