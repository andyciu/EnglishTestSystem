#include <stdio.h>
#include <stdlib.h>

//====================================
void ETSUMPUsercreate(void);
void ETSUMPUseredit(int );
void ETSUMPUserdelete(void);
//====================================
void helloworld(void){
	system("cls");
	printf("\n\t\t\t�^�����t�ΨϥΪ̺޲z�{��\n");
	printf("\t\tEnglish Test System User Management Program V1.0\n\t\t\t\t\t\t\t   2015 By AndyCiu.\n");
}

void ETSUMPmainmenu(void){
	char input;
	extern int ETSUsermode;
	if(ETSUsermode==1){
		while(1){
			printf("\n\n�п�ܫ��O�G\n");
			//=================
			printf("1.�ק�ϥΪ̤��K�X\n");
			//=================
			printf("0.���}\n");
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
					printf("\n��J���~!�Э��s��J�C\n");
			}
		}
	}
	else{
		while(1){
			printf("\n\n�п�ܫ��O�G\n");
			//=================
			printf("1.�s�W�ϥΪ�\n");
			printf("2.�ק�ϥΪ�\n");
			printf("3.�ק�ۨ��b�����K�X\n");
			printf("4.�R���ϥΪ�\n");
			//=================
			printf("0.���}\n");
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
					printf("\n��J���~!�Э��s��J�C\n");
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
				printf("��J���~!�Э��s��J�C\n");
		}
	}
}
