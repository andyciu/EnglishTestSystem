#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//====================================
int wordpersoncheckyesno(char *);
int wordpersoncheckabcd(char *);
void wordpersoncheckstring(char *,char *);
//====================================
struct wordt3{
	char question[200];
	char a1[50];
	char a2[50];
	char a3[50];
	char a4[50];
	int answer;
};
typedef struct wordt3 WORDTR3;

struct worddatanumstruct{
	int datanum;
};
typedef struct worddatanumstruct WORDDATANUM;
//====================================
void word3create(void){
	char filename1[255],filename2[999],answern;
	char input;
	FILE *fptr;
	int i,j,num1=0,k=0;
	WORDTR3 wordstr[1],*wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�s�W����D\n");
	//=================
	BOOKcreatestart:
	printf("\n�п�J�D�w�ɮצW�١G�]�Y���s�b�h�|�۰ʫإߡ^\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\3\\%s.etd3",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("�}���ɮצ��\\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		BOOKnewword3:
		printf("\n���D�w�ɮצ@%d���D��:\n",num1);
		if(num1>0){
			wordstrn=(WORDTR3 *) malloc(num1*sizeof(WORDTR3));
			fseek(fptr,-num1*sizeof(WORDTR3),SEEK_END);
			fread(wordstrn,sizeof(WORDTR3),num1,fptr);
			for(i=0;i<num1;i++){
				printf("%d.%s\n",i+1,(wordstrn+i)->question);
			}
			k=1;
		}
		//==========================================
		//printf("\n�п�J�s�D�ءG");
		//fflush(stdin);
		//gets(wordstr[0].question);
		wordpersoncheckstring("\n�п�J�s�D�ءG",wordstr[0].question);
		//==========================================
		printf("��襤...");
		if(num1>0){
			for(i=0;i<num1;i++){
				if(strcmp(wordstr[0].question,(wordstrn+i)->question)==0){
					printf("�z�ҿ�J���D�ؤw�s�b!");
					goto BOOKnewword3retry;
				}
			}
		}
		printf("��粒���C\n");
		//=========================================
		//printf("�п�J�ﶵ(A):");
		//fflush(stdin);
		//gets(wordstr[0].a1);
		wordpersoncheckstring("�п�J�ﶵ(A):",wordstr[0].a1);
		//printf("�п�J�ﶵ(B):");
		//fflush(stdin);
		//gets(wordstr[0].a2);
		wordpersoncheckstring("�п�J�ﶵ(B):",wordstr[0].a2);
		//printf("�п�J�ﶵ(C):");
		//fflush(stdin);
		//gets(wordstr[0].a3);
		wordpersoncheckstring("�п�J�ﶵ(C):",wordstr[0].a3);
		//printf("�п�J�ﶵ(D):");
		//fflush(stdin);
		//gets(wordstr[0].a4);
		wordpersoncheckstring("�п�J�ﶵ(D):",wordstr[0].a4);
		//=========================================
		wordstr[0].answer=wordpersoncheckabcd("�п�J����:");
		//=========================================
		printf("�s�W���...\n");
		rewind(fptr);
		//fprintf(fptr,"[%d]",++num1);
		wordnum[0].datanum=++num1;
		fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR3),1,fptr);
		//==========================================
		printf("�s�W��Ƨ���!");
		BOOKnewword3retry:
		if(k==1){
			free(wordstrn);
			k=0;
		}
		if(wordpersoncheckyesno("�O�_�~��?")==1){
			goto BOOKnewword3;
		}
		else{
			fclose(fptr);
			return;
		}
	}
	else{
		fptr = fopen(filename2,"w+b");
		printf("�t�Τ��L���ɮסA�w�s�W�C\n");
		goto BOOKnewword3;
	}
}

void word3edit(void){
	char filename1[255],filename2[999];
	char input,answern;
	FILE *fptr;
	int i,j,num1=0,input2;
	WORDTR3 wordstrnew[1],*wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�ק����D\n");
	//=================
	BOOKeditstart3:
	printf("\n�п�J�D�w�ɮצW�١G\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\3\\%s.etd3",filename1);
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
			goto BOOKeditexit3;
		}
		BOOKeditword3:
		printf("\n���D�w�ɮצ@%d���D��:\n",num1);
		wordstrn=(WORDTR3 *) malloc(num1*sizeof(WORDTR3));
		fseek(fptr,-num1*sizeof(WORDTR3),SEEK_END);
		fread(wordstrn,sizeof(WORDTR3),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s\n",i+1,(wordstrn+i)->question);
		}
		//==========================================
		printf("\n�п�J���ק蠟�D�ؽs���G");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2);
		if(input2>0 && input2<=num1){
			printf("\n��%d����ơA�D��:%s\n",input2,(wordstrn+(input2-1))->question);
			printf("(A)%s\n",(wordstrn+(input2-1))->a1);
			printf("(B)%s\n",(wordstrn+(input2-1))->a2);
			printf("(C)%s\n",(wordstrn+(input2-1))->a3);
			printf("(D)%s\n",(wordstrn+(input2-1))->a4);
			printf("����:(%c)\n",((wordstrn+(input2-1))->answer)+64);
			//============================================================
			if(wordpersoncheckyesno("�O�_�ק��D��?")==1){
				//printf("�п�J�ק�ᤧ�D�ءG");
				//fflush(stdin);
				//gets(wordstrnew[0].question);
				wordpersoncheckstring("�п�J�ק�ᤧ�D�ءG",wordstrnew[0].question);
				printf("��襤...");
				if(num1>0){
					for(i=0;i<num1;i++){
						if((i!=(input2-1)) && (strcmp(wordstrnew[0].question,(wordstrn+i)->question)==0)){
							printf("�z�ҿ�J���D�ؤw�s�b!�O�_����");
							goto BOOKeditword3retry;
						}
					}
				}
				printf("��粒���C\n");
			}
			else{
				sprintf(wordstrnew[0].question,"%s",(wordstrn+(input2-1))->question);
			}
			//==================
			if(wordpersoncheckyesno("�O�_�ק�ﶵ(A)?")==1){
				//printf("�п�J�ק�ᤧ�ﶵ(A):");
				//fflush(stdin);
				//gets(wordstrnew[0].a1);
				wordpersoncheckstring("�п�J�ק�ᤧ�ﶵ(A):",wordstrnew[0].a1);
			}
			else{
				sprintf(wordstrnew[0].a1,"%s",(wordstrn+(input2-1))->a1);
			}
			//==================
			if(wordpersoncheckyesno("�O�_�ק�ﶵ(B)?")==1){
				//printf("�п�J�ק�ᤧ�ﶵ(B):");
				//fflush(stdin);
				//gets(wordstrnew[0].a2);
				wordpersoncheckstring("�п�J�ק�ᤧ�ﶵ(B):",wordstrnew[0].a2);
			}
			else{
				sprintf(wordstrnew[0].a2,"%s",(wordstrn+(input2-1))->a2);
			}
			//==================
			if(wordpersoncheckyesno("�O�_�ק�ﶵ(C)?")==1){
				//printf("�п�J�ק�ᤧ�ﶵ(C):");
				//fflush(stdin);
				//gets(wordstrnew[0].a3);
				wordpersoncheckstring("�п�J�ק�ᤧ�ﶵ(C):",wordstrnew[0].a3);
			}
			else{
				sprintf(wordstrnew[0].a3,"%s",(wordstrn+(input2-1))->a3);
			}
			//==================
			if(wordpersoncheckyesno("�O�_�ק�ﶵ(D)?")==1){
				//printf("�п�J�ק�ᤧ�ﶵ(D):");
				//fflush(stdin);
				//gets(wordstrnew[0].a4);
				wordpersoncheckstring("�п�J�ק�ᤧ�ﶵ(D):",wordstrnew[0].a4);
			}
			else{
				sprintf(wordstrnew[0].a4,"%s",(wordstrn+(input2-1))->a4);
			}
			//=========================================
			if(wordpersoncheckyesno("�O�_�קﵪ��?")==1){
				wordstrnew[0].answer=wordpersoncheckabcd("�п�J�ק�ᵪ��:");
			}
			else{
				wordstrnew[0].answer=(wordstrn+(input2-1))->answer;
			}
			//====================================
			printf("�ק���...\n");
			fseek(fptr,-(num1-(input2-1))*sizeof(WORDTR3),SEEK_END);
			fwrite(wordstrnew,sizeof(WORDTR3),1,fptr);
			//====================================
			printf("�ק��Ƨ���!�O�_�~��");
			BOOKeditword3retry:
			free(wordstrn);
			if(wordpersoncheckyesno("?")==1){
				goto BOOKeditword3;
			}
			else{
				fclose(fptr);
				return;
			}
		}
		//==========================================�Y�L����� 
		free(wordstrn);
		if(wordpersoncheckyesno("��J�s�����~!�O�_����?")==1){
			goto BOOKeditword3;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("�}���ɮץ���!...");
		BOOKeditexit3:
		if(wordpersoncheckyesno("�O�_���}?")==1){
			return;
		}
		else{
			goto BOOKeditstart3;
		}
	}
}

void word3del(void){
	char filename1[255],filename2[999];
	char input;
	FILE *fptr;
	int i,j,num1=0,input2;
	WORDTR3 *wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�R������D\n");
	//=================
	BOOKdelstart3:
	printf("\n�п�J�D�w�ɮצW�١G\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\3\\%s.etd3",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("�}���ɮצ��\\!\n");
		//==========================================
		BOOKdelword3:
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		if(num1<=0){
			printf("���D�w�|�L���!\n");
			goto BOOKdelexit3;
		}
		printf("\n���D�w�ɮצ@%d���D��:\n",num1);
		wordstrn=(WORDTR3 *) malloc(num1*sizeof(WORDTR3));
		fseek(fptr,-num1*sizeof(WORDTR3),SEEK_END);
		fread(wordstrn,sizeof(WORDTR3),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s\n",i+1,(wordstrn+i)->question);
		}
		//==========================================
		printf("�п�J���R�����D�ؽs���G");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2); 
		if(input2>0 && input2<=num1){
			printf("\n��%d����ơA�D��:%s\n",input2,(wordstrn+(input2-1))->question);
			printf("(A)%s\n",(wordstrn+(input2-1))->a1);
			printf("(B)%s\n",(wordstrn+(input2-1))->a2);
			printf("(C)%s\n",(wordstrn+(input2-1))->a3);
			printf("(D)%s\n",(wordstrn+(input2-1))->a4);
			printf("����:(%c)\n",((wordstrn+(input2-1))->answer)+64);
			if(wordpersoncheckyesno("�O�_�T�{�R���o�����?")==1){
				fclose(fptr);
				fptr = fopen(filename2,"wb");
				//fprintf(fptr,"[%d]",--num1);
				wordnum[0].datanum=--num1;
				fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
				for(j=0;j<num1+1;j++){
					if((input2-1)!=j){
						fwrite((wordstrn+j),sizeof(WORDTR3),1,fptr);
					}
				}
				fclose(fptr);
				printf("\n�R����Ƨ���!\n");
			}
			//====================================
			free(wordstrn);
			if(wordpersoncheckyesno("�O�_�~��?")==1){
				fptr = fopen(filename2,"r+b");
				goto BOOKdelword3;
			}
			else{
				return;
			}
		}
		//==========================================�Y�L����� 
		free(wordstrn);
		if(wordpersoncheckyesno("��J�s�����~!�O�_����?")==1){
			rewind(fptr);
			goto BOOKdelword3;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("�}���ɮץ���!...");
		BOOKdelexit3:
		if(wordpersoncheckyesno("�O�_���}?")==1){
			return;
		}
		else{
			goto BOOKdelstart3;
		}
	}
}
