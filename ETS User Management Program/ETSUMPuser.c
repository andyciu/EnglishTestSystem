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
			if(i==1) printf("\n\n�п�J�s���ϥΪ̦W�١G");
			else printf("�п�J�s�ϥΪ̤��K�X�G");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0' && i==1){
				printf("��J���~!�ЦA�դ@�M...\n");
				continue;
			}
			else{
				if(i==1) sprintf(PersonDatabaseUsernew[0].username,"%s",input);
				else sprintf(PersonDatabaseUsernew[0].password,"%s",input);
				i++;
			}
		}
		//===============
		printf("��襤....\n");
		for(i=0;i<num1;i++){
			if(strcmp((PersonDatabaseUser+i)->username,PersonDatabaseUsernew[0].username)==0){
				if(wordpersoncheckyesno("�z�ҿ�J�ϥΪ̤w�s�b!�O�_����?")==1){
					goto BOOKusercreate1;
				}
				else{
					return;
				}
			}
		}
		//================
		printf("��粒���C\n");
		if(ETSUsermode==3){
			while(1){
				printf("�п�J�ϥΪ̨����O�G\n(1.�ǥ�/2.�Юv/3.�t�κ޲z��)\n>");
				fflush(stdin);
				scanf("%d",&inputnum);
				//=================
				if(inputnum<=0 || inputnum>3){
					printf("��J���~!�Э��s��J...\n");
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
			printf("�����O���ѿ��~!���p���t�κ޲z��...\n");
		}
		//==================================
		rewind(fptr);
		PersonDatabaseMain[0].usernum=++num1;
		fwrite(PersonDatabaseMain,sizeof(PERSONDATAMAIN),1,fptr);
		//==================================
		fseek(fptr,0L,SEEK_END);
		fwrite(PersonDatabaseUsernew,sizeof(PERSONDATAUSER),1,fptr);
		printf("�s�W����! User:%s �����O:%s\n\n",PersonDatabaseUsernew[0].username,ETSUMPLoginmodeChinese(PersonDatabaseUsernew[0].usermode));
		fclose(fptr);
		system("pause");
	}
	else{
		BOOKopendatafail:
		printf("�}�ҨϥΪ̬����ɥ���!���p���t�κ޲z��...\n");
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
			printf("\n\n�ثe�ϥΪ̸�Ʀp�U�G\n");
			for(i=0;i<num1;i++){
				if(ETSUsermode==3 || (ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1)){
					printf("%d.User:%s  �����O:%s\n",i+1,(PersonDatabaseUser+i)->username,ETSUMPLoginmodeChinese((PersonDatabaseUser+i)->usermode));
				}
			} 
		}	
		//===============
		if(ETSUsermode==1 || mode==1){
			while(1){
				BOOKeditmode1:
				printf("\n\n�п�J��K�X�G");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0'){
					printf("��J���~!�ЦA�դ@�M...\n");
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
							if(wordpersoncheckyesno("��J���~!�O�_����?")==1){
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
				printf("�п�J�ק�ᤧ�K�X�G");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0'){
					printf("��J���~!�ЦA�դ@�M...\n");
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
				printf("\n\n�п�J���ק蠟�ϥΪ̦W�١G");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0'){
					printf("��J���~!�ЦA�դ@�M...\n");
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
					printf("�d�ߦ��\\�C"); 
					break;
				}
				else if(i==num1-1){
					printf("�d�ߥ��ѡC�t�άd�L���ϥΪ�...\n");
					return;
				} 
			}
		}
		else{
			i=1;
			while(i<=2){
				if(i==1) printf("\n\n�п�J���ק蠟�ϥΪ̦W�١G");
				else printf("�п�J�K�X�G");
				fflush(stdin);
				gets(input);
				if(input[0]=='\0' && i==1){
					printf("��J���~!�ЦA�դ@�M...\n");
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
					printf("�n�J���\\�C");
					if((ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1) || (ETSUsermode==1 && (PersonDatabaseUser+i)->usermode==1 && strcmp(ETSLoginUserName,(PersonDatabaseUser+i)->username)==0)) ;
					else{
						printf("�z�ثe���v������...���p���t�κ޲z���C\n");
						return;
					} 
					break;
				}
				else if(i==num1-1){
					printf("�d�ߥ��ѡC�t�άd�L���ϥΪ̩ο�J���ϥΪ̦W�٤αK�X���~...\n");
					return;
				}
			}
		}	
		//=========================
		BOOKuseredit1:
		if(strcmp((PersonDatabaseUser+usernum)->username,ETSLoginUserName)==0){
			printf("\n���涥�q���~�G�ثe�d�ߤ��b�����b�ϥΡC\n");
			return;
		}
		//========================= 
		i=1;
		while(i<=2){
			if(i==1) printf("�п�J�ק�ᤧ�ϥΪ̦W�١G");
			else printf("�п�J�ק�ᤧ�K�X�G");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0' && i==1){
				printf("��J���~!�ЦA�դ@�M...\n");
				continue;
			}
			else{
				if(i==1) sprintf(PersonDatabaseUsernew[0].username,"%s",input);
				else sprintf(PersonDatabaseUsernew[0].password,"%s",input);
				i++;
			}
		}
		//===============
		printf("��襤....\n");
		for(i=0;i<num1;i++){
			if(i!=usernum){
				if(strcmp((PersonDatabaseUser+i)->username,PersonDatabaseUsernew[0].username)==0){
					if(wordpersoncheckyesno("�z�ҿ�J�ϥΪ̤w�s�b!�O�_����?")==1){
						goto BOOKuseredit1;
					}
					else{
						return;
					}
				}
			} 	
		}
		printf("��粒���C\n");
		//==================================
		BOOKeditwritedata:
		if(ETSUsermode==3 && mode==2){
			while(1){
				printf("�п�J���ק蠟�ϥΪ̷s�����O�G\n(1.�ǥ�/2.�Юv/3.�t�κ޲z��)\n>");
				fflush(stdin);
				scanf("%d",&inputnum);
				//=================
				if(inputnum<=0 || inputnum>3){
					printf("��J���~!�Э��s��J...\n");
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
		printf("�ק粒��! User:%s �����O:%s\n\n",PersonDatabaseUsernew[0].username,ETSUMPLoginmodeChinese(PersonDatabaseUsernew[0].usermode));
		fclose(fptr);
		system("pause");
	}
	else{
		BOOKopendatafail:
		printf("�}�ҨϥΪ̬����ɥ���!���p���t�κ޲z��...\n");
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
		printf("\n\n�ثe�ϥΪ̸�Ʀp�U�G\n");
		for(i=0;i<num1;i++){
			if(ETSUsermode==3 || (ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1)){
				printf("%d.User:%s  �����O:%s\n",i+1,(PersonDatabaseUser+i)->username,ETSUMPLoginmodeChinese((PersonDatabaseUser+i)->usermode));
			}
		} 
		//=============
		BOOKuserdelete1:
		while(1){
			printf("�п�J���R�����ϥΪ̦W�١G");
			fflush(stdin);
			gets(input);
			if(input[0]=='\0'){
				printf("��J���~!�ЦA�դ@�M...\n");
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
				printf("�d�ߦ��\\�C");
				break;
			}
			else if(i==num1-1){
				printf("�d�ߥ��ѡC�t�άd�L���ϥΪ�...\n");
				return;
			} 
		}
		if(ETSUsermode==3 || (ETSUsermode==2 && (PersonDatabaseUser+i)->usermode==1)) ;
		else{
			printf("\n�z�ثe���v������...���p���t�κ޲z���C\n");
			return;
		}
		//===============
		if(strcmp((PersonDatabaseUser+usernum)->username,ETSLoginUserName)==0){
			printf("\n���涥�q���~�G�ثe�d�ߤ��b�����b�ϥΡC\n");
			return;
		}
		//================
		if(num1>1){
			printf("\n�ϥΪ�:%s  �����O:%s\n�O�_�T�{�R���ϥΪ�",(PersonDatabaseUser+usernum)->username,ETSUMPLoginmodeChinese((PersonDatabaseUser+usernum)->usermode));
		}
		else{
			printf("\n���涥�q���~�A�ثe�ϥΪ̼Ƥw�F�̧C�зǤU���C\n");
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
			printf("�w�����R���C\n");
			system("pause");
		}
		else{
			return;
		}
		
	}
	else{
		BOOKopendatafail:
		printf("�}�ҨϥΪ̬����ɥ���!���p���t�κ޲z��...\n");
		exit(2);
	}
}
