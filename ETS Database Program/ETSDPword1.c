#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wordt{
	char eng[30];
	char chi[99];
};
typedef struct wordt WORDTR;

struct worddatanumstruct{
	int datanum;
};
typedef struct worddatanumstruct WORDDATANUM;
//====================================
int wordpersoncheckyesno(char *);
void wordpersoncheckstring(char *,char *);
//====================================

void word1create(void){
	char filename1[255],filename2[999];
	char input;
	FILE *fptr;
	int i,j,num1=0,k=0;
	WORDTR wordstr[1],*wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�s�W��r�D\n");
	//=================
	BOOKcreatestart:
	printf("\n�п�J�D�w�ɮצW�١G�]�Y���s�b�h�|�۰ʫإߡ^\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\1\\%s.etd1",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("�}���ɮצ��\\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		BOOKnewword:
		printf("\n���D�w�ɮצ@%d����r:\n",num1);
		if(num1>0){
			wordstrn=(WORDTR*) malloc(num1*sizeof(WORDTR));
			fseek(fptr,-num1*sizeof(WORDTR),SEEK_END);
			fread(wordstrn,sizeof(WORDTR),num1,fptr);
			for(i=0;i<num1;i++){
				printf("%d.%s %s\n",i+1,(wordstrn+i)->eng,(wordstrn+i)->chi);
			}
			k=1;
		}
		//==========================================
		//printf("\n�п�J�s�^���r�G");
		//fflush(stdin);
		//gets(wordstr[0].eng);
		wordpersoncheckstring("\n�п�J�s�^���r�G",wordstr[0].eng);
		//printf("�п�J�䤤�����q�G");
		//fflush(stdin);
		//gets(wordstr[0].chi);
		wordpersoncheckstring("\n�п�J�䤤�����q�G",wordstr[0].chi);
		//==========================================
		if(num1>0){
			printf("��襤...\n");
			for(i=0;i<num1;i++){
				if(strcmp(wordstr[0].eng,(wordstrn+i)->eng)==0){
					printf("�z�ҿ�J���^���r�w�s�b!�O�_����");
					goto BOOKnewwordretry;
				}
			}
			printf("��粒���A�s�W���...\n");
		}
		/*==========================================
		rewind(fptr);
		fprintf(fptr,"[%d]\n",++num1);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR),1,fptr);
		//==========================================*/
		rewind(fptr);
		wordnum[0].datanum=++num1;
		fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR),1,fptr);
		//==========================================
		printf("�s�W��Ƨ���!�O�_�~��");
		BOOKnewwordretry: 
		if(k==1){
			free(wordstrn);
			k=0;
		}
		if(wordpersoncheckyesno("?")==1){
			goto BOOKnewword;
		}
		else{
			fclose(fptr);
			return;
		}
	}
	else{
		fptr = fopen(filename2,"w+b");
		printf("�t�Τ��L���ɮסA�w�s�W�C\n");
		goto BOOKnewword;
	}
}
void word1edit(void){
	char filename1[255],filename2[999];
	char input,input2[999];
	FILE *fptr;
	int i,j,num1=0;
	WORDTR wordstrnew[1],*wordstrn;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�ק��r�D\n");
	//=================
	BOOKeditstart:
	printf("\n�п�J�D�w�ɮצW�١G\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\1\\%s.etd1",filename1);
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
			goto BOOKeditexit1;
		}
		BOOKeditword:
		printf("\n���D�w�ɮצ@%d����r:\n",num1);
		wordstrn=(WORDTR*) malloc(num1*sizeof(WORDTR));
		fseek(fptr,-num1*sizeof(WORDTR),SEEK_END);
		fread(wordstrn,sizeof(WORDTR),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s %s\n",i+1,(wordstrn+i)->eng,(wordstrn+i)->chi);
		}
		//==========================================
		printf("\n�п�J���ק蠟�^���r�G");
		fflush(stdin);
		gets(input2);
		for(i=0;i<num1;i++){
			if(strcmp((wordstrn+i)->eng,input2)==0){
				printf("\n�w����ơA��r�G%s,�������q�G%s\n",(wordstrn+i)->eng,(wordstrn+i)->chi);
				//printf("�п�J�ק�ᤧ�^���r�G");
				//fflush(stdin);
				//gets(wordstrnew[0].eng);
				wordpersoncheckstring("\n�п�J�ק�ᤧ�^���r�G",wordstrnew[0].eng);
				//printf("�п�J�ק�ᤧ�������q�G");
				//fflush(stdin);
				//gets(wordstrnew[0].chi);
				wordpersoncheckstring("\n�п�J�ק�ᤧ�������q�G",wordstrnew[0].chi);
				//====================================
				printf("��襤...\n");
				for(j=0;j<num1;j++){
					if((i!=j) && (strcmp(wordstrnew[0].eng,(wordstrn+j)->eng)==0)){
						printf("�z�ҿ�J���^���r�w�s�b!�O�_����");
						goto BOOKeditwordretry;
					}
				}
				printf("��粒���A�ק���...\n");
				//====================================
				fseek(fptr,-(num1-i)*sizeof(WORDTR),SEEK_END);
				fwrite(wordstrnew,sizeof(WORDTR),1,fptr);
				//====================================
				printf("�ק��Ƨ���!�O�_�~��");
				BOOKeditwordretry:
				free(wordstrn);
				if(wordpersoncheckyesno("?")==1){
					goto BOOKeditword;
				}
				else{
					fclose(fptr);
					return;
				}
			}
		}
		//==========================================�Y�L����� 
		free(wordstrn);
		if(wordpersoncheckyesno("�䤣����...�O�_���}?")==1){
			fclose(fptr);
			return;
		}
		else{
			goto BOOKeditword;
		}
		//==========================================	
	}
	else{
		printf("�}���ɮץ���!...");
		BOOKeditexit1:
		if(wordpersoncheckyesno("�O�_���}?")==1){
			return;
		}
		else{
			goto BOOKeditstart;
		}
	}
}
void word1del(void){
	char filename1[255],filename2[999];
	char input,input2[999];
	FILE *fptr;
	int i,j,num1=0;
	WORDTR *wordstr;
	WORDDATANUM wordnum[1];
	//=================
	system("cls");
	printf("�^�����t���D�w�޲z�{��>>�R����r�D\n");
	//=================
	BOOKdelstart:
	printf("\n�п�J�D�w�ɮצW�١G\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\1\\%s.etd1",filename1);
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
		printf("\n���D�w�ɮצ@%d����r:\n",num1);
		wordstr=(WORDTR*) malloc(num1*sizeof(WORDTR));
		fseek(fptr,-num1*sizeof(WORDTR),SEEK_END);
		fread(wordstr,sizeof(WORDTR),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s %s\n",i+1,(wordstr+i)->eng,(wordstr+i)->chi);
		}
		//==========================================
		printf("�п�J���R�����^���r�G");
		fflush(stdin);
		gets(input2);
		for(i=0;i<num1;i++){
			if(strcmp((wordstr+i)->eng,input2)==0){
				printf("\n�w����ơA��r�G%s,�������q�G%s\n",(wordstr+i)->eng,(wordstr+i)->chi);
				if(wordpersoncheckyesno("�O�_�T�{�R���o�����?")==1){
					fclose(fptr);
					fptr = fopen(filename2,"wb");
					//fprintf(fptr,"[%d]",--num1);
					wordnum[0].datanum=--num1;
					fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
					for(j=0;j<num1+1;j++){
						if(i!=j){
							fwrite((wordstr+j),sizeof(WORDTR),1,fptr);
						}
					}
					fclose(fptr);
					printf("�R����Ƨ���!\n");
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
		}
		//==========================================�Y�L����� 
		free(wordstr);
		if(wordpersoncheckyesno("�䤣����...�O�_���}?")==1){
			fclose(fptr);
			return;
		}
		else{
			rewind(fptr);
			goto BOOKdelword;
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
