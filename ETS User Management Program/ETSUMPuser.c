#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\\ETSUMPpersoncheckheader.h"
//====================================
int wordpersoncheckyesno(char *);
int ETSUMPUserLogin(int );
char* ETSUMPLoginmodeChinese(int );
//====================================
void ETSUMPUsercreate(void){
	PERSONDATAMAIN PersonDatabaseMain[1];
	PERSONDATAUSER *PersonDatabaseUser,PersonDatabaseUsernew[1];
	FILE *fptr;
	char pathname[999];
	char input[100];
	int inputnum,num1,i;
	extern int ETSUsermode;
	//=====================
	sprintf(pathname,"..\\Database\\userconfig.etu");
	if((fptr = fopen(pathname,"r+b"))!=NULL){
		PersonDatabaseMain[0].usernum=0;
		fread(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		num1=PersonDatabaseMain[0].usernum;
		if(num1<=0){
			goto BOOKopendatafail;
		}
		//=============
		PersonDatabaseUser=(PERSONDATAUSER *) malloc(num1*sizeof(PERSONDATAUSER));
		fseek(fptr,-num1*sizeof(PERSONDATAUSER),SEEK_END);
		fread(PersonDatabaseUser,sizeof(PERSONDATAUSER),num1,fptr);
		//=============
		BOOKusercreate1:
		i=1;
		while(i<=2){
			if(i==1) printf("\n\n請輸入新的使用者名稱：");
			else printf("請輸入新使用者之密碼：");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0' && i==1){
				printf("輸入錯誤!請再試一遍...\n");
				continue;
			}
			else{
				if(i==1) sprintf(PersonDatabaseUsernew[0].username,"%s",input);
				else sprintf(PersonDatabaseUsernew[0].password,"%s",input);
				i++;
			}
		}
		//===============
		printf("比對中....\n");
		for(i=0;i<num1;i++){
			if(strcmp((PersonDatabaseUser+i)->username,PersonDatabaseUsernew[0].username)==0){
				if(wordpersoncheckyesno("您所輸入使用者已存在!是否重試?")==1){
					goto BOOKusercreate1;
				}
				else{
					return;
				}
			}
		}
		//================
		printf("比對完成。\n");
		if(ETSUsermode==3){
			while(1){
				printf("請輸入使用者身分別：\n(1.學生/2.教師/3.系統管理員)\n>");
				fflush(stdin);
				scanf("%d",&inputnum);
				//=================
				if(inputnum<=0 || inputnum>3){
					printf("輸入錯誤!請重新輸入...\n");
					continue;
				}
				else{
					PersonDatabaseUsernew[0].usermode=inputnum;
					break;
				}
			}
		}
		else if(ETSUsermode==2){
			PersonDatabaseUsernew[0].usermode=1;
		}
		else{
			printf("身分別辨識錯誤!請聯絡系統管理員...\n");
		}
		//==================================
		rewind(fptr);
		PersonDatabaseMain[0].usernum=++num1;
		fwrite(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		//==================================
		fseek(fptr,0L,SEEK_END);
		fwrite(PersonDatabaseUsernew,sizeof(PERSONDATAUSER),1,fptr);
		printf("新增完成! User:%s 身分別:%s\n\n",PersonDatabaseUsernew[0].username,ETSUMPLoginmodeChinese(PersonDatabaseUsernew[0].usermode));
		fclose(fptr);
		system("pause");
	}
	else{
		BOOKopendatafail:
		printf("開啟使用者紀錄檔失敗!請聯絡系統管理員...\n");
		exit(2);
	}
}

void ETSUMPUseredit(int mode){
	PERSONDATAMAIN PersonDatabaseMain[1];
	PERSONDATAUSER *PersonDatabaseUser,PersonDatabaseUsernew[1];
	FILE *fptr;
	char pathname[999];
	char input[100],inputusername[100],inputpassword[100];
	int inputnum,usernum,num1,i;
	extern int ETSUsermode;
	extern char ETSLoginUserName[999];
	//=====================
	sprintf(pathname,"..\\Database\\userconfig.etu");
	if((fptr = fopen(pathname,"r+b"))!=NULL){
		PersonDatabaseMain[0].usernum=0;
		fread(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		num1=PersonDatabaseMain[0].usernum;
		if(num1<=0){
			goto BOOKopendatafail;
		}
		//=============
		PersonDatabaseUser=(PERSONDATAUSER *) malloc(num1*sizeof(PERSONDATAUSER));
		fseek(fptr,-num1*sizeof(PERSONDATAUSER),SEEK_END);
		fread(PersonDatabaseUser,sizeof(PERSONDATAUSER),num1,fptr);
		//======================================================================
		if(ETSUsermode>1 && mode==2){
			printf("\n\n目前使用者資料如下：\n");
			for(i=0;i<num1;i++){
				if(ETSUsermode==3 || (ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1)){
					printf("%d.User:%s  身分別:%s\n",i+1,(PersonDatabaseUser+i)->username,ETSUMPLoginmodeChinese((PersonDatabaseUser+i)->usermode));
				}
			} 
		}	
		//===============
		if(ETSUsermode==1 || mode==1){
			while(1){
				BOOKeditmode1:
				printf("\n\n請輸入原密碼：");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0'){
					printf("輸入錯誤!請再試一遍...\n");
					continue;
				}
				else{
					sprintf(inputpassword,"%s",input);
					for(i=0;i<num1;i++){
						if(strcmp(ETSLoginUserName,(PersonDatabaseUser+i)->username)==0 && strcmp((PersonDatabaseUser+i)->password,inputpassword)==0){
							usernum=i;
							break;
						}
						else if(i==num1-1){
							if(wordpersoncheckyesno("輸入錯誤!是否重試?")==1){
								goto BOOKeditmode1;
							}
							else{
								return;
							}
						}
		
					}
					break;
				}
			}
			//=========================
			while(1){
				printf("請輸入修改後之密碼：");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0'){
					printf("輸入錯誤!請再試一遍...\n");
					continue;
				}
				else{
					sprintf(PersonDatabaseUsernew[0].password,"%s",input);
					sprintf(PersonDatabaseUsernew[0].username,"%s",ETSLoginUserName);
					goto BOOKeditwritedata;
				}
			}
			
		}
		if(ETSUsermode==3){
			while(1){
				printf("\n\n請輸入欲修改之使用者名稱：");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0'){
					printf("輸入錯誤!請再試一遍...\n");
					continue;
				}
				else{
					sprintf(inputusername,"%s",input);
					break;
				}
			}
			for(i=0;i<num1;i++){
				if(strcmp((PersonDatabaseUser+i)->username,inputusername)==0){
					usernum=i;
					printf("查詢成功\。"); 
					break;
				}
				else if(i==num1-1){
					printf("查詢失敗。系統查無此使用者...\n");
					return;
				} 
			}
		}
		else{
			i=1;
			while(i<=2){
				if(i==1) printf("\n\n請輸入欲修改之使用者名稱：");
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
					usernum=i;
					printf("登入成功\。");
					if((ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1) || (ETSUsermode==1 && (PersonDatabaseUser+i)->usermode==1 && strcmp(ETSLoginUserName,(PersonDatabaseUser+i)->username)==0)) ;
					else{
						printf("您目前的權限不足...請聯絡系統管理員。\n");
						return;
					} 
					break;
				}
				else if(i==num1-1){
					printf("查詢失敗。系統查無此使用者或輸入之使用者名稱及密碼錯誤...\n");
					return;
				}
			}
		}	
		//=========================
		BOOKuseredit1:
		if(strcmp((PersonDatabaseUser+usernum)->username,ETSLoginUserName)==0){
			printf("\n執行階段錯誤：目前查詢之帳號正在使用。\n");
			return;
		}
		//========================= 
		i=1;
		while(i<=2){
			if(i==1) printf("請輸入修改後之使用者名稱：");
			else printf("請輸入修改後之密碼：");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0' && i==1){
				printf("輸入錯誤!請再試一遍...\n");
				continue;
			}
			else{
				if(i==1) sprintf(PersonDatabaseUsernew[0].username,"%s",input);
				else sprintf(PersonDatabaseUsernew[0].password,"%s",input);
				i++;
			}
		}
		//===============
		printf("比對中....\n");
		for(i=0;i<num1;i++){
			if(i!=usernum){
				if(strcmp((PersonDatabaseUser+i)->username,PersonDatabaseUsernew[0].username)==0){
					if(wordpersoncheckyesno("您所輸入使用者已存在!是否重試?")==1){
						goto BOOKuseredit1;
					}
					else{
						return;
					}
				}
			} 	
		}
		printf("比對完成。\n");
		//==================================
		BOOKeditwritedata:
		if(ETSUsermode==3 && mode==2){
			while(1){
				printf("請輸入欲修改之使用者新身分別：\n(1.學生/2.教師/3.系統管理員)\n>");
				fflush(stdin);
				scanf("%d",&inputnum);
				//=================
				if(inputnum<=0 || inputnum>3){
					printf("輸入錯誤!請重新輸入...\n");
					continue;
				}
				else{
					PersonDatabaseUsernew[0].usermode=inputnum;
					break;
				}
			}
		}
		else{
			PersonDatabaseUsernew[0].usermode=(PersonDatabaseUser+usernum)->usermode;
		}
		//==================================
		fseek(fptr,-(num1-usernum)*sizeof(PERSONDATAUSER),SEEK_END);
		fwrite(PersonDatabaseUsernew,sizeof(PERSONDATAUSER),1,fptr);
		printf("修改完成! User:%s 身分別:%s\n\n",PersonDatabaseUsernew[0].username,ETSUMPLoginmodeChinese(PersonDatabaseUsernew[0].usermode));
		fclose(fptr);
		system("pause");
	}
	else{
		BOOKopendatafail:
		printf("開啟使用者紀錄檔失敗!請聯絡系統管理員...\n");
		exit(2);
	}
}

void ETSUMPUserdelete(void){
	PERSONDATAMAIN PersonDatabaseMain[1];
	PERSONDATAUSER *PersonDatabaseUser,PersonDatabaseUsernew[1];
	FILE *fptr;
	char pathname[999];
	char input[100],inputusername[100];
	int inputnum,num1,i,usernum;
	extern int ETSUsermode;
	extern char ETSLoginUserName[999];
	//=====================
	sprintf(pathname,"..\\Database\\userconfig.etu");
	if((fptr = fopen(pathname,"r+b"))!=NULL){
		PersonDatabaseMain[0].usernum=0;
		fread(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		num1=PersonDatabaseMain[0].usernum;
		if(num1<=0){
			goto BOOKopendatafail;
		}
		//=============
		PersonDatabaseUser=(PERSONDATAUSER *) malloc(num1*sizeof(PERSONDATAUSER));
		fseek(fptr,-num1*sizeof(PERSONDATAUSER),SEEK_END);
		fread(PersonDatabaseUser,sizeof(PERSONDATAUSER),num1,fptr);
		//=============
		printf("\n\n目前使用者資料如下：\n");
		for(i=0;i<num1;i++){
			if(ETSUsermode==3 || (ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1)){
				printf("%d.User:%s  身分別:%s\n",i+1,(PersonDatabaseUser+i)->username,ETSUMPLoginmodeChinese((PersonDatabaseUser+i)->usermode));
			}
		} 
		//=============
		BOOKuserdelete1:
		while(1){
			printf("請輸入欲刪除之使用者名稱：");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0'){
				printf("輸入錯誤!請再試一遍...\n");
				continue;
			}
			else{
				sprintf(inputusername,"%s",input);
				break;
			}
		}
		for(i=0;i<num1;i++){
			if(strcmp((PersonDatabaseUser+i)->username,inputusername)==0){
				usernum=i;
				printf("查詢成功\。");
				break;
			}
			else if(i==num1-1){
				printf("查詢失敗。系統查無此使用者...\n");
				return;
			} 
		}
		if(ETSUsermode==3 || (ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1)) ;
		else{
			printf("\n您目前的權限不足...請聯絡系統管理員。\n");
			return;
		}
		//===============
		if(strcmp((PersonDatabaseUser+usernum)->username,ETSLoginUserName)==0){
			printf("\n執行階段錯誤：目前查詢之帳號正在使用。\n");
			return;
		}
		//================
		if(num1>1){
			printf("\n使用者:%s  身分別:%s\n是否確認刪除使用者",(PersonDatabaseUser+usernum)->username,ETSUMPLoginmodeChinese((PersonDatabaseUser+usernum)->usermode));
		}
		else{
			printf("\n執行階段錯誤，目前使用者數已達最低標準下限。\n");
			return;
		}
		//==================================
		if(wordpersoncheckyesno("?")==1){
			fclose(fptr);
			if((fptr = fopen(pathname,"wb"))!=NULL){
				PersonDatabaseMain[0].usernum=--num1;
				fwrite(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
				//==============================
				for(i=0;i<num1+1;i++){
					if(i!=usernum){
						sprintf(PersonDatabaseUsernew[0].username,"%s",(PersonDatabaseUser+i)->username);
						sprintf(PersonDatabaseUsernew[0].password,"%s",(PersonDatabaseUser+i)->password);
						PersonDatabaseUsernew[0].usermode=(PersonDatabaseUser+i)->usermode;
						fwrite(PersonDatabaseUsernew,sizeof(PERSONDATAUSER),1,fptr);
					}
				}
				fclose(fptr);
			}
			printf("已完成刪除。\n");
			system("pause");
		}
		else{
			return;
		}
		
	}
	else{
		BOOKopendatafail:
		printf("開啟使用者紀錄檔失敗!請聯絡系統管理員...\n");
		exit(2);
	}
}
