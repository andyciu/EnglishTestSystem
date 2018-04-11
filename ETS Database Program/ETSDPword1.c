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
	printf("英文測驗系統題庫管理程式>>新增單字題\n");
	//=================
	BOOKcreatestart:
	printf("\n請輸入題庫檔案名稱：（若不存在則會自動建立）\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\1\\%s.etd1",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		BOOKnewword:
		printf("\n此題庫檔案共%d筆單字:\n",num1);
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
		//printf("\n請輸入新英文單字：");
		//fflush(stdin);
		//gets(wordstr[0].eng);
		wordpersoncheckstring("\n請輸入新英文單字：",wordstr[0].eng);
		//printf("請輸入其中文釋義：");
		//fflush(stdin);
		//gets(wordstr[0].chi);
		wordpersoncheckstring("\n請輸入其中文釋義：",wordstr[0].chi);
		//==========================================
		if(num1>0){
			printf("比對中...\n");
			for(i=0;i<num1;i++){
				if(strcmp(wordstr[0].eng,(wordstrn+i)->eng)==0){
					printf("您所輸入的英文單字已存在!是否重試");
					goto BOOKnewwordretry;
				}
			}
			printf("比對完成，新增資料...\n");
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
		printf("新增資料完成!是否繼續");
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
		printf("系統中無此檔案，已新增。\n");
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
	printf("英文測驗系統題庫管理程式>>修改單字題\n");
	//=================
	BOOKeditstart:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\1\\%s.etd1",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//==========================================
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		if(num1<=0){
			printf("此題庫尚無資料!\n");
			goto BOOKeditexit1;
		}
		BOOKeditword:
		printf("\n此題庫檔案共%d筆單字:\n",num1);
		wordstrn=(WORDTR*) malloc(num1*sizeof(WORDTR));
		fseek(fptr,-num1*sizeof(WORDTR),SEEK_END);
		fread(wordstrn,sizeof(WORDTR),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s %s\n",i+1,(wordstrn+i)->eng,(wordstrn+i)->chi);
		}
		//==========================================
		printf("\n請輸入欲修改之英文單字：");
		fflush(stdin);
		gets(input2);
		for(i=0;i<num1;i++){
			if(strcmp((wordstrn+i)->eng,input2)==0){
				printf("\n已找到資料，單字：%s,中文釋義：%s\n",(wordstrn+i)->eng,(wordstrn+i)->chi);
				//printf("請輸入修改後之英文單字：");
				//fflush(stdin);
				//gets(wordstrnew[0].eng);
				wordpersoncheckstring("\n請輸入修改後之英文單字：",wordstrnew[0].eng);
				//printf("請輸入修改後之中文釋義：");
				//fflush(stdin);
				//gets(wordstrnew[0].chi);
				wordpersoncheckstring("\n請輸入修改後之中文釋義：",wordstrnew[0].chi);
				//====================================
				printf("比對中...\n");
				for(j=0;j<num1;j++){
					if((i!=j) && (strcmp(wordstrnew[0].eng,(wordstrn+j)->eng)==0)){
						printf("您所輸入的英文單字已存在!是否重試");
						goto BOOKeditwordretry;
					}
				}
				printf("比對完成，修改資料...\n");
				//====================================
				fseek(fptr,-(num1-i)*sizeof(WORDTR),SEEK_END);
				fwrite(wordstrnew,sizeof(WORDTR),1,fptr);
				//====================================
				printf("修改資料完成!是否繼續");
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
		//==========================================若無找到資料 
		free(wordstrn);
		if(wordpersoncheckyesno("找不到資料...是否離開?")==1){
			fclose(fptr);
			return;
		}
		else{
			goto BOOKeditword;
		}
		//==========================================	
	}
	else{
		printf("開啟檔案失敗!...");
		BOOKeditexit1:
		if(wordpersoncheckyesno("是否離開?")==1){
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
	printf("英文測驗系統題庫管理程式>>刪除單字題\n");
	//=================
	BOOKdelstart:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\1\\%s.etd1",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//==========================================
		BOOKdelword:
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		if(num1<=0){
			printf("此題庫尚無資料!\n");
			goto BOOKdelexit;
		}
		printf("\n此題庫檔案共%d筆單字:\n",num1);
		wordstr=(WORDTR*) malloc(num1*sizeof(WORDTR));
		fseek(fptr,-num1*sizeof(WORDTR),SEEK_END);
		fread(wordstr,sizeof(WORDTR),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s %s\n",i+1,(wordstr+i)->eng,(wordstr+i)->chi);
		}
		//==========================================
		printf("請輸入欲刪除之英文單字：");
		fflush(stdin);
		gets(input2);
		for(i=0;i<num1;i++){
			if(strcmp((wordstr+i)->eng,input2)==0){
				printf("\n已找到資料，單字：%s,中文釋義：%s\n",(wordstr+i)->eng,(wordstr+i)->chi);
				if(wordpersoncheckyesno("是否確認刪除這筆資料?")==1){
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
					printf("刪除資料完成!\n");
				}
				//====================================
				free(wordstr);
				if(wordpersoncheckyesno("是否繼續?")==1){
					fptr = fopen(filename2,"r+b");
					goto BOOKdelword;
				}
				else{
					return;
				}
			}
		}
		//==========================================若無找到資料 
		free(wordstr);
		if(wordpersoncheckyesno("找不到資料...是否離開?")==1){
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
		printf("開啟檔案失敗!...");
		BOOKdelexit:
		if(wordpersoncheckyesno("是否離開?")==1){
			return;
		}
		else{
			goto BOOKdelstart;
		}
	}
}
