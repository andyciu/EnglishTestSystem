#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//====================================
int word2strcheck(char* , char*);
int wordpersoncheckyesno(char *);
void wordpersoncheckstring(char *,char *);
//====================================
struct wordt2{
	char mainstr[100];
	char ans[30];
};
typedef struct wordt2 WORDTR2;

struct worddatanumstruct{
	int datanum;
};
typedef struct worddatanumstruct WORDDATANUM;
//=================================

void word2create(void){
	char filename1[255],filename2[999];
	char input;
	FILE *fptr;
	int i,j,num1=0,k=0;
	WORDTR2 wordstr[1],*wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�s�W��R�D\n");
	//=================
	BOOKcreatestart:
	printf("\n�п�J�D�w�ɮצW�١G�]�Y���s�b�h�|�۰ʫإߡ^\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\2\\%s.etd2",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("�}���ɮצ��\\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		BOOKnewword2:
		printf("\n���D�w�ɮצ@%d���D��:\n",num1);
		if(num1>0){
			wordstrn=(WORDTR2 *) malloc(num1*sizeof(WORDTR2));
			fseek(fptr,-num1*sizeof(WORDTR2),SEEK_END);
			fread(wordstrn,sizeof(WORDTR2),num1,fptr);
			for(i=0;i<num1;i++){
				printf("%d.%s, Ans:%s\n",i+1,(wordstrn+i)->mainstr,(wordstrn+i)->ans);
			}
			k=1;
		}
		//==========================================
		//printf("\n�п�J�s�^��y�l(����)�G");
		wordpersoncheckstring("\n�п�J�s�^��y�l(����)�G",wordstr[0].mainstr);
		//fflush(stdin);
		//gets(wordstr[0].mainstr);
		//printf("�п�J����:");
		wordpersoncheckstring("�п�J����:",wordstr[0].ans);
		//fflush(stdin);
		//gets(wordstr[0].ans);
		//==========================================
		printf("��襤...\n");
		if(word2strcheck(wordstr[0].mainstr,wordstr[0].ans) == 1){
			if(num1>0){
				for(i=0;i<num1;i++){
					if(strcmp(wordstr[0].mainstr,(wordstrn+i)->mainstr)==0){
						printf("�z�ҿ�J���y�l�w�s�b!�O�_����");
						goto BOOKnewword2retry;
					}
				}
			}
		}
		else{
			printf("�L�k�b�y�l�����P���׬۲ŦX����r...�O�_����");
			goto BOOKnewword2retry;
		}
		//=========================================
		printf("��粒���A�s�W���...\n");
		rewind(fptr);
		//fprintf(fptr,"[%d]",++num1);
		wordnum[0].datanum=++num1;
		fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR2),1,fptr);
		//==========================================
		printf("�s�W��Ƨ���!�O�_�~��");
		BOOKnewword2retry:
		if(k==1){
			free(wordstrn);
			k=0;
		}
		if(wordpersoncheckyesno("?")==1){
			goto BOOKnewword2;
		}
		else{
			fclose(fptr);
			return;
		}
	}
	else{
		fptr = fopen(filename2,"w+b");
		printf("�t�Τ��L���ɮסA�w�s�W�C\n");
		goto BOOKnewword2;
	}
}

void word2edit(void){
	char filename1[255],filename2[999];
	char input;
	FILE *fptr;
	int i,j,num1=0,input2;
	WORDTR2 wordstrnew[1],*wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�ק��R�D\n");
	//=================
	BOOKeditstart2:
	printf("\n�п�J�D�w�ɮצW�١G\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\2\\%s.etd2",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("�}���ɮצ��\\!\n");
		//==========================================
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		if(num1<=0){
			printf("���D�w�|�L���!\n");
			goto BOOKeditexit2;
		}
		BOOKeditword2:
		printf("\n���D�w�ɮצ@%d���D��:\n",num1);
		wordstrn=(WORDTR2 *) malloc(num1*sizeof(WORDTR2));
		fseek(fptr,-num1*sizeof(WORDTR2),SEEK_END);
		fread(wordstrn,sizeof(WORDTR2),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s, Ans:%s\n",i+1,(wordstrn+i)->mainstr,(wordstrn+i)->ans);
		}
		//==========================================
		printf("\n�п�J���ק蠟�^��y�l�s���G");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2);
		if(input2>0 && input2<=num1){
			printf("\n��%d����ơA�y�l�G%s,���סG%s\n",input2,(wordstrn+(input2-1))->mainstr,(wordstrn+(input2-1))->ans);
			//printf("�п�J�ק�ᤧ�^��y�l�G");
			//fflush(stdin);
			//gets(wordstrnew[0].mainstr);
			wordpersoncheckstring("�п�J�ק�ᤧ�^��y�l�G",wordstrnew[0].mainstr);
			//printf("�п�J�ק�ᤧ���סG");
			//fflush(stdin);
			//gets(wordstrnew[0].ans);
			wordpersoncheckstring("�п�J�ק�ᤧ���סG",wordstrnew[0].ans);
			//====================================
			printf("��襤...\n");
			if(word2strcheck(wordstrnew[0].mainstr,wordstrnew[0].ans) == 1){
				if(num1>0){
					for(j=0;j<num1;j++){
						if(((input2-1)!=j) && (strcmp(wordstrnew[0].mainstr,(wordstrn+j)->mainstr)==0)){
							printf("�z�ҿ�J���y�l�w�s�b!�O�_����");
							goto BOOKeditword2retry;
						}
					}
				}
			}
			else{
				printf("�L�k�b�y�l�����P���׬۲ŦX����r...�O�_����");
				goto BOOKeditword2retry;
			}
			//====================================
			printf("��粒���A�ק���...\n");
			fseek(fptr,-(num1-(input2-1))*sizeof(WORDTR2),SEEK_END);
			fwrite(wordstrnew,sizeof(WORDTR2),1,fptr);
			printf("�ק��Ƨ���!�O�_�~��");
			//====================================
			BOOKeditword2retry:
			free(wordstrn);
			if(wordpersoncheckyesno("?")==1){
				goto BOOKeditword2;
			}
			else{
				fclose(fptr);
				return;
			}
		}
		//==========================================�Y�L����� 
		free(wordstrn);
		if(wordpersoncheckyesno("��J�s�����~!�O�_����?")==1){
			goto BOOKeditword2;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("�}���ɮץ���!...");
		BOOKeditexit2:
		if(wordpersoncheckyesno("�O�_���}?")==1){
			return;
		}
		else{
			goto BOOKeditstart2;
		}
	}
}

void word2del(void){
	char filename1[255],filename2[999];
	char input;
	FILE *fptr;
	int i,j,num1=0,input2;
	WORDTR2 *wordstr;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�R����R�D\n");
	//=================
	BOOKdelstart:
	printf("\n�п�J�D�w�ɮצW�١G\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\2\\%s.etd2",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("�}���ɮצ��\\!\n");
		//==========================================
		BOOKdelword:
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		if(num1<=0){
			printf("���D�w�|�L���!\n");
			goto BOOKdelexit;
		}
		printf("\n���D�w�ɮצ@%d���D��:\n",num1);
		wordstr=(WORDTR2*) malloc(num1*sizeof(WORDTR2));
		fread(wordstr,sizeof(WORDTR2),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s, Ans:%s\n",i+1,(wordstr+i)->mainstr,(wordstr+i)->ans);
		}
		//==========================================
		printf("�п�J���R�����^��y�l�s���G");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2); 
		if(input2>0 && input2<=num1){
			printf("\n��%d����ơA�y�l�G%s,���סG%s\n",input2,(wordstr+(input2-1))->mainstr,(wordstr+(input2-1))->ans);
			if(wordpersoncheckyesno("�O�_�T�{�R���o�����?")==1){
				fclose(fptr);
				fptr = fopen(filename2,"wb");
				//fprintf(fptr,"[%d]",--num1);
				wordnum[0].datanum=--num1;
				fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
				for(j=0;j<num1+1;j++){
					if((input2-1)!=j){
						fwrite((wordstr+j),sizeof(WORDTR2),1,fptr);
					}
				}
				fclose(fptr);
				printf("\n�R����Ƨ���!\n");
			}
			//====================================
			free(wordstr);
			if(wordpersoncheckyesno("�O�_�~��?")==1){
				fptr = fopen(filename2,"r+b");
				goto BOOKdelword;
			}
			else{
				return;
			}
		}
		//==========================================�Y�L����� 
		free(wordstr);
		if(wordpersoncheckyesno("��J�s�����~!�O�_����?")==1){
			rewind(fptr);
			goto BOOKdelword;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("�}���ɮץ���!...");
		BOOKdelexit:
		if(wordpersoncheckyesno("�O�_���}?")==1){
			return;
		}
		else{
			goto BOOKdelstart;
		}
	}
}

int word2strcheck(char *str1,char *str2){
	int i=strlen(str1);
	int j,k=0,p=0;
	
	for(j=0;j<i+1;j++){
		if(str1[j]==str2[0] && p==0){
			p=1;
		}
		if(p==1){
			if(k>=strlen(str2)){
				if((str1[j]>='A' && str1[j]<='Z') || (str1[j]>='a' && str1[j]<='z')){
					p=0;
				}
				else{
					return 1;
				}
			}
			else if(str1[j]!=str2[k++]){
				p=0;
				k=0;
			}
		}
	}
	return 0;
}
