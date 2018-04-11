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
	printf("\n\t\t\t�w��Ө�^�����t��\n");
	printf("\t\t       English Test System V1.0\n\t\t\t\t\t\t\t   2015 By AndyCiu.\n");
}

void mainmenu(void){
	char input;
	while(1){
		printf("\n\n�п�ܫ��O�G\n");
		//=================
		printf("1.�i��@�ӷs������\n");
		printf("2.�[�ݴ��絲�G����\n");
		//=================
		printf("0.���}\n");
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
				printf("��J���~!�Э��s��J�C\n");
		}
	}
}

void menu1(void){ //�i������� 
	char input;
	int usernum;
	while(1){
		printf("\n\n�п�ܫ��O�G\n");
		//=================
		printf("1.�i��s����X����\n");
		printf("2.�i��s����r����\n");
		printf("3.�i��s����R����\n");
		printf("4.�i��s����ܴ���\n");
		printf("5.�i��s���\\Ū����\n");
		//=================
		printf("0.�^��D���\n");
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
				if(usernum==1){  //�����D�w�H�����D
					testmenu1(2,1);
					testmenu2(2,1);
				}
				else if(usernum==2){ //���w�D�w���H�����D
					testmenu1(2,1);
					SystemRecordReset();
					if(menuadddataname(2)==0){
						testmenu2(2,2);
					}
				}
				break;
			case '3':
				usernum=menu1_2();
				if(usernum==1){  //�����D�w�H�����D
					testmenu1(3,1);
					testmenu2(3,1);
				}
				else if(usernum==2){ //���w�D�w���H�����D
					testmenu1(3,1);
					SystemRecordReset();
					if(menuadddataname(3)==0){
						testmenu2(3,2);
					}
				}
				break;
			case '4':
				usernum=menu1_2();
				if(usernum==1){  //�����D�w�H�����D
					testmenu1(4,1);
					testmenu2(4,1);
				}
				else if(usernum==2){ //���w�D�w���H�����D
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
				printf("��J���~!�Э��s��J�C\n");
		}
	}
}

int menu1_2(void){ 
	char input;
	while(1){
		printf("\n\n�п�ܫ��O�G\n");
		//=================
		printf("1.�ĥΥ����D�w�H�����D\n");
		printf("2.���w�D�w���H�����D\n");
		//=================
		printf("0.�^��D���\n");
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
				printf("��J���~!�Э��s��J�C\n");
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
			sprintf(modestr,"��X");
			break;
		case 2:
			sprintf(modestr,"��r");
			break;
		case 3:
			sprintf(modestr,"��R");
			break;
		case 4:
			sprintf(modestr,"���");
			break;
		case 5:
			sprintf(modestr,"�\\Ū");
			break;
			
	}
	if(timenum==1){
		printf("�^�����t��>>%s����\t\t\t�}�l�ɶ�:%s\n",modestr,ctime(&t1));
	}
	else{
		printf("�^�����t��>>%s����\t\t\t�}�l�ɶ�:%s\n",modestr,UserTestHistory->testtime);
	}
	printf("�ϥΪ�:%s\n\n",ETSLoginUserName);
}

void testmenu2(int mode,int num){
	extern char ETSLoginUserName[999];
	switch(mode){
		case 1:
			printf("�Y�N�}�l��X����A������ĥ��D�w�H�����D�A�@�����H�U�|�������G\n\n");
			printf("�@�B��r�D(5�D)�A�C�D3���A�@15��\n");
			printf("�G�B��R�D(5�D)�A�C�D3���A�@15��\n");
			printf("�T�B����D(10�D)�A�C�D5���A�@50��\n");
			printf("�|�B�\\Ū�D(2�D)�A�C�j�D10���A�@20��\n\n");
			printf("������X�p�@ 100 ���A�������˦�\n");
			if(wordpersoncheckyesno("�O�_�}�l����?")==1){
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
				printf("�Y�N�}�l��r����A������ĥ��D�w�H�����D�A�`�@����p�U�G\n\n");
			}
			else{
				printf("\n�Y�N�}�l��r����A������ī��w�D�w�D�w�H�����D�A�`�@����p�U�G\n\n");
			}
			printf("�@�B��r�D(10�D)�A�C�D10���A�@100��\n");
			printf("������X�p�@ 100 ���A�������˦�\n");
			if(wordpersoncheckyesno("�O�_�}�l����?")==1){
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
				printf("�Y�N�}�l��R����A������ĥ��D�w�H�����D�A�`�@����p�U�G\n\n");
			}
			else{
				printf("\n�Y�N�}�l��R����A������ī��w�D�w�D�w�H�����D�A�`�@����p�U�G\n\n");
			}
			printf("�@�B��R�D(10�D)�A�C�D10���A�@100��\n");
			printf("������X�p�@ 100 ���A�������˦�\n");
			if(wordpersoncheckyesno("�O�_�}�l����?")==1){
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
				printf("�Y�N�}�l��ܴ���A������ĥ��D�w�H�����D�A�`�@����p�U�G\n\n");
			}
			else{
				printf("\n�Y�N�}�l��ܴ���A������ī��w�D�w�D�w�H�����D�A�`�@����p�U�G\n\n");
			}
			printf("�@�B����D(10�D)�A�C�D10���A�@100��\n");
			printf("������X�p�@ 100 ���A�������˦�\n");
			if(wordpersoncheckyesno("�O�_�}�l����?")==1){
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
			printf("�Y�N�}�l�\\Ū����A������ĥ��D�w�H�����D�A�`�@����p�U�G\n\n");
			printf("�@�B�\\Ū�D(4�D)�A�C�j�D25���A�@100��\n\n");
			printf("������X�p�@ 100 ���A�������˦�\n");
			if(wordpersoncheckyesno("�O�_�}�l����?")==1){
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
		printf("\n�п�J���w�D�w�W�١G");
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
			printf("��J���~!�ЦA�դ@�M...\n");
		}
	}
}

void testmenu3(void){
	printf("\n");
	printf("Ctrl+Q=���}  Ctrl+B:���ܤW�@�D  Ctrl+N:���ܤU�@�D  Enter:�T�w\n");
}

void testmenumain(int mode){
	int i,j,k,qmode,qnum=1,qBnum=1,qnumMax=0,Fmode=1,Fqnum=1;
	extern int Word1TESTnum,Word2TESTnum,Word3TESTnum,Word4TESTnum,Word4chooseTESTnum,WordTesttot; //�ϥΪ̤���-�U�D���D�Ƭ��� 
	extern int TestScore[9];
	char answern[100];
	char userwere[100];
	//======================
	while(1){
		testmenu1(mode,2);
		testmenu3();
		qmode=mode;
		if(mode==1){  //��X���� 
			qmode+=Fmode;
		}
		switch(qmode){
			case 2: //��r�D 
				printf("\n%s�B��r�D(�C�D%d���A�@%d��):\n\n",QuestionNumChinese(qBnum),TestScore[1],TestScore[2]);
				qnumMax=Word1TESTnum;
				QuestionGet(1,qnum);
				break;
			case 3: //��R�D 
				printf("\n%s�B��R�D(�C�D%d���A�@%d��):\n\n",QuestionNumChinese(qBnum),TestScore[3],TestScore[4]);
				qnumMax=Word2TESTnum;
				QuestionGet(2,qnum);
				break;
			case 4: //����D 
				printf("\n%s�B����D(�C�D%d���A�@%d��):\n\n",QuestionNumChinese(qBnum),TestScore[5],TestScore[6]);
				qnumMax=Word3TESTnum;
				QuestionGet(3,qnum);
				break;
			case 5: //�\Ū�D 
				printf("\n%s�B�\\Ū�D(�C�j�D%d���A�@%d��):\n\n",QuestionNumChinese(qBnum),TestScore[7],TestScore[8]);
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
				printf("�w���}��������C\n");
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
						sprintf(answern,"%s",userwere); //�q�{���e�ҿ�J������ 
					}
					else{
						printf("��J���~!�ЦA�դ@�M...\n");
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
							printf("��J���׿��~!�ЦA�դ@�M:\n");
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
				case 1: //��r�D 
					if(qnum<=0){
						qnum=1;
					}
					else if(qnum>5){
						Fmode++;
						qBnum++;
						qnum=1;
					}
					break;
				case 2: //��R�D 
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
				case 3: //����D 
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
				case 4: //�\Ū�D 
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
		if(wordpersoncheckyesno("\n�z�w�����@���C�O�_����?")==1){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		printf("\n�z�٦�%d�D���@���C\n�O�_����",checknum);
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
	printf("���Z���G�����G\n\n");
	printf("%s�A�z����������ƥ[�`�p�U�G\n",ETSLoginUserName);
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
				printf("%s�B��r�D�A�@���� %d �D�A%d ���C\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[1],TestCheckQuestionNum[2]);
				Fmode++;
				qBnum++;
				break;
			case 3:
				printf("%s�B��R�D�A�@���� %d �D�A%d ���C\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[3],TestCheckQuestionNum[4]);
				Fmode++;
				qBnum++;
				break;
			case 4:
				printf("%s�B����D�A�@���� %d �D�A%d ���C\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[5],TestCheckQuestionNum[6]);
				Fmode++;
				qBnum++;
				break;
			case 5:
				printf("%s�B�\\Ū�D�A�@���� %d �D�A%d ���C\n",QuestionNumChinese(qBnum),TestCheckQuestionNum[7],TestCheckQuestionNum[8]);
				Fmode++;
				qBnum++;
				break;
		}
	}
	printf("\n��o�`���G %d ���C\n",TestCheckQuestionNum[0]);
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
				printf("��J���~!�Э��s��J�C\n");
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
			return "�@";
			break;
		case 2:
			return "�G";
			break;
		case 3:
			return "�T";
			break;
		case 4:
			return "�|";
			break;
	}
}
