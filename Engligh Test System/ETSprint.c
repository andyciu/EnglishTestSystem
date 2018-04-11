#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include ".\\ETSprogramin.h"
//====================================
void menu1(void);
int menu1_2(void);
void testmenu1(int ,int );
void testmenu2(int ,int );
void testmenu3(void);
int wordpersoncheckyesno(char *);
int wordpersoncheckabcd(char *);
void QuestionGet(int ,int );
void testmenumain(int );
void UserAnswerFillin(int ,int ,char *);
int QuestionCatchinFirst(int ,int );
char* UserAnswerCheckOut(int ,int );
char* QuestionNumChinese(int );
void UserRecordReset(char *,int );
int testmenuend(int );
void QuestionCheckAnswer(int );
void testmenuscore(int );
void SystemRecordReset(void);
void UserTestSaveRecord(int );
int searchfile(int );
int adddata(int ,char *,char *);
int menuadddataname(int );
void ETSRPmainmenu(void);
//====================================
char UserInputDatabaseFilename[255];
//==================================== 
void helloworld(void){
	system("cls");
	printf("\n\t\t\t歡迎來到英文測驗系統\n");
	printf("\t\t       English Test System V1.0\n\t\t\t\t\t\t\t   2015 By AndyCiu.\n");
}

void mainmenu(void){
	char input;
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.進行一個新的測驗\n");
		printf("2.觀看測驗結果紀錄\n");
		//=================
		printf("0.離開\n");
		//=================
		printf(">");
		fflush(stdin);
		input=getche();
		switch(input){
			case '1':
				menu1();
				break;
			case '2':
				ETSRPmainmenu();
				break;
			case '0':
				exit(0);
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}

void menu1(void){ //進行測驗類 
	char input;
	int usernum;
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.進行新的綜合測驗\n");
		printf("2.進行新的單字測驗\n");
		printf("3.進行新的填充測驗\n");
		printf("4.進行新的選擇測驗\n");
		printf("5.進行新的閱\讀測驗\n");
		//=================
		printf("0.回到主選單\n");
		//=================
		printf(">");
		fflush(stdin);
		input=getche();
		switch(input){
			case '1':
				testmenu1(1,1);
				testmenu2(1,0);
				break;
			case '2':
				usernum=menu1_2();
				if(usernum==1){  //全部題庫隨機選題
					testmenu1(2,1);
					testmenu2(2,1);
				}
				else if(usernum==2){ //指定題庫並隨機選題
					testmenu1(2,1);
					SystemRecordReset();
					if(menuadddataname(2)==0){
						testmenu2(2,2);
					}
				}
				break;
			case '3':
				usernum=menu1_2();
				if(usernum==1){  //全部題庫隨機選題
					testmenu1(3,1);
					testmenu2(3,1);
				}
				else if(usernum==2){ //指定題庫並隨機選題
					testmenu1(3,1);
					SystemRecordReset();
					if(menuadddataname(3)==0){
						testmenu2(3,2);
					}
				}
				break;
			case '4':
				usernum=menu1_2();
				if(usernum==1){  //全部題庫隨機選題
					testmenu1(4,1);
					testmenu2(4,1);
				}
				else if(usernum==2){ //指定題庫並隨機選題
					testmenu1(4,1);
					SystemRecordReset();
					if(menuadddataname(4)==0){
						testmenu2(4,2);
					}
				}
				break;
			case '5':
				testmenu1(5,1);
				testmenu2(5,0);
				break;
			case '0':
				helloworld();
				return;
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}

int menu1_2(void){ 
	char input;
	while(1){
		printf("\n\n請選擇指令：\n");
		//=================
		printf("1.採用全部題庫隨機選題\n");
		printf("2.指定題庫並隨機選題\n");
		//=================
		printf("0.回到主選單\n");
		//=================
		printf(">");
		fflush(stdin);
		input=getche();
		switch(input){
			case '1':
				return 1;
			case '2':
				return 2;
			case '0':
				return 0;
			default:
				printf("輸入錯誤!請重新輸入。\n");
		}
	}
}

void testmenu1(int mode,int timenum){
	char modestr[10];
	extern char ETSLoginUserName[999];
	time_t t1 = time(NULL);
	extern PERSONTESTHISTORY *UserTestHistory;
	system("cls");
	switch(mode){
		case 1:
			sprintf(modestr,"綜合");
			break;
		case 2:
			sprintf(modestr,"單字");
			break;
		case 3:
			sprintf(modestr,"填充");
			break;
		case 4:
			sprintf(modestr,"選擇");
			break;
		case 5:
			sprintf(modestr,"閱\讀");
			break;
			
	}
	if(timenum==1){
		printf("英文測驗系統>>%s測驗\t\t\t開始時間:%s\n",modestr,ctime(&t1));
	}
	else{
		printf("英文測驗系統>>%s測驗\t\t\t開始時間:%s\n",modestr,UserTestHistory->testtime);
	}
	printf("使用者:%s\n\n",ETSLoginUserName);
}

void testmenu2(int mode,int num){
	extern char ETSLoginUserName[999];
	switch(mode){
		case 1:
			printf("即將開始綜合測驗，本測驗採全題庫隨機選題，共分成以下四種類型：\n\n");
			printf("一、單字題(5題)，每題3分，共15分\n");
			printf("二、填充題(5題)，每題3分，共15分\n");
			printf("三、選擇題(10題)，每題5分，共50分\n");
			printf("四、閱\讀題(2題)，每大題10分，共20分\n\n");
			printf("本測驗合計共 100 分，答錯不倒扣\n");
			if(wordpersoncheckyesno("是否開始測驗?")==1){
				SystemRecordReset();
				if(searchfile(mode)==0){
					if(QuestionCatchinFirst(mode,0)==0){
						UserRecordReset(ETSLoginUserName,mode);
						testmenumain(mode);
					}
				}
			}
			break;
		case 2:
			if(num==1){
				printf("即將開始單字測驗，本測驗採全題庫隨機選題，總共測驗如下：\n\n");
			}
			else{
				printf("\n即將開始單字測驗，本測驗採指定題庫題庫隨機選題，總共測驗如下：\n\n");
			}
			printf("一、單字題(10題)，每題10分，共100分\n");
			printf("本測驗合計共 100 分，答錯不倒扣\n");
			if(wordpersoncheckyesno("是否開始測驗?")==1){
				if(num==1){
					SystemRecordReset();
					if(searchfile(mode)==0){
						if(QuestionCatchinFirst(mode,10)==0){
							UserRecordReset(ETSLoginUserName,mode);
							testmenumain(mode);
						}
					}
				}
				else{
					if(QuestionCatchinFirst(mode,10)==0){
						UserRecordReset(ETSLoginUserName,mode);
						testmenumain(mode);
					}
				}		
			}
			break;
		case 3:
			if(num==1){
				printf("即將開始填充測驗，本測驗採全題庫隨機選題，總共測驗如下：\n\n");
			}
			else{
				printf("\n即將開始填充測驗，本測驗採指定題庫題庫隨機選題，總共測驗如下：\n\n");
			}
			printf("一、填充題(10題)，每題10分，共100分\n");
			printf("本測驗合計共 100 分，答錯不倒扣\n");
			if(wordpersoncheckyesno("是否開始測驗?")==1){
				if(num==1){
					SystemRecordReset();
					if(searchfile(mode)==0){
						if(QuestionCatchinFirst(mode,10)==0){
							UserRecordReset(ETSLoginUserName,mode);
							testmenumain(mode);
						}
					}
				}
				else{
					if(QuestionCatchinFirst(mode,10)==0){
						UserRecordReset(ETSLoginUserName,mode);
						testmenumain(mode);
					}
				}		
			}
			break;
		case 4:
			if(num==1){
				printf("即將開始選擇測驗，本測驗採全題庫隨機選題，總共測驗如下：\n\n");
			}
			else{
				printf("\n即將開始選擇測驗，本測驗採指定題庫題庫隨機選題，總共測驗如下：\n\n");
			}
			printf("一、選擇題(10題)，每題10分，共100分\n");
			printf("本測驗合計共 100 分，答錯不倒扣\n");
			if(wordpersoncheckyesno("是否開始測驗?")==1){
				if(num==1){
					SystemRecordReset();
					if(searchfile(mode)==0){
						if(QuestionCatchinFirst(mode,10)==0){
							UserRecordReset(ETSLoginUserName,mode);
							testmenumain(mode);
						}
					}
				}
				else{
					if(QuestionCatchinFirst(mode,10)==0){
						UserRecordReset(ETSLoginUserName,mode);
						testmenumain(mode);
					}
				}		
			}
			break;
		case 5:
			printf("即將開始閱\讀測驗，本測驗採全題庫隨機選題，總共測驗如下：\n\n");
			printf("一、閱\讀題(4題)，每大題25分，共100分\n\n");
			printf("本測驗合計共 100 分，答錯不倒扣\n");
			if(wordpersoncheckyesno("是否開始測驗?")==1){
				SystemRecordReset();
				if(searchfile(mode)==0){
					if(QuestionCatchinFirst(mode,0)==0){
						UserRecordReset(ETSLoginUserName,mode);
						testmenumain(mode);
					}
				}
			}
			break;
	}
	
}

int menuadddataname(int mode){
	char dataname[255];
	char datapathname[999];
	while(1){
		printf("\n請輸入指定題庫名稱：");
		fflush(stdin);
		scanf("%s",dataname);
		if(dataname[0]!='\0'){
			sprintf(datapathname,"..\\Database\\%d\\%s.etd%d",mode-1,dataname,mode-1);
			if(adddata(mode-1,datapathname,dataname)==1){
				return 1;
			}
			else{
				return 0;
			}
		}
		else{
			printf("輸入錯誤!請再試一遍...\n");
		}
	}
}

void testmenu3(void){
	printf("\n");
	printf("Ctrl+Q=離開  Ctrl+B:跳至上一題  Ctrl+N:跳至下一題  Enter:確定\n");
}

void testmenumain(int mode){
	int i,j,k,qmode,qnum=1,qBnum=1,qnumMax=0,Fmode=1,Fqnum=1;
	extern int Word1TESTnum,Word2TESTnum,Word3TESTnum,Word4TESTnum,Word4chooseTESTnum,WordTesttot; //使用者介面-各題型題數紀錄 
	extern int TestScore[9];
	char answern[100];
	char userwere[100];
	//======================
	while(1){
		testmenu1(mode,2);
		testmenu3();
		qmode=mode;
		if(mode==1){  //綜合測驗 
			qmode+=Fmode;
		}
		switch(qmode){
			case 2: //單字題 
				printf("\n%s、單字題(每題%d分，共%d分):\n\n",QuestionNumChinese(qBnum),TestScore[1],TestScore[2]);
				qnumMax=Word1TESTnum;
				QuestionGet(1,qnum);
				break;
			case 3: //填充題 
				printf("\n%s、填充題(每題%d分，共%d分):\n\n",QuestionNumChinese(qBnum),TestScore[3],TestScore[4]);
				qnumMax=Word2TESTnum;
				QuestionGet(2,qnum);
				break;
			case 4: //選擇題 
				printf("\n%s、選擇題(每題%d分，共%d分):\n\n",QuestionNumChinese(qBnum),TestScore[5],TestScore[6]);
				qnumMax=Word3TESTnum;
				QuestionGet(3,qnum);
				break;
			case 5: //閱讀題 
				printf("\n%s、閱\讀題(每大題%d分，共%d分):\n\n",QuestionNumChinese(qBnum),TestScore[7],TestScore[8]);
				qnumMax=Word4chooseTESTnum;
				QuestionGet(4,qnum);
				break;
		}
		//=================================================
		while(1){
			sprintf(userwere,"%s",UserAnswerCheckOut(qmode-1,qnum));
			if(strcmp(userwere,"0000")!=0){
				printf("[%s]",userwere);
			}
			printf(">");
			fflush(stdin);
			//scanf("%s",answern);
			gets(answern);
			if(answern[0]==17){
				printf("已離開本次測驗。\n");
				exit(2);
			}
			else if(answern[0]==2){
				qnum--;
				break;
			}
			else if(answern[0]==14){
				qnum++;
				break;
			}
			else{
				if(answern[0]=='\0'){
					if(strcmp(userwere,"0000")!=0){
						sprintf(answern,"%s",userwere); //默認之前所輸入之答案 
					}
					else{
						printf("輸入錯誤!請再試一遍...\n");
						continue;
					}
				}
				switch(qmode){
					case 2:
					case 3:
						UserAnswerFillin(qmode-1,qnum,answern);
						qnum++;
						break;
					case 4:
					case 5:
						if(wordpersoncheckabcd(answern)!=0){
							UserAnswerFillin(qmode-1,qnum,answern);
							qnum++;
						}
						else{
							printf("輸入答案錯誤!請再試一遍:\n");
							continue;
						}
						break;
				}
				break;
			}
		}
		//=================================================
		if(mode==1){
			switch(Fmode){
				case 1: //單字題 
					if(qnum<=0){
						qnum=1;
					}
					else if(qnum>5){
						Fmode++;
						qBnum++;
						qnum=1;
					}
					break;
				case 2: //填充題 
					if(qnum<=0){
						Fmode--; 
						qBnum--;
						qnum=5;
					}
					else if(qnum>5){
						Fmode++;
						qBnum++;
						qnum=1;
					}
					break;
				case 3: //選擇題 
					if(qnum<=0){
						Fmode--; 
						qBnum--;
						qnum=5;
					}
					else if(qnum>10){
						Fmode++;
						qBnum++;
						qnum=1;
					}
					break;
				case 4: //閱讀題 
					if(qnum<=0){
						Fmode--; 
						qBnum--;
						qnum=10;
					}
					else if(qnum>qnumMax){
						if(testmenuend(mode)==1){
							testmenuscore(mode);
							return;
						}
						else{
							qnum=qnumMax;
						}
					}
					break;
			}
		}
		else{
			if(qnum<1) qnum=1;
			else if(qnum>qnumMax){
				if(testmenuend(mode)==1){
					testmenuscore(mode);
					return;
				}
				else{
					qnum=qnumMax;
				}
			}
		}
	}	
}

int testmenuend(int mode){
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	//=======================================
	int qmode,Fmode=1,checknum=0;
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
					if(Word1NodeExNow->useranswercheck!=1){
						checknum++;
					}
					Word1NodeExNow=Word1NodeExNow->next;
				}
				Fmode++;
				break;
			case 3:
				Word2NodeExNow=Word2NodeExFirst;
				while(Word2NodeExNow!=NULL){
					if(Word2NodeExNow->useranswercheck!=1){
						checknum++;
					}
					Word2NodeExNow=Word2NodeExNow->next;
				}
				Fmode++;
				break;
			case 4:
				Word3NodeExNow=Word3NodeExFirst;
				while(Word3NodeExNow!=NULL){
					if(Word3NodeExNow->useranswercheck!=1){
						checknum++;
					}
					Word3NodeExNow=Word3NodeExNow->next;
				}
				Fmode++;
				break;
			case 5:
				Word4NodeNow=Word4NodeFirst;
				while(Word4NodeNow!=NULL){
					if(Word4NodeNow->useranswercheck!=1){
						checknum++;
					}
					Word4NodeNow=Word4NodeNow->next;
				}
				Fmode++;
				break;
		}
	}
	if(checknum==0){
		if(wordpersoncheckyesno("\n您已完成作答。是否提交?")==1){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		printf("\n您還有%d題未作答。\n是否提交",checknum);
		if(wordpersoncheckyesno("?")==1){
			return 1;
		}
		else{
			return 0;
		}
	}
}

void testmenuscore(int mode){
	extern int TestCheckQuestionNum[9];
	extern char ETSLoginUserName[999];
	int qmode,Fmode=1,qBnum=1;
	//===========================
	QuestionCheckAnswer(mode);
	//===========================
	testmenu1(mode,2);
	printf("成績結果公布：\n\n");
	printf("%s，您本次測驗分數加總如下：\n",ETSLoginUserName);
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
				printf("%s、單字題，共答對 %d 題，%d 分。\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[1],TestCheckQuestionNum[2]);
				Fmode++;
				qBnum++;
				break;
			case 3:
				printf("%s、填充題，共答對 %d 題，%d 分。\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[3],TestCheckQuestionNum[4]);
				Fmode++;
				qBnum++;
				break;
			case 4:
				printf("%s、選擇題，共答對 %d 題，%d 分。\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[5],TestCheckQuestionNum[6]);
				Fmode++;
				qBnum++;
				break;
			case 5:
				printf("%s、閱\讀題，共答對 %d 題，%d 分。\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[7],TestCheckQuestionNum[8]);
				Fmode++;
				qBnum++;
				break;
		}
	}
	printf("\n實得總分： %d 分。\n",TestCheckQuestionNum[0]);
	//====================
	UserTestSaveRecord(mode);
	//====================
	system("pause");
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
	if(str1[0]=='A' || str1[0]=='a'){
		return 1;
	}
	else if(str1[0]=='B' || str1[0]=='b'){
		return 2;
	}
	else if(str1[0]=='C' || str1[0]=='c'){
		return 3;
	}
	else if(str1[0]=='D' || str1[0]=='d'){
		return 4;
	}
	else{
		return 0;
	}
}

char* QuestionNumChinese(int num){
	switch(num){
		case 1:
			return "一";
			break;
		case 2:
			return "二";
			break;
		case 3:
			return "三";
			break;
		case 4:
			return "四";
			break;
	}
}
