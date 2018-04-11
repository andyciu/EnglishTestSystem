#include <stdio.h>
#include <stdlib.h>

//====================================
void ETSUMPUsercreate(void);
void ETSUMPUseredit(int );
void ETSUMPUserdelete(void);
//====================================
void helloworld(void){
	system("cls");
	printf("\n\t\t\t英文測驗系統使用者管理程式\n");
	printf("\t\tEnglish Test System User Management Program V1.0\n\t\t\t\t\t\t\t   2015 By AndyCiu.\n");
}

void ETSUMPmainmenu(void){
	char input;
	extern int ETSUsermode;
	if(ETSUsermode==1){
		while(1){
			printf("\n\n請選擇指令：\n");
			//=================
			printf("1.修改使用者之密碼\n");
			//=================
			printf("0.離開\n");
			//=================
			printf(">");
			fflush(stdin);
			input=getche();
			switch(input){
				case '1':
					ETSUMPUseredit(1);
					break;
				case '0':
					exit(0);
				default:
					printf("\n輸入錯誤!請重新輸入。\n");
			}
		}
	}
	else{
		while(1){
			printf("\n\n請選擇指令：\n");
			//=================
			printf("1.新增使用者\n");
			printf("2.修改使用者\n");
			printf("3.修改自身帳號之密碼\n");
			printf("4.刪除使用者\n");
			//=================
			printf("0.離開\n");
			//=================
			printf(">");
			fflush(stdin);
			input=getche();
			switch(input){
				case '1':
					ETSUMPUsercreate();
					break;
				case '2':
					ETSUMPUseredit(2);
					break;
				case '3':
					ETSUMPUseredit(1);
					break;
				case '4':
					ETSUMPUserdelete();
					break;
				case '0':
					exit(0);
				default:
					printf("\n輸入錯誤!請重新輸入。\n");
			}
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
