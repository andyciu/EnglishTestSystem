#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include ".\\ETSprogramin.h"
//====================================
int ETSRPsearchfileChecknum(int );
int ETSRPcheckuser(char *,char *,int );
char* ETSRPtestmodechinese(int );
int ETSRPreadtestrecord(int ,int ,PERSONTESTRECORD *);
char* QuestionTrueFalseChinese(int );
void QusetionSecondprint(char *,char *);
int QuestionForthprint(char *);
void ETSRPviewsecond(int );
void ETSRPrecordmenu1(char *);
//====================================
PERSONTESTHISTORYNODE *UserTestHistoryNodeFirst=NULL; //紀錄瀏覽-使用者記錄檔鏈結串列(標頭) 
//====================================
void ETSRPviewfirst(int mode){
	FILE *fptr;
	int i=0;
	extern char ETSLoginUserName[999];
	extern int ETSUsermode;
	extern PERSONTESTHISTORYNODE *UserTestHistoryNodeFirst;
	PERSONTESTHISTORYNODE *UserTestHistoryNodePre, *UserTestHistoryNodeNow;
	//==========================
	if(ETSUsermode==1) printf("\n\n%s,您目前有%d筆測驗結果紀錄：\n",ETSLoginUserName,ETSRPsearchfileChecknum(1));
	else printf("\n\n%s,系統目前有%d筆測驗結果紀錄：\n",ETSLoginUserName,ETSRPsearchfileChecknum(2));
	//===========
	UserTestHistoryNodeNow=UserTestHistoryNodeFirst;
	while(UserTestHistoryNodeNow!=NULL){
		if(ETSUsermode==1) printf("%d.Time:%s   Mode:%s   Score:%d\n",++i,UserTestHistoryNodeNow->testtime,ETSRPtestmodechinese(UserTestHistoryNodeNow->mode),UserTestHistoryNodeNow->score);
		else printf("%d.User:%s  Time:%s   Mode:%s   Score:%d\n",++i,UserTestHistoryNodeNow->username,UserTestHistoryNodeNow->testtime,ETSRPtestmodechinese(UserTestHistoryNodeNow->mode),UserTestHistoryNodeNow->score);
		UserTestHistoryNodeNow=UserTestHistoryNodeNow->next;
	}
	if(mode==2){
		int input=0;
		while(1){
			printf("請輸入欲觀看測驗結果紀錄之編號：\n");
			printf(">");
			fflush(stdin);
			scanf("%d",&input);
			if(input==0){
				printf("輸入錯誤!請再試一遍...\n");
			}
			else if(input>i){
				printf("輸入的編號已超過最大值!請再試一遍...\n");
			}
			else{
				ETSRPviewsecond(input);
				break;
			}
		}
	}
	else{
		system("pause");
	}
	//==========================
}

void ETSRPviewsecond(int datanum){
	extern PERSONTESTHISTORYNODE *UserTestHistoryNodeFirst;
	PERSONTESTHISTORYNODE *UserTestHistoryNodePre, *UserTestHistoryNodeNow;
	PERSONTESTRECORD *PersonTestRecord;
	int i=1,j;
	FILE *fptr;
	char pathname[999];
	//=============================
	UserTestHistoryNodeNow=UserTestHistoryNodeFirst;
	while(UserTestHistoryNodeNow!=NULL){
		if(i==datanum){
			break;
		}
		else{
			UserTestHistoryNodeNow=UserTestHistoryNodeNow->next;
			i++;
		}
	}
	//===============================
	sprintf(pathname,"..\\Log\\%s",UserTestHistoryNodeNow->dataname);
	if((fptr = fopen(pathname,"rb"))!=NULL){
		PersonTestRecord=(PERSONTESTRECORD *) malloc((UserTestHistoryNodeNow->testtotnum)*sizeof(PERSONTESTRECORD));
		fseek(fptr,-(UserTestHistoryNodeNow->testtotnum)*sizeof(PERSONTESTRECORD),SEEK_END);
		fread(PersonTestRecord,sizeof(PERSONTESTRECORD),(UserTestHistoryNodeNow->testtotnum),fptr);
		//==================================
		for(j=0;j<(UserTestHistoryNodeNow->testtotnum);j++){
			ETSRPrecordmenu1(UserTestHistoryNodeNow->testtime);
			//====================
			if(ETSRPreadtestrecord((PersonTestRecord+j)->modenum,j+1,(PersonTestRecord+j))==1){
				printf("%d：該題讀取時發生錯誤...\n",j+1);
			}
			system("pause");
		}
	} 
}

int ETSRPsearchfileChecknum(int usermode){
	DIR * dir;
    DIR * dir2;
    struct dirent * ptr;
    int i,j,k,pnum=0;
    char pathname[999];
    char filenamestr[30];
    //==========================================
	sprintf(pathname,"..\\Log");
	dir =opendir(pathname);
    while((ptr = readdir(dir))!=NULL) {
        sprintf(pathname,"..\\Log\\%s",ptr->d_name);
        if((dir2 = opendir(pathname))==NULL) {  //開啟時不為資料夾之形式 
            //printf("%s: file(%s)\n", ptr->d_name,getfilestr(pathname));
            sprintf(filenamestr,"%s",getfilestr(pathname));
            if(strcmp(filenamestr,"etlog")==0){
				if(ETSRPcheckuser(pathname,ptr->d_name,usermode)==1){
					pnum++;
				}
			}
        } else {
            closedir(dir2);
        }
    }
    closedir(dir);
	return pnum;
}

int ETSRPcheckuser(char *pathname,char *filenamestr,int usermode){
	PERSONTESTHISTORY PersonTestHistory[1];
	extern PERSONTESTHISTORYNODE *UserTestHistoryNodeFirst;
	PERSONTESTHISTORYNODE *UserTestHistoryNodePre, *UserTestHistoryNodeNow;
	extern char ETSLoginUserName[999];
	FILE *fptr;
	if((fptr = fopen(pathname,"rb"))!=NULL){
		fread(PersonTestHistory,sizeof(PERSONTESTHISTORY),1,fptr);
		if((strcmp(PersonTestHistory[0].username,ETSLoginUserName)==0 && usermode==1) || (usermode==2)){
			UserTestHistoryNodeNow=UserTestHistoryNodeFirst;
			while(UserTestHistoryNodeNow!=NULL){
				UserTestHistoryNodePre=UserTestHistoryNodeNow;
				UserTestHistoryNodeNow=UserTestHistoryNodeNow->next;
			}
			UserTestHistoryNodeNow=(PERSONTESTHISTORYNODE *) malloc(sizeof(PERSONTESTHISTORYNODE));
			sprintf(UserTestHistoryNodeNow->dataname,"%s",filenamestr);
			sprintf(UserTestHistoryNodeNow->username,"%s",PersonTestHistory[0].username);
			sprintf(UserTestHistoryNodeNow->testtime,"%s",PersonTestHistory[0].testtime);
			UserTestHistoryNodeNow->mode=PersonTestHistory[0].mode;
			UserTestHistoryNodeNow->testtotnum=PersonTestHistory[0].testtotnum;
			UserTestHistoryNodeNow->score=PersonTestHistory[0].score;
			UserTestHistoryNodeNow->next=NULL;
			if(UserTestHistoryNodeFirst==NULL){
				UserTestHistoryNodeFirst=UserTestHistoryNodeNow;
			}
			else{
				UserTestHistoryNodePre->next=UserTestHistoryNodeNow;
			}
			return 1;
		}
	}
	return 0;
}

void ETSRPsystemNodeReset(void){
	extern PERSONTESTHISTORYNODE *UserTestHistoryNodeFirst;
	PERSONTESTHISTORYNODE *UserTestHistoryNodePre, *UserTestHistoryNodeNow;
	//===========================
	while(UserTestHistoryNodeFirst!=NULL){
		UserTestHistoryNodeNow=UserTestHistoryNodeFirst;
		UserTestHistoryNodeFirst=UserTestHistoryNodeNow->next;
		free(UserTestHistoryNodeNow);
	}
}

int ETSRPreadtestrecord(int testmode,int testnum,PERSONTESTRECORD *PersonTestRecordPtr){
	char pathname[999], QusetionMode4Path[999];
	WORDTR *Word1File;
	WORDTR2 *Word2File;
	WORDTR3 *Word3File;
	WORDTR4MAIN *Word4mainFile;
	WORDTR4 *Word4File;
	WORDDATANUM wordnum[1];
	FILE *fptr, *fptr2;
	int num1;
	//==============================
	switch(testmode){
		case 1: //單字類 
			sprintf(pathname,"..\\Database\\%d\\%s",testmode,PersonTestRecordPtr->databasename);
			if((fptr = fopen(pathname,"rb"))!=NULL){
				//fscanf(fptr,"[%d]",&num1);
				wordnum[0].datanum=0;
				fread(wordnum,sizeof(WORDDATANUM),1,fptr);
				num1=wordnum[0].datanum;
				if(num1<=0){
					fclose(fptr);
					goto BOOKreturnfalse;
				}
				Word1File=(WORDTR*) malloc(num1*sizeof(WORDTR));
				fseek(fptr,-num1*sizeof(WORDTR),SEEK_END);
				fread(Word1File,sizeof(WORDTR),num1,fptr);
				//===============
				printf("%d.%s\n",testnum,(Word1File+(PersonTestRecordPtr->datanum-1))->chi);
				printf("\nUser Ans:%s\n",PersonTestRecordPtr->answer);
				printf("Qusetion Ans:%s\n",(Word1File+(PersonTestRecordPtr->datanum-1))->eng);
				printf("系統核定：%s\n\n",QuestionTrueFalseChinese(PersonTestRecordPtr->useranstruefalse));
				//==========================
				free(Word1File);
				fclose(fptr);
			}
			else{
				BOOKreturnfalse:
				return 1;
			}
			break;
		case 2:  //填充類 
			sprintf(pathname,"..\\Database\\%d\\%s",testmode,PersonTestRecordPtr->databasename);
			if((fptr = fopen(pathname,"rb"))!=NULL){
				//fscanf(fptr,"[%d]",&num1);
				wordnum[0].datanum=0;
				fread(wordnum,sizeof(WORDDATANUM),1,fptr);
				num1=wordnum[0].datanum;
				if(num1<=0){
					fclose(fptr);
					return 1;
				}
				Word2File=(WORDTR2*) malloc(num1*sizeof(WORDTR2));
				fseek(fptr,-num1*sizeof(WORDTR2),SEEK_END);
				fread(Word2File,sizeof(WORDTR2),num1,fptr);
				//===============
				printf("%d.",testnum);
				QusetionSecondprint((Word2File+(PersonTestRecordPtr->datanum-1))->mainstr,(Word2File+(PersonTestRecordPtr->datanum-1))->ans);
				printf("\nUser Ans:%s\n",PersonTestRecordPtr->answer);
				printf("Qusetion Ans:%s\n",(Word2File+(PersonTestRecordPtr->datanum-1))->ans);
				printf("系統核定：%s\n\n",QuestionTrueFalseChinese(PersonTestRecordPtr->useranstruefalse));
				//==========================
				free(Word2File);
				fclose(fptr);
			}
			else{
				return 1;
			}
			break;
		case 3: //選擇類 
			sprintf(pathname,"..\\Database\\%d\\%s",testmode,PersonTestRecordPtr->databasename);
			if((fptr = fopen(pathname,"rb"))!=NULL){
				//fscanf(fptr,"[%d]",&num1);
				wordnum[0].datanum=0;
				fread(wordnum,sizeof(WORDDATANUM),1,fptr);
				num1=wordnum[0].datanum;
				if(num1<=0){
					fclose(fptr);
					return 1;
				}
				Word3File=(WORDTR3*) malloc(num1*sizeof(WORDTR3));
				fseek(fptr,-num1*sizeof(WORDTR3),SEEK_END);
				fread(Word3File,sizeof(WORDTR3),num1,fptr);
				//===============
				printf("%d.%s\n",testnum,(Word3File+(PersonTestRecordPtr->datanum-1))->question);
				printf("(A)%s\n",(Word3File+(PersonTestRecordPtr->datanum-1))->a1);
				printf("(B)%s\n",(Word3File+(PersonTestRecordPtr->datanum-1))->a2);
				printf("(C)%s\n",(Word3File+(PersonTestRecordPtr->datanum-1))->a3);
				printf("(D)%s\n",(Word3File+(PersonTestRecordPtr->datanum-1))->a4);
				printf("\nUser Ans:%s\n",PersonTestRecordPtr->answer);
				printf("Qusetion Ans:%c\n",((Word3File+(PersonTestRecordPtr->datanum-1))->answer)+64);
				printf("系統核定：%s\n\n",QuestionTrueFalseChinese(PersonTestRecordPtr->useranstruefalse));
				//==========================
				free(Word3File);
				fclose(fptr);
			}
			else{
				return 1;
			}
			break;
		case 4: //閱讀類 
			sprintf(pathname,"..\\Database\\%d\\%s",testmode,PersonTestRecordPtr->databasename);
			if((fptr = fopen(pathname,"rb"))!=NULL){
				Word4mainFile=(WORDTR4MAIN *) malloc(sizeof(WORDTR4MAIN));
				Word4mainFile->questionnum=0;
				fread(Word4mainFile,sizeof(WORDTR4MAIN),1,fptr);
				num1=Word4mainFile->questionnum;
				if(num1<=0){
					fclose(fptr);
					return 1;
				}
				//==============================
				if(QuestionForthprint(Word4mainFile->filename)==1){
					fclose(fptr);
					return 1;
				}
				//==============================
				Word4File=(WORDTR4*) malloc(num1*sizeof(WORDTR4));
				fseek(fptr,-num1*sizeof(WORDTR4),SEEK_END);
				fread(Word4File,sizeof(WORDTR4),num1,fptr);
				//===============
				printf("%d.%s\n",testnum,(Word4File+(PersonTestRecordPtr->datanum-1))->question);
				printf("(A)%s\n",(Word4File+(PersonTestRecordPtr->datanum-1))->a1);
				printf("(B)%s\n",(Word4File+(PersonTestRecordPtr->datanum-1))->a2);
				printf("(C)%s\n",(Word4File+(PersonTestRecordPtr->datanum-1))->a3);
				printf("(D)%s\n",(Word4File+(PersonTestRecordPtr->datanum-1))->a4);
				printf("\nUser Ans:%s\n",PersonTestRecordPtr->answer);
				printf("Qusetion Ans:%c\n",((Word4File+(PersonTestRecordPtr->datanum-1))->answer)+64);
				printf("系統核定：%s\n\n",QuestionTrueFalseChinese(PersonTestRecordPtr->useranstruefalse));
				//==========================
				free(Word4File);
				free(Word4mainFile);
				fclose(fptr);
			}
			else{
				return 1;
			}
			break;
	}
	return 0;
}
