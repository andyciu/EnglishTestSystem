#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include ".\\ETSprogramin.h"
//====================================
void QuestionCatchinSecond(int ,int *,int);
int Checknum(int ,int *,int );
void arrayresume(int *,int );
int wordpersoncheckabcd(char *);
void QusetionSecondprint(char *,char *);
int QuestionForthprint(char *);
void nodedatafree(void);
//====================================
WORDTRNODEEX *Word1NodeExFirst=NULL; //使用者介面-雙重鏈結串列(單字) 
WORDTR2NODEEX *Word2NodeExFirst=NULL; //使用者介面-雙重鏈結串列(填充) 
WORDTR3NODEEX *Word3NodeExFirst=NULL; //使用者介面-雙重鏈結串列(選擇) 
WORDTR4NORMALEX *Word4NormalNodeExFirst=NULL; //使用者介面-雙重鍵結串列(閱讀-綜合標頭)  
PERSONTESTHISTORY *UserTestHistory=NULL; //使用者記錄檔結構 
//=====================================
int Word1TESTnum=0,Word2TESTnum=0,Word3TESTnum=0,Word4TESTnum=0,Word4chooseTESTnum=0,WordTesttot=0; //使用者介面-各題型題數紀錄  
int TestScore[]={100,0,0,0,0,0,0,0,0}; //使用者介面-各題型分配分數紀錄(0.總分/1,3,5,7.各題型每題得分/2,4,6,8.各題型總分) 
int TestCheckQuestionNum[]={0,0,0,0,0,0,0,0,0}; //使用者介面-檢查答案各題型得分紀錄(0.總得分/1,3,5,7.各題型答對題數/2,4,6,8.各題型答對總分) 
//=====================================
int QuestionCatchinFirst(int mode,int num){
	srand((unsigned) time(NULL));
	int i,j,k,pnum,wordnum,m,n;
	int **mainnum, *pData, *mainnum2;
	extern int Word1totnum,Word2totnum,Word3totnum,Word4totnum,Word4choosetotnum;
	extern int Word1TESTnum,Word2TESTnum,Word3TESTnum,Word4TESTnum,Word4chooseTESTnum,WordTesttot;
	extern int TestScore[9];
	//=====================================
	switch(mode){
		case 1: //綜合測驗 
			m=4;n=10;
			mainnum = (int **)malloc(m*sizeof(int *)+m*n*sizeof(int)); //宣告[m][n]之二維陣列 
			for (i = 0, pData = (int *)(mainnum+m); i < m; i++, pData += n){
				mainnum[i]=pData;
			}
			//========================================
			if(Word1totnum<5){
				printf("進行隨機選題時發生錯誤:單字題題目總數不到最低指定數量。\n");
				free(mainnum);
				return 1;
			}
			for(i=0;i<5;i++){
				pnum=(rand()%Word1totnum)+1;
				if(Checknum(pnum,mainnum[0],5)==0){
					mainnum[0][i]=pnum;
					//printf("%d,",mainnum[0][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word1TESTnum=5;
			TestScore[1]=3;
			TestScore[2]=15;
			//arrayresume(*(mainnum+0),5);
			//system("pause");
			QuestionCatchinSecond(1,mainnum[0],5);
			//========================================
			if(Word2totnum<5){
				printf("進行隨機選題時發生錯誤:填充題題目總數不到最低指定數量。\n");
				free(mainnum);
				return 1;
			}
			for(i=0;i<5;i++){
				pnum=(rand()%Word2totnum)+1;
				if(Checknum(pnum,mainnum[1],5)==0){
					mainnum[1][i]=pnum;
					//printf("%d,",mainnum[1][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word2TESTnum=5;
			TestScore[3]=3;
			TestScore[4]=15;
			//arrayresume(*(mainnum+1),5);
			//system("pause");
			QuestionCatchinSecond(2,mainnum[1],5);
			//========================================
			if(Word3totnum<10){
				printf("進行隨機選題時發生錯誤:選擇題題目總數不到最低指定數量。\n");
				free(mainnum);
				return 1;
			}
			for(i=0;i<10;i++){
				pnum=(rand()%Word3totnum)+1;
				if(Checknum(pnum,mainnum[2],10)==0){
					mainnum[2][i]=pnum;
					//printf("%d,",mainnum[2][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word3TESTnum=10;
			TestScore[5]=5;
			TestScore[6]=50;
			//arrayresume(*(mainnum+2),10);
			//system("pause");
			QuestionCatchinSecond(3,mainnum[2],10);
			//========================================
			if(Word4totnum<2){
				printf("進行隨機選題時發生錯誤:閱\讀題題目總數不到最低指定數量。\n");
				free(mainnum);
				return 1;
			}
			for(i=0;i<2;i++){
				pnum=(rand()%Word4totnum)+1;
				if(Checknum(pnum,mainnum[3],2)==0){
					mainnum[3][i]=pnum;
					//printf("%d,",mainnum[3][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word4TESTnum=2;
			TestScore[7]=10;
			TestScore[8]=20;
			//arrayresume(*(mainnum+3),2);
			//system("pause");
			QuestionCatchinSecond(4,mainnum[3],2);
			//=========================================
			WordTesttot=22;
			free(mainnum);
			break;
		case 2: //單字題 
			mainnum2=(int *) malloc(10*sizeof(int));
			//========================================
			if(Word1totnum<10){
				printf("進行隨機選題時發生錯誤:單字題題目總數不到最低指定數量。\n");
				free(mainnum2);
				return 1;
			}
			for(i=0;i<10;i++){
				pnum=(rand()%Word1totnum)+1;
				if(Checknum(pnum,mainnum2,10)==0){
					mainnum2[i]=pnum;
					//printf("%d,",mainnum[0][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word1TESTnum=10;
			WordTesttot=10;
			TestScore[1]=10;
			TestScore[2]=100;
			QuestionCatchinSecond(1,mainnum2,10);
			break;
		case 3: //填充題 
			mainnum2=(int *) malloc(10*sizeof(int));
			//========================================
			if(Word2totnum<10){
				printf("進行隨機選題時發生錯誤:填充題題目總數不到最低指定數量。\n");
				free(mainnum2);
				return 1;
			}
			for(i=0;i<10;i++){
				pnum=(rand()%Word2totnum)+1;
				if(Checknum(pnum,mainnum2,10)==0){
					mainnum2[i]=pnum;
					//printf("%d,",mainnum[0][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word2TESTnum=10;
			WordTesttot=10;
			TestScore[3]=10;
			TestScore[4]=100;
			QuestionCatchinSecond(2,mainnum2,10);
			break;
		case 4: //選擇題 
			mainnum2=(int *) malloc(10*sizeof(int));
			//========================================
			if(Word3totnum<10){
				printf("進行隨機選題時發生錯誤:選擇題題目總數不到最低指定數量。\n");
				free(mainnum2);
				return 1;
			}
			for(i=0;i<10;i++){
				pnum=(rand()%Word3totnum)+1;
				if(Checknum(pnum,mainnum2,10)==0){
					mainnum2[i]=pnum;
					//printf("%d,",mainnum[0][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word3TESTnum=10;
			WordTesttot=10;
			TestScore[5]=10;
			TestScore[6]=100;
			QuestionCatchinSecond(3,mainnum2,10);
			break;
		case 5: //閱讀題 
			mainnum2=(int *) malloc(4*sizeof(int));
			//========================================
			if(Word4totnum<4){
				printf("進行隨機選題時發生錯誤:閱\讀題題目總數不到最低指定數量。\n");
				free(mainnum2);
				return 1;
			}
			for(i=0;i<4;i++){
				pnum=(rand()%Word4totnum)+1;
				if(Checknum(pnum,mainnum2,4)==0){
					mainnum2[i]=pnum;
					//printf("%d,",mainnum[0][i]);
				}
				else{
					i--; //象徵再來一次 
				}
			}
			Word4TESTnum=4;
			WordTesttot=4;
			TestScore[7]=25;
			TestScore[8]=100;
			QuestionCatchinSecond(4,mainnum2,4);
			break;
	}
	return 0;
}

void QuestionCatchinSecond(int qnsmode,int *num,int totnum){
	extern WORDTRNODE *Word1NodeFirst;
	extern WORDTR2NODE *Word2NodeFirst;
	extern WORDTR3NODE *Word3NodeFirst;
	extern WORDTR4NORMAL *Word4NormalNodeFirst;
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	extern WORDTR4NORMALEX *Word4NormalNodeExFirst;
	WORDTRNODE *Word1NodePre,*Word1NodeNow;
	WORDTR2NODE *Word2NodePre,*Word2NodeNow;
	WORDTR3NODE *Word3NodePre,*Word3NodeNow;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTR4NORMAL *Word4NormalNodePre,*Word4NormalNodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	WORDTR4NORMALEX *Word4NormalNodeExPre,*Word4NormalNodeExNow;
	WORDTR4 *Word4File;
	FILE *fptr;
	int k=1,p=0,i;
	char filename1[999];
	//====================================================
	switch(qnsmode){
		case 1:
			Word1NodeExNow=Word1NodeExFirst;
			while(Word1NodeExNow!=NULL){
				Word1NodeExPre=Word1NodeExNow;
				Word1NodeExNow=Word1NodeExNow->next;
			}
			//============================
			while(p<totnum){
				Word1NodeNow=Word1NodeFirst;
				k=1;
				while(Word1NodeNow!=NULL){
					if(k++==num[p]){
						Word1NodeExNow=(WORDTRNODEEX *) malloc(sizeof(WORDTRNODEEX));
						Word1NodeExNow->nodeptr=Word1NodeNow;
						Word1NodeExNow->useranswercheck=0;
						Word1NodeExNow->useranstruefalse=0;
						Word1NodeExNow->next=NULL;
						if(Word1NodeExFirst==NULL){
							Word1NodeExFirst=Word1NodeExNow;
						}
						else{
							Word1NodeExPre->next=Word1NodeExNow;
						}
						Word1NodeExPre=Word1NodeExNow;
						Word1NodeExNow=Word1NodeExNow->next;
						p++;
					}
					Word1NodeNow=Word1NodeNow->next;
				}
			}
			break;
		case 2:
			Word2NodeExNow=Word2NodeExFirst;
			while(Word2NodeExNow!=NULL){
				Word2NodeExPre=Word2NodeExNow;
				Word2NodeExNow=Word2NodeExNow->next;
			}
			//============================
			while(p<totnum){
				Word2NodeNow=Word2NodeFirst;
				k=1;
				while(Word2NodeNow!=NULL){
					if(k++==num[p]){
						Word2NodeExNow=(WORDTR2NODEEX *) malloc(sizeof(WORDTR2NODEEX));
						Word2NodeExNow->nodeptr=Word2NodeNow;
						Word2NodeExNow->useranswercheck=0;
						Word2NodeExNow->useranstruefalse=0;
						Word2NodeExNow->next=NULL;
						if(Word2NodeExFirst==NULL){
							Word2NodeExFirst=Word2NodeExNow;
						}
						else{
							Word2NodeExPre->next=Word2NodeExNow;
						}
						Word2NodeExPre=Word2NodeExNow;
						Word2NodeExNow=Word2NodeExNow->next;
						p++;
					}
					Word2NodeNow=Word2NodeNow->next;
				}
			}	
			break;
		case 3:
			Word3NodeExNow=Word3NodeExFirst;
			while(Word3NodeExNow!=NULL){
				Word3NodeExPre=Word3NodeExNow;
				Word3NodeExNow=Word3NodeExNow->next;
			}
			//============================
			while(p<totnum){
				Word3NodeNow=Word3NodeFirst;
				k=1;
				while(Word3NodeNow!=NULL){
					if(k++==num[p]){
						Word3NodeExNow=(WORDTR3NODEEX *) malloc(sizeof(WORDTR3NODEEX));
						Word3NodeExNow->nodeptr=Word3NodeNow;
						Word3NodeExNow->useranswercheck=0;
						Word3NodeExNow->useranstruefalse=0;
						Word3NodeExNow->next=NULL;
						if(Word3NodeExFirst==NULL){
							Word3NodeExFirst=Word3NodeExNow;
						}
						else{
							Word3NodeExPre->next=Word3NodeExNow;
						}
						Word3NodeExPre=Word3NodeExNow;
						Word3NodeExNow=Word3NodeExNow->next;
						p++;
					}
					Word3NodeNow=Word3NodeNow->next;
				}
			}	
			break;
		case 4:
			Word4NormalNodeExNow=Word4NormalNodeExFirst;
			while(Word4NormalNodeExNow!=NULL){
				Word4NormalNodeExPre=Word4NormalNodeExNow;
				Word4NormalNodeExNow=Word4NormalNodeExNow->next;
			}
			//============================
			while(p<totnum){
				Word4NormalNodeNow=Word4NormalNodeFirst;
				k=1;
				while(Word4NormalNodeNow!=NULL){
					if(k++==num[p]){
						Word4NormalNodeExNow=(WORDTR4NORMALEX *) malloc(sizeof(WORDTR4NORMALEX));
						Word4NormalNodeExNow->nodeptr=Word4NormalNodeNow;
						Word4NormalNodeExNow->next=NULL;
						if(Word4NormalNodeExFirst==NULL){
							Word4NormalNodeExFirst=Word4NormalNodeExNow;
						}
						else{
							Word4NormalNodeExPre->next=Word4NormalNodeExNow;
						}
						//==============================================
						Word4NodeNow=Word4NodeFirst;
						while(Word4NodeNow!=NULL){
							Word4NodePre=Word4NodeNow;
							Word4NodeNow=Word4NodeNow->next;
						}
						//============================
						sprintf(filename1,"..\\Database\\4\\%s",Word4NormalNodeNow->databasefilename);
						if((fptr = fopen(filename1,"rb"))!=NULL){
							Word4File=(WORDTR4 *) malloc((Word4NormalNodeNow->questionnum)*sizeof(WORDTR4));
							fseek(fptr,-(Word4NormalNodeNow->questionnum)*sizeof(WORDTR4),SEEK_END);
							fread(Word4File,sizeof(WORDTR4),(Word4NormalNodeNow->questionnum),fptr);
							for(i=0;i<Word4NormalNodeNow->questionnum;i++){
								Word4NodeNow=(WORDTR4NODE *) malloc(sizeof(WORDTR4NODE));
								sprintf(Word4NodeNow->question,"%s",(Word4File+i)->question);
								sprintf(Word4NodeNow->a1,"%s",(Word4File+i)->a1);
								sprintf(Word4NodeNow->a2,"%s",(Word4File+i)->a2);
								sprintf(Word4NodeNow->a3,"%s",(Word4File+i)->a3);
								sprintf(Word4NodeNow->a4,"%s",(Word4File+i)->a4);
								Word4NodeNow->answer=(Word4File+i)->answer;
								Word4NodeNow->useranswercheck=0;
								Word4NodeNow->useranstruefalse=0;
								Word4NodeNow->next=NULL;
								if(Word4NodeFirst==NULL){
									Word4NodeFirst=Word4NodeNow;
								}
								else{
									Word4NodePre->next=Word4NodeNow;
								}
								Word4NodePre=Word4NodeNow;
								Word4NodeNow=Word4NodeNow->next;
							}
							Word4chooseTESTnum+=Word4NormalNodeNow->questionnum;
							free(Word4File);
							fclose(fptr);
						}
						else{
							printf("開啟檔案失敗!請檢查您的資料庫檔案...\n");
							exit(1);
						}
						//================================
						Word4NormalNodeExPre=Word4NormalNodeExNow;
						Word4NormalNodeExNow=Word4NormalNodeExNow->next;
						p++;
					}
					Word4NormalNodeNow=Word4NormalNodeNow->next;
				}
			}	
			break;
	}
}

void QuestionGet(int mode,int num){
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	extern WORDTR4NORMALEX *Word4NormalNodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	WORDTR4NORMALEX *Word4NormalNodeExPre,*Word4NormalNodeExNow;
	//=======================================
	FILE *fptr;
	char filename1[999],txtinout;
	int k=1,p=0;
	//======================================= 
	switch(mode){
		case 1: //單字題 
			Word1NodeExNow=Word1NodeExFirst;
			while(Word1NodeExNow!=NULL){
				if(k++==num){
					printf("%d.%s\n",num,Word1NodeExNow->nodeptr->chi);
					return;
				}
				Word1NodeExNow=Word1NodeExNow->next;
			}
			break;
		case 2: //填充題 
			Word2NodeExNow=Word2NodeExFirst;
			while(Word2NodeExNow!=NULL){
				if(k++==num){
					printf("%d.",num);
					QusetionSecondprint(Word2NodeExNow->nodeptr->mainstr,Word2NodeExNow->nodeptr->ans);
					return;
				}
				Word2NodeExNow=Word2NodeExNow->next;
			}
			break;
		case 3: //選擇題 
			Word3NodeExNow=Word3NodeExFirst;
			while(Word3NodeExNow!=NULL){
				if(k++==num){
					printf("%d.%s\n",num,Word3NodeExNow->nodeptr->question);
					printf("(A)%s\n",Word3NodeExNow->nodeptr->a1);
					printf("(B)%s\n",Word3NodeExNow->nodeptr->a2);
					printf("(C)%s\n",Word3NodeExNow->nodeptr->a3);
					printf("(D)%s\n",Word3NodeExNow->nodeptr->a4);
					return;
				}
				Word3NodeExNow=Word3NodeExNow->next;
			}
			break;
		case 4: //閱讀題 
			Word4NormalNodeExNow=Word4NormalNodeExFirst;
			Word4NodeNow=Word4NodeFirst;
			while(Word4NormalNodeExNow!=NULL){
				if((p+(Word4NormalNodeExNow->nodeptr->questionnum))<num){
					p+=Word4NormalNodeExNow->nodeptr->questionnum;
				}
				else{
					if(QuestionForthprint(Word4NormalNodeExNow->nodeptr->filename)==1){
						printf("[本閱\讀題組之文本檔案已損毀或遺失，本題組不予給分。]");
						return;
					}
					//==================================================
					while(Word4NodeNow!=NULL){
						if(k++==num){
							printf("%d.%s\n",num,Word4NodeNow->question);
							printf("(A)%s\n",Word4NodeNow->a1);
							printf("(B)%s\n",Word4NodeNow->a2);
							printf("(C)%s\n",Word4NodeNow->a3);
							printf("(D)%s\n",Word4NodeNow->a4);
							return;
						}
						Word4NodeNow=Word4NodeNow->next;
					}
				}
				Word4NormalNodeExNow=Word4NormalNodeExNow->next;
			}
			break;
	}

}

void UserAnswerFillin(int mode,int num,char *str){
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	//=======================================
	int k=1;
	//======================================= 
	switch(mode){
		case 1: //單字題 
			Word1NodeExNow=Word1NodeExFirst;
			while(Word1NodeExNow!=NULL){
				if(k++==num){
					sprintf(Word1NodeExNow->useranswer,"%s",str);
					Word1NodeExNow->useranswercheck=1;
					return;
				}
				Word1NodeExNow=Word1NodeExNow->next;
			}
			break;
		case 2: //填充題 
			Word2NodeExNow=Word2NodeExFirst;
			while(Word2NodeExNow!=NULL){
				if(k++==num){
					sprintf(Word2NodeExNow->useranswer,"%s",str);
					Word2NodeExNow->useranswercheck=1;
					return;
				}
				Word2NodeExNow=Word2NodeExNow->next;
			}
			break;
		case 3: //選擇題 
			Word3NodeExNow=Word3NodeExFirst;
			while(Word3NodeExNow!=NULL){
				if(k++==num){
					Word3NodeExNow->useranswer=wordpersoncheckabcd(str);
					Word3NodeExNow->useranswercheck=1;
					return;
				}
				Word3NodeExNow=Word3NodeExNow->next;
			}
			break;
		case 4: //閱讀題 
			Word4NodeNow=Word4NodeFirst;
			while(Word4NodeNow!=NULL){
				if(k++==num){
					Word4NodeNow->useranswer=wordpersoncheckabcd(str);
					Word4NodeNow->useranswercheck=1;
					return;
				}
				Word4NodeNow=Word4NodeNow->next;
			}
			break;
	}

}

char* UserAnswerCheckOut(int mode,int num){
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	//=======================================
	int k=1;
	char userans[2];
	//======================================= 
	switch(mode){
		case 1: //單字題 
			Word1NodeExNow=Word1NodeExFirst;
			while(Word1NodeExNow!=NULL){
				if(k++==num){
					if(Word1NodeExNow->useranswercheck==1){
						return Word1NodeExNow->useranswer;
					}
					else{
						return "0000";
					}
				}
				Word1NodeExNow=Word1NodeExNow->next;
			}
			break;
		case 2: //填充題 
			Word2NodeExNow=Word2NodeExFirst;
			while(Word2NodeExNow!=NULL){
				if(k++==num){
					if(Word2NodeExNow->useranswercheck==1){
						return Word2NodeExNow->useranswer;
					}
					else{
						return "0000";
					}
				}
				Word2NodeExNow=Word2NodeExNow->next;
			}
			break;
		case 3: //選擇題 
			Word3NodeExNow=Word3NodeExFirst;
			while(Word3NodeExNow!=NULL){
				if(k++==num){
					if(Word3NodeExNow->useranswercheck==1){
						sprintf(userans,"%c",(Word3NodeExNow->useranswer)+64);
						return userans;
					}
					else{
						return "0000";
					}
				}
				Word3NodeExNow=Word3NodeExNow->next;
			}
			break;
		case 4: //閱讀題 
			Word4NodeNow=Word4NodeFirst;
			while(Word4NodeNow!=NULL){
				if(k++==num){
					if(Word4NodeNow->useranswercheck==1){
						//return ((Word4NodeNow->useranswer)+64);
						sprintf(userans,"%c",(Word4NodeNow->useranswer)+64);
						return userans;
					}
					else{
						return "0000";
					}
				}
				Word4NodeNow=Word4NodeNow->next;
			}
			break;
	}

}

void QuestionCheckAnswer(int mode){
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	extern WORDTR4NORMALEX *Word4NormalNodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	WORDTR4NORMALEX *Word4NormalNodeExPre,*Word4NormalNodeExNow;
	//=======================================
	int qmode,Fmode=1,k=1;
	double totscore=0.0,Forthscore,ForthscoreTot=0.0;
	extern int Word1TESTnum,Word2TESTnum,Word3TESTnum,Word4TESTnum,Word4chooseTESTnum,WordTesttot; //使用者介面-各題型題數紀錄 
	extern int TestScore[9];
	extern int TestCheckQuestionNum[9];
	//=======================================
	while(1){
		qmode=mode;
		if(mode==1){
			if(Fmode>=5) break;
			else qmode+=Fmode;
		}
		else{
			if(Fmode>=2) break;
		}
		switch(qmode){
			case 2:
				Word1NodeExNow=Word1NodeExFirst;
				while(Word1NodeExNow!=NULL){
					if(strcmp(Word1NodeExNow->useranswer,Word1NodeExNow->nodeptr->eng)==0){
						totscore+=(double) TestScore[1];
						TestCheckQuestionNum[1]+=1;
						Word1NodeExNow->useranstruefalse=1;
					}
					Word1NodeExNow=Word1NodeExNow->next;
				}
				TestCheckQuestionNum[2]=TestCheckQuestionNum[1]*TestScore[1];
				Fmode++;
				break;
			case 3:
				Word2NodeExNow=Word2NodeExFirst;
				while(Word2NodeExNow!=NULL){
					if(strcmp(Word2NodeExNow->useranswer,Word2NodeExNow->nodeptr->ans)==0){
						totscore+=(double) TestScore[3];
						TestCheckQuestionNum[3]+=1;
						Word2NodeExNow->useranstruefalse=1;
					}
					Word2NodeExNow=Word2NodeExNow->next;
				}
				TestCheckQuestionNum[4]=TestCheckQuestionNum[3]*TestScore[3];
				Fmode++;
				break;
			case 4:
				Word3NodeExNow=Word3NodeExFirst;
				while(Word3NodeExNow!=NULL){
					if(Word3NodeExNow->useranswer==Word3NodeExNow->nodeptr->answer){
						totscore+=(double) TestScore[5];
						TestCheckQuestionNum[5]+=1;
						Word3NodeExNow->useranstruefalse=1;
					}
					Word3NodeExNow=Word3NodeExNow->next;
				}
				TestCheckQuestionNum[6]=TestCheckQuestionNum[5]*TestScore[5];
				Fmode++;
				break;
			case 5:
				Word4NodeNow=Word4NodeFirst;
				Word4NormalNodeExNow=Word4NormalNodeExFirst;
				//=====================================
				while(Word4NormalNodeExNow!=NULL){
					Forthscore=(double) TestScore[7]/Word4NormalNodeExNow->nodeptr->questionnum;
					while((Word4NodeNow!=NULL) && (k<=Word4NormalNodeExNow->nodeptr->questionnum)){
						if(Word4NodeNow->useranswer==Word4NodeNow->answer){
							totscore+=Forthscore;
							ForthscoreTot+=Forthscore;
							TestCheckQuestionNum[7]+=1;
							Word4NodeNow->useranstruefalse=1;
						}
						Word4NodeNow=Word4NodeNow->next;
						k++;
					}
					k=1;
					Word4NormalNodeExNow=Word4NormalNodeExNow->next;
				}
				//=====================================
				TestCheckQuestionNum[8]=(int) round(ForthscoreTot);
				Fmode++;
				break;
		}
	}
	TestCheckQuestionNum[0]=(int) round(totscore);
}

int Checknum(int num,int *mainnum,int mainnummax){
	int i;
	for(i=0;i<mainnummax;i++){
		if(mainnum[i]==num){
			return 1;
		}
	}
	return 0;
}

void arrayresume(int *mainnum,int mainnummax){
	int i,j,pnum;
	for(i=mainnummax-1;i>0;i--){
		for(j=0;j<i;j++){
			if(mainnum[j]>mainnum[j+1]){
				pnum=mainnum[j];
				mainnum[j]=mainnum[j+1];
				mainnum[j+1]=pnum;
			}
		}
	}
	for(i=0;i<mainnummax;i++){
		printf("%d;",mainnum[i]);
	}
}

void QusetionSecondprint(char *str1,char *str2){
	int i=strlen(str1);
	int j,k=0,p=0,pnum1,pnum2,m;
	for(j=0;j<i+1;j++){
		if(str1[j]==str2[0] && p==0){
			p=1;
			pnum1=j;
		}
		if(p==1){
			if(k>=strlen(str2)){
				if((str1[j]>='A' && str1[j]<='Z') || (str1[j]>='a' && str1[j]<='z')){
					p=0;
					k=0;
					pnum1=0;
				}
				else{
					//return 1;
					pnum2=j;
					//=========================
					for(m=0;m<i+1;m++){
						if(m>=pnum1 && m<pnum2){
							printf(" %c ",'_');
						}
						else{
							printf("%c",str1[m]);
						}
					}
					printf("\n");
					return;
				}
			}
			else if(str1[j]!=str2[k++]){
				p=0;
				k=0;
				pnum1=0;
			}
		}
	}
	return;
}

int QuestionForthprint(char *filename){
	FILE *fptr;
	char filename1[999],txtinout;
	//int k=0;
	//==================================
	sprintf(filename1,"..\\Database\\4\\%s",filename);
	if((fptr=fopen(filename1,"r"))!=NULL){
		while(!feof(fptr)){
			txtinout=fgetc(fptr);
			printf("%c",txtinout);
			/*k++;
			if(k==79){
				if((txtinout>='A' && txtinout<='Z') || (txtinout>='a' && txtinout<='z')){
					printf("%c",'-');
					k=0;
				}
			}
			else if(k==80 || txtinout=='\0'){
				k=0;
			}*/
		}
		printf("\n\n");
		fclose(fptr);
		return 0;
	}
	else{
		return 1;
	}
}

void UserRecordReset(char *user,int sysmode){
	extern PERSONTESTHISTORY *UserTestHistory;
	//=============================
	if(UserTestHistory==NULL){
		UserTestHistory=(PERSONTESTHISTORY *) malloc(sizeof(PERSONTESTHISTORY));
	}
	else{
		free(UserTestHistory);
		UserTestHistory=(PERSONTESTHISTORY *) malloc(sizeof(PERSONTESTHISTORY));
	}
	//=============================
	time_t t1 = time(NULL);
	struct tm *nPtr = localtime(&t1);
	strftime(UserTestHistory->testtime, 100, "%a %b %d %X %Y", nPtr);
	//==============================
	sprintf(UserTestHistory->username,"%s",user);
	UserTestHistory->mode=sysmode;
	UserTestHistory->score=0;
	UserTestHistory->testtotnum=0;

}

void SystemRecordReset(void){
	extern int Word1TESTnum,Word2TESTnum,Word3TESTnum,Word4TESTnum,Word4chooseTESTnum,WordTesttot;
	extern int Word1totnum,Word2totnum,Word3totnum,Word4totnum,Word4choosetotnum;
	extern int TestScore[9];
	extern int TestCheckQuestionNum[9];
	int i;
	//=====================================================
	Word1TESTnum=0;Word2TESTnum=0;Word3TESTnum=0;Word4TESTnum=0;Word4chooseTESTnum=0;WordTesttot=0;
	Word1totnum=0,Word2totnum=0,Word3totnum=0,Word4totnum=0,Word4choosetotnum=0;
	for(i=0;i<9;i++){
		TestScore[i]=0;
		TestCheckQuestionNum[i]=0;
	}
	//=====================================================
	nodedatafree();
}

void UserTestSaveRecord(int mode){
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	extern WORDTR4NORMALEX *Word4NormalNodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	WORDTR4NORMALEX *Word4NormalNodeExPre,*Word4NormalNodeExNow;
	extern PERSONTESTHISTORY *UserTestHistory;
	extern int TestCheckQuestionNum[9];
	extern int Word1TESTnum,Word2TESTnum,Word3TESTnum,Word4TESTnum,Word4chooseTESTnum,WordTesttot; //使用者介面-各題型題數紀錄 
	PERSONTESTRECORD UserTestRecord[1];
	char timestr[100];
	char filename[999];
	FILE *fptr;
	int i,j,k=1,qmode;
	//================
	time_t t1 = time(NULL);
	struct tm *nPtr = localtime(&t1);
	strftime(timestr, 100, "%Y-%m-%d_%H-%M-%S", nPtr);
	//===============================
	sprintf(filename,"..\\Log\\%s.etlog",timestr);
	if((fptr=fopen(filename,"wb"))!=NULL){
		//========================
		UserTestHistory->score=TestCheckQuestionNum[0];
		UserTestHistory->testtotnum=(Word1TESTnum+Word2TESTnum+Word3TESTnum+Word4chooseTESTnum);
		//========================
		fwrite(UserTestHistory,sizeof(PERSONTESTHISTORY),1,fptr);
		//========================
		Word1NodeExNow=Word1NodeExFirst;
		Word2NodeExNow=Word2NodeExFirst;
		Word3NodeExNow=Word3NodeExFirst;
		Word4NodeNow=Word4NodeFirst;
		Word4NormalNodeExNow=Word4NormalNodeExFirst;
		for(i=1;i<=WordTesttot;i++){
			qmode=mode;
			if(mode==1){
				if(i<=5) qmode+=1; //單字題 
				else if(i<=10) qmode+=2;  //填充題 
				else if(i<=20) qmode+=3; //選擇題 
				else qmode+=4; //閱讀題 
			}
			switch(qmode){
				case 2:
					if(Word1NodeExNow!=NULL){
						UserTestRecord[0].modenum=qmode-1;
						sprintf(UserTestRecord[0].databasename,"%s",Word1NodeExNow->nodeptr->databasename);
						UserTestRecord[0].datanum=Word1NodeExNow->nodeptr->datanum;
						sprintf(UserTestRecord[0].answer,"%s",Word1NodeExNow->useranswer);
						UserTestRecord[0].useranstruefalse=Word1NodeExNow->useranstruefalse;
						//================================
						fwrite(UserTestRecord,sizeof(PERSONTESTRECORD),1,fptr);
						Word1NodeExNow=Word1NodeExNow->next;
					}
					break;
				case 3:
					if(Word2NodeExNow!=NULL){
						UserTestRecord[0].modenum=qmode-1;
						sprintf(UserTestRecord[0].databasename,"%s",Word2NodeExNow->nodeptr->databasename);
						UserTestRecord[0].datanum=Word2NodeExNow->nodeptr->datanum;
						sprintf(UserTestRecord[0].answer,"%s",Word2NodeExNow->useranswer);
						UserTestRecord[0].useranstruefalse=Word2NodeExNow->useranstruefalse;
						//================================
						fwrite(UserTestRecord,sizeof(PERSONTESTRECORD),1,fptr);
						Word2NodeExNow=Word2NodeExNow->next;
					}
					break;
				case 4:
					if(Word3NodeExNow!=NULL){
						UserTestRecord[0].modenum=qmode-1;
						sprintf(UserTestRecord[0].databasename,"%s",Word3NodeExNow->nodeptr->databasename);
						UserTestRecord[0].datanum=Word3NodeExNow->nodeptr->datanum;
						sprintf(UserTestRecord[0].answer,"%c",(Word3NodeExNow->useranswer)+64);
						UserTestRecord[0].useranstruefalse=Word3NodeExNow->useranstruefalse;
						//================================
						fwrite(UserTestRecord,sizeof(PERSONTESTRECORD),1,fptr);
						Word3NodeExNow=Word3NodeExNow->next;
					}
					break;
				case 5:
					if(Word4NormalNodeExNow!=NULL){
						for(k=1;k<=Word4NormalNodeExNow->nodeptr->questionnum;k++){
							if(Word4NodeNow!=NULL){
								UserTestRecord[0].modenum=qmode-1;
								sprintf(UserTestRecord[0].databasename,"%s",Word4NormalNodeExNow->nodeptr->databasefilename);
								UserTestRecord[0].datanum=k;
								sprintf(UserTestRecord[0].answer,"%c",(Word4NodeNow->useranswer)+64);
								UserTestRecord[0].useranstruefalse=Word4NodeNow->useranstruefalse;
								//================================
								fwrite(UserTestRecord,sizeof(PERSONTESTRECORD),1,fptr);
								Word4NodeNow=Word4NodeNow->next;
							}
						}
						Word4NormalNodeExNow=Word4NormalNodeExNow->next;
					}
					break;	
			}
		}
	}
	printf("\n記錄檔已存至檔案 %s.etlog。\n",timestr);
	fclose(fptr);
}
