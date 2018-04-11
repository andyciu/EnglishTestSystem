#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\\ETSUMPpersoncheckheader.h"
//====================================
int ETSUMPUserLogin(int );
//====================================
char ETSLoginUserName[999];
int ETSUsermode;
//===================================
void personcheckmain(void){
	int usernum;
	BOOKlogintry:
	usernum=ETSUMPUserLogin(1);
	if(usernum>0){
		if(usernum==1){
			printf("\n您目前的權限不足...請聯絡系統管理員。\n");
			exit(1);
		}
		helloworld();
		printf("\n歡迎%s!\n",ETSLoginUserName);
	}
	else{
		printf("登入失敗，使用者名稱或密碼輸入錯誤。\n");
		if(wordpersoncheckyesno("是否重試?")==1){
			goto BOOKlogintry;
		}
		else exit(1);
	}
}
//========================================================
int ETSUMPUserLogin(int mode){
	FILE *fptr;
	char pathname[999];
	char input[100],inputusername[100],inputpassword[100];
	PERSONDATAMAIN PersonDatabaseMain[1];
	PERSONDATAUSER *PersonDatabaseUser;
	int num1,i=1,usermodenum;
	//=========================
	sprintf(pathname,"..\\Database\\userconfig.etu");
	if((fptr = fopen(pathname,"rb"))!=NULL){
		PersonDatabaseMain[0].usernum=0;
		fread(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		num1=PersonDatabaseMain[0].usernum;
		if(num1<=0){
			fclose(fptr);
			return 0;
		}
		//=============
		PersonDatabaseUser=(PERSONDATAUSER *) malloc(num1*sizeof(PERSONDATAUSER));
		fseek(fptr,-num1*sizeof(PERSONDATAUSER),SEEK_END);
		fread(PersonDatabaseUser,sizeof(PERSONDATAUSER),num1,fptr);
		//=============
		i=1;
		while(i<=2){
			if(i==1) printf("請輸入使用者名稱：");
			else printf("請輸入密碼：");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0' && i==1){
				printf("輸入錯誤!請再試一遍...\n");
				continue;
			}
			else{
				if(i==1) sprintf(inputusername,"%s",input);
				else sprintf(inputpassword,"%s",input);
				i++;
			}
		}
		//===============
		for(i=0;i<num1;i++){
			if(strcmp((PersonDatabaseUser+i)->username,inputusername)==0 && strcmp((PersonDatabaseUser+i)->password,inputpassword)==0){
				usermodenum=(PersonDatabaseUser+i)->usermode;
				sprintf(ETSLoginUserName,"%s",(PersonDatabaseUser+i)->username);
				ETSUsermode=(PersonDatabaseUser+i)->usermode;
				free(PersonDatabaseUser);
				fclose(fptr);
				return usermodenum;
			}
		}
		//================
		free(PersonDatabaseUser);
		fclose(fptr);
		return 0;
	}
	if(mode==2) return -1;
	else if(mode==3){
		i=1;
		while(i<=2){
			if(i==1) printf("請輸入使用者名稱：");
			else printf("請輸入密碼：");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0' && i==1){
				printf("輸入錯誤!請再試一遍...\n");
				continue;
			}
			else{
				if(i==1) sprintf(inputusername,"%s",input);
				else sprintf(inputpassword,"%s",input);
				i++;
			}
		}
		if(strcmp("root",inputusername)==0 && strcmp("root",inputpassword)==0){
			sprintf(ETSLoginUserName,"root");
			ETSUsermode=3;
			return 3;
		}
	}
	//===========
	return 0;
}

char* ETSUMPLoginmodeChinese(int usermode){
	switch(usermode){
		case 1:
			return "學生";
		case 2:
			return "教師";
		case 3:
			return "系統管理員";
	}
}
//=====================================================
