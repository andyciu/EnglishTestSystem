#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\\ETSUMPpersoncheckheader.h"
//====================================
int wordpersoncheckyesno(char *);
void ETSUMPCreateuserdatabase(void);
int ETSUMPUserLogin(int );
char* ETSUMPLoginmodeChinese(int );
void helloworld(void);
//====================================
char ETSLoginUserName[999];
int ETSUsermode;
//===================================
void SystemUserLogin(void){
	int loginnum=0;
	extern char ETSLoginUserName[999];
	extern int ETSUsermode;
	//========================
	BOOKlogintry:
	loginnum=ETSUMPUserLogin(2);
	if(loginnum==-1){
		printf("系統查無使用者登入檔，依預設模式登入。\n");
		if(ETSUMPUserLogin(3)==3){
			goto BOOKloginsuccess;
		}
		else{
			goto BOOKloginfail;
		}
	}
	else if(loginnum>0){
		goto BOOKloginsuccess;
	}
	else{
		goto BOOKloginfail;
	}
	//================
	BOOKloginfail:
	printf("登入失敗，使用者名稱或密碼輸入錯誤。\n");
	if(wordpersoncheckyesno("是否重試?")==1){
		goto BOOKlogintry;
	}
	else exit(1);
	//================
	BOOKloginsuccess:
	helloworld();
	printf("登入成功\!  使用者：%s  身分別：%s\n",ETSLoginUserName,ETSUMPLoginmodeChinese(ETSUsermode));
	//===============
	if(loginnum==-1) ETSUMPCreateuserdatabase();
	
}

void ETSUMPCreateuserdatabase(void){
	FILE *fptr;
	char pathname[999];
	PERSONDATAMAIN PersonDatabaseMain[1];
	PERSONDATAUSER PersonDatabaseUser[1];
	//======================
	sprintf(pathname,"..\\Database\\userconfig.etu");
	if((fptr = fopen(pathname,"wb"))!=NULL){
		printf("\n已建立使用者紀錄檔。");
		//================
		PersonDatabaseMain[0].usernum=1;
		fwrite(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		//================
		sprintf(PersonDatabaseUser[0].username,"root");
		sprintf(PersonDatabaseUser[0].password,"root");
		PersonDatabaseUser[0].usermode=3;
		fwrite(PersonDatabaseUser,sizeof(PERSONDATAUSER),1,fptr);
		//================
		fclose(fptr);
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
