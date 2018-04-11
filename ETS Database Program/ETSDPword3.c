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
	printf("英文測驗系統題庫管理程式>>新增選擇題\n");
	//=================
	BOOKcreatestart:
	printf("\n請輸入題庫檔案名稱：（若不存在則會自動建立）\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\3\\%s.etd3",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		BOOKnewword3:
		printf("\n此題庫檔案共%d筆題目:\n",num1);
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
		//printf("\n請輸入新題目：");
		//fflush(stdin);
		//gets(wordstr[0].question);
		wordpersoncheckstring("\n請輸入新題目：",wordstr[0].question);
		//==========================================
		printf("比對中...");
		if(num1>0){
			for(i=0;i<num1;i++){
				if(strcmp(wordstr[0].question,(wordstrn+i)->question)==0){
					printf("您所輸入的題目已存在!");
					goto BOOKnewword3retry;
				}
			}
		}
		printf("比對完成。\n");
		//=========================================
		//printf("請輸入選項(A):");
		//fflush(stdin);
		//gets(wordstr[0].a1);
		wordpersoncheckstring("請輸入選項(A):",wordstr[0].a1);
		//printf("請輸入選項(B):");
		//fflush(stdin);
		//gets(wordstr[0].a2);
		wordpersoncheckstring("請輸入選項(B):",wordstr[0].a2);
		//printf("請輸入選項(C):");
		//fflush(stdin);
		//gets(wordstr[0].a3);
		wordpersoncheckstring("請輸入選項(C):",wordstr[0].a3);
		//printf("請輸入選項(D):");
		//fflush(stdin);
		//gets(wordstr[0].a4);
		wordpersoncheckstring("請輸入選項(D):",wordstr[0].a4);
		//=========================================
		wordstr[0].answer=wordpersoncheckabcd("請輸入答案:");
		//=========================================
		printf("新增資料...\n");
		rewind(fptr);
		//fprintf(fptr,"[%d]",++num1);
		wordnum[0].datanum=++num1;
		fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR3),1,fptr);
		//==========================================
		printf("新增資料完成!");
		BOOKnewword3retry:
		if(k==1){
			free(wordstrn);
			k=0;
		}
		if(wordpersoncheckyesno("是否繼續?")==1){
			goto BOOKnewword3;
		}
		else{
			fclose(fptr);
			return;
		}
	}
	else{
		fptr = fopen(filename2,"w+b");
		printf("系統中無此檔案，已新增。\n");
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
	printf("英文測驗系統題庫管理程式>>修改選擇題\n");
	//=================
	BOOKeditstart3:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\3\\%s.etd3",filename1);
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
			goto BOOKeditexit3;
		}
		BOOKeditword3:
		printf("\n此題庫檔案共%d筆題目:\n",num1);
		wordstrn=(WORDTR3 *) malloc(num1*sizeof(WORDTR3));
		fseek(fptr,-num1*sizeof(WORDTR3),SEEK_END);
		fread(wordstrn,sizeof(WORDTR3),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s\n",i+1,(wordstrn+i)->question);
		}
		//==========================================
		printf("\n請輸入欲修改之題目編號：");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2);
		if(input2>0 && input2<=num1){
			printf("\n第%d筆資料，題目:%s\n",input2,(wordstrn+(input2-1))->question);
			printf("(A)%s\n",(wordstrn+(input2-1))->a1);
			printf("(B)%s\n",(wordstrn+(input2-1))->a2);
			printf("(C)%s\n",(wordstrn+(input2-1))->a3);
			printf("(D)%s\n",(wordstrn+(input2-1))->a4);
			printf("答案:(%c)\n",((wordstrn+(input2-1))->answer)+64);
			//============================================================
			if(wordpersoncheckyesno("是否修改題目?")==1){
				//printf("請輸入修改後之題目：");
				//fflush(stdin);
				//gets(wordstrnew[0].question);
				wordpersoncheckstring("請輸入修改後之題目：",wordstrnew[0].question);
				printf("比對中...");
				if(num1>0){
					for(i=0;i<num1;i++){
						if((i!=(input2-1)) && (strcmp(wordstrnew[0].question,(wordstrn+i)->question)==0)){
							printf("您所輸入的題目已存在!是否重試");
							goto BOOKeditword3retry;
						}
					}
				}
				printf("比對完成。\n");
			}
			else{
				sprintf(wordstrnew[0].question,"%s",(wordstrn+(input2-1))->question);
			}
			//==================
			if(wordpersoncheckyesno("是否修改選項(A)?")==1){
				//printf("請輸入修改後之選項(A):");
				//fflush(stdin);
				//gets(wordstrnew[0].a1);
				wordpersoncheckstring("請輸入修改後之選項(A):",wordstrnew[0].a1);
			}
			else{
				sprintf(wordstrnew[0].a1,"%s",(wordstrn+(input2-1))->a1);
			}
			//==================
			if(wordpersoncheckyesno("是否修改選項(B)?")==1){
				//printf("請輸入修改後之選項(B):");
				//fflush(stdin);
				//gets(wordstrnew[0].a2);
				wordpersoncheckstring("請輸入修改後之選項(B):",wordstrnew[0].a2);
			}
			else{
				sprintf(wordstrnew[0].a2,"%s",(wordstrn+(input2-1))->a2);
			}
			//==================
			if(wordpersoncheckyesno("是否修改選項(C)?")==1){
				//printf("請輸入修改後之選項(C):");
				//fflush(stdin);
				//gets(wordstrnew[0].a3);
				wordpersoncheckstring("請輸入修改後之選項(C):",wordstrnew[0].a3);
			}
			else{
				sprintf(wordstrnew[0].a3,"%s",(wordstrn+(input2-1))->a3);
			}
			//==================
			if(wordpersoncheckyesno("是否修改選項(D)?")==1){
				//printf("請輸入修改後之選項(D):");
				//fflush(stdin);
				//gets(wordstrnew[0].a4);
				wordpersoncheckstring("請輸入修改後之選項(D):",wordstrnew[0].a4);
			}
			else{
				sprintf(wordstrnew[0].a4,"%s",(wordstrn+(input2-1))->a4);
			}
			//=========================================
			if(wordpersoncheckyesno("是否修改答案?")==1){
				wordstrnew[0].answer=wordpersoncheckabcd("請輸入修改後答案:");
			}
			else{
				wordstrnew[0].answer=(wordstrn+(input2-1))->answer;
			}
			//====================================
			printf("修改資料...\n");
			fseek(fptr,-(num1-(input2-1))*sizeof(WORDTR3),SEEK_END);
			fwrite(wordstrnew,sizeof(WORDTR3),1,fptr);
			//====================================
			printf("修改資料完成!是否繼續");
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
		//==========================================若無找到資料 
		free(wordstrn);
		if(wordpersoncheckyesno("輸入編號錯誤!是否重試?")==1){
			goto BOOKeditword3;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("開啟檔案失敗!...");
		BOOKeditexit3:
		if(wordpersoncheckyesno("是否離開?")==1){
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
	printf("英文測驗系統題庫管理程式>>刪除選擇題\n");
	//=================
	BOOKdelstart3:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\3\\%s.etd3",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//==========================================
		BOOKdelword3:
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		if(num1<=0){
			printf("此題庫尚無資料!\n");
			goto BOOKdelexit3;
		}
		printf("\n此題庫檔案共%d筆題目:\n",num1);
		wordstrn=(WORDTR3 *) malloc(num1*sizeof(WORDTR3));
		fseek(fptr,-num1*sizeof(WORDTR3),SEEK_END);
		fread(wordstrn,sizeof(WORDTR3),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s\n",i+1,(wordstrn+i)->question);
		}
		//==========================================
		printf("請輸入欲刪除之題目編號：");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2); 
		if(input2>0 && input2<=num1){
			printf("\n第%d筆資料，題目:%s\n",input2,(wordstrn+(input2-1))->question);
			printf("(A)%s\n",(wordstrn+(input2-1))->a1);
			printf("(B)%s\n",(wordstrn+(input2-1))->a2);
			printf("(C)%s\n",(wordstrn+(input2-1))->a3);
			printf("(D)%s\n",(wordstrn+(input2-1))->a4);
			printf("答案:(%c)\n",((wordstrn+(input2-1))->answer)+64);
			if(wordpersoncheckyesno("是否確認刪除這筆資料?")==1){
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
				printf("\n刪除資料完成!\n");
			}
			//====================================
			free(wordstrn);
			if(wordpersoncheckyesno("是否繼續?")==1){
				fptr = fopen(filename2,"r+b");
				goto BOOKdelword3;
			}
			else{
				return;
			}
		}
		//==========================================若無找到資料 
		free(wordstrn);
		if(wordpersoncheckyesno("輸入編號錯誤!是否重試?")==1){
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
		printf("開啟檔案失敗!...");
		BOOKdelexit3:
		if(wordpersoncheckyesno("是否離開?")==1){
			return;
		}
		else{
			goto BOOKdelstart3;
		}
	}
}
