#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//====================================
int wordpersoncheckyesno(char *);
int wordpersoncheckabcd(char *);
void wordpersoncheckstring(char *,char *);
//====================================
struct wordt4b{
	char filename[255];
	int questionnum;
};
struct wordt4a{
	char question[200];
	char a1[50];
	char a2[50];
	char a3[50];
	char a4[50];
	int answer;
};
typedef struct wordt4a WORDTR4;
typedef struct wordt4b WORDTR4MAIN;

void word4create(void){
	char filename1[255],filename2[999],filename3[999],filename4[255],answern;
	char input,txtinout;
	FILE *fptr, *fptr2;
	int i,j,num1=0,k=0;
	WORDTR4 wordstr[1],*wordstrn;
	WORDTR4MAIN wordmain[1];
	//=================
	system("cls");
	printf("英文測驗系統題庫管理程式>>新增閱\讀題\n");
	//=================
	BOOKcreatestart:
	printf("\n請輸入題庫檔案名稱：（若不存在則會自動建立）\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\4\\%s.etd4",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordmain[0].questionnum=0;
		fread(wordmain,sizeof(WORDTR4MAIN),1,fptr);
		num1=wordmain[0].questionnum;
		BOOKnewword4:
		if(num1>0){
			printf("\n此題庫檔案共%d筆題目。\n",num1);
			wordstrn=(WORDTR4 *) malloc(num1*sizeof(WORDTR4));
			fseek(fptr,-num1*sizeof(WORDTR4),SEEK_END);
			fread(wordstrn,sizeof(WORDTR4),num1,fptr);
			for(i=0;i<num1;i++){
				printf("%d.%s\n",i+1,(wordstrn+i)->question);
			}
			k=1;
		}
		else{
			while(1){
				printf("\n請輸入該閱\讀文章之文件名稱(*.txt)：");
				fflush(stdin);
				gets(filename4);
				printf("\n開啟中...");
				sprintf(filename3,"..\\Database\\4\\%s",filename4);
				if((fptr2 = fopen(filename3,"r"))!=NULL){
					printf("開啟成功\!\n文章預覽：\n");
					while(!feof(fptr2)){
						txtinout=fgetc(fptr2);
						printf("%c",txtinout);
					}
					if(wordpersoncheckyesno("\n是否要使用本文件?")==1){
						sprintf(wordmain[0].filename,"%s",filename4);
						fclose(fptr2);
						break;
					}
					else{
						printf("文件選取已取消...\n");
					}
				}
			}
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
					goto BOOKnewword4retry;
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
		wordmain[0].questionnum=++num1;
		fwrite(wordmain,sizeof(WORDTR4MAIN),1,fptr);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR4),1,fptr);
		//==========================================
		printf("新增資料完成!");
		BOOKnewword4retry:
		if(k==1){
			free(wordstrn);
			k=0;
		}
		if(wordpersoncheckyesno("是否繼續?")==1){
			goto BOOKnewword4;
		}
		else{
			fclose(fptr);
			return;
		}
	}
	else{
		fptr = fopen(filename2,"w+b");
		printf("系統中無此檔案，已新增。\n");
		goto BOOKnewword4;
	}
}
void word4edit(void){
	char filename1[255],filename2[999],filename3[999],filename4[255];
	char input,answern,txtinout;
	FILE *fptr, *fptr2;
	int i,j,num1=0,input2;
	WORDTR4 wordstrnew[1],*wordstrn;
	WORDTR4MAIN wordmain[1];
	//=================
	system("cls");
	printf("英文測驗系統題庫管理程式>>修改閱\讀題\n");
	//=================
	BOOKeditstart4:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\4\\%s.etd4",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//==========================================
		wordmain[0].questionnum=0;
		fread(wordmain,sizeof(WORDTR4MAIN),1,fptr);
		num1=wordmain[0].questionnum;
		if(num1<=0){
			printf("此題庫尚無資料!\n");
			goto BOOKeditexit4;
		}
		//=========================================
		printf("文章預覽：\n");
		sprintf(filename3,"..\\Database\\4\\%s",wordmain[0].filename);
		if((fptr2 = fopen(filename3,"r"))!=NULL){
			while(!feof(fptr2)){
				txtinout=fgetc(fptr2);
				printf("%c",txtinout);
			}
			printf("\n\n");
			fclose(fptr2);
		}
		else{
			printf("開啟文章失敗!請確認該文章檔案是否存在。\n");
			goto BOOKeditexit4;
		}
		if(wordpersoncheckyesno("\n是否修改閱\讀文章?")==1){
			while(1){
				printf("\n請輸入該閱\讀文章之文件名稱(*.txt)：");
				fflush(stdin);
				gets(filename4);
				printf("\n開啟中...");
				sprintf(filename3,"..\\Database\\4\\%s",filename4);
				if((fptr2 = fopen(filename3,"r"))!=NULL){
					printf("開啟成功\!\n文章預覽：\n");
					while(!feof(fptr2)){
						txtinout=fgetc(fptr2);
						printf("%c",txtinout);
					}
					if(wordpersoncheckyesno("\n是否要使用本文件?")==1){
						sprintf(wordmain[0].filename,"%s",filename4);
						fclose(fptr2);
						//===========================================
						rewind(fptr);
						fwrite(wordmain,sizeof(WORDTR4MAIN),1,fptr);
						printf("文章修改完成!是否繼續");
						goto BOOKeditword4retry2;
					}
					else{
						printf("文件選取已取消...\n");
					}
				}
			}
		}
		//==========================================
		BOOKeditword4:
		printf("\n此題庫檔案共%d筆題目:\n",num1);
		wordstrn=(WORDTR4 *) malloc(num1*sizeof(WORDTR4));
		fseek(fptr,-num1*sizeof(WORDTR4),SEEK_END);
		fread(wordstrn,sizeof(WORDTR4),num1,fptr);
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
							goto BOOKeditword4retry;
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
			rewind(fptr);
			fwrite(wordmain,sizeof(WORDTR4MAIN),1,fptr);
			fseek(fptr,-(num1-(input2-1))*sizeof(WORDTR4),SEEK_END);
			fwrite(wordstrnew,sizeof(WORDTR4),1,fptr);
			//====================================
			printf("修改資料完成!是否繼續");
			BOOKeditword4retry:
			free(wordstrn);
			BOOKeditword4retry2:
			if(wordpersoncheckyesno("?")==1){
				goto BOOKeditword4;
			}
			else{
				fclose(fptr);
				return;
			}
		}
		//==========================================若無找到資料 
		free(wordstrn);
		if(wordpersoncheckyesno("輸入編號錯誤!是否重試?")==1){
			goto BOOKeditword4;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("開啟檔案失敗!...");
		BOOKeditexit4:
		if(wordpersoncheckyesno("是否離開?")==1){
			return;
		}
		else{
			goto BOOKeditstart4;
		}
	}
}

void word4del(void){
	char filename1[255],filename2[999],filename3[999];
	char input,txtinout;
	FILE *fptr, *fptr2;
	int i,j,num1=0,input2;
	WORDTR4 *wordstrn;
	WORDTR4MAIN wordmain[1];
	//=================
	system("cls");
	printf("英文測驗系統題庫管理程式>>刪除閱\讀題\n");
	//=================
	BOOKdelstart4:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\4\\%s.etd4",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//==========================================
		wordmain[0].questionnum=0;
		fread(wordmain,sizeof(WORDTR4MAIN),1,fptr);
		num1=wordmain[0].questionnum;
		BOOKdelword4:
		if(num1<=0){
			printf("此題庫尚無資料!\n");
			goto BOOKdelexit4;
		}
		printf("\n此題庫檔案共%d筆題目:\n",num1);
		wordstrn=(WORDTR4 *) malloc(num1*sizeof(WORDTR4));
		fseek(fptr,-num1*sizeof(WORDTR4),SEEK_END);
		fread(wordstrn,sizeof(WORDTR4),num1,fptr);
		//==========================================
		sprintf(filename3,"..\\Database\\4\\%s",wordmain[0].filename);
		if((fptr2 = fopen(filename3,"r"))!=NULL){
			while(!feof(fptr2)){
				txtinout=fgetc(fptr2);
				printf("%c",txtinout);
			}
			printf("\n\n");
			fclose(fptr2);
		}
		else{
			printf("開啟文章失敗!請確認該文章檔案是否存在。\n");
			goto BOOKdelexit4;
		}
		for(i=0;i<num1;i++){
			printf("%d.%s\n",i+1,(wordstrn+i)->question);
		}
		//==========================================
		printf("\n**本功\能僅供刪除閱\讀題組之選擇題部分**\n");
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
				wordmain[0].questionnum=--num1;
				fwrite(wordmain,sizeof(WORDTR4MAIN),1,fptr);
				for(j=0;j<num1+1;j++){
					if((input2-1)!=j){
						fwrite((wordstrn+j),sizeof(WORDTR4),1,fptr);
					}
				}
				fclose(fptr);
				printf("\n刪除資料完成!\n");
			}
			//====================================
			free(wordstrn);
			if(wordpersoncheckyesno("是否繼續?")==1){
				fptr = fopen(filename2,"r+b");
				goto BOOKdelword4;
			}
			else{
				return;
			}
		}
		//==========================================若無找到資料 
		free(wordstrn);
		if(wordpersoncheckyesno("輸入編號錯誤!是否重試?")==1){
			rewind(fptr);
			goto BOOKdelword4;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("開啟檔案失敗!...");
		BOOKdelexit4:
		if(wordpersoncheckyesno("是否離開?")==1){
			return;
		}
		else{
			goto BOOKdelstart4;
		}
	}
}
