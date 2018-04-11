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
	printf("英文測驗系統題庫管理程式>>新增填充題\n");
	//=================
	BOOKcreatestart:
	printf("\n請輸入題庫檔案名稱：（若不存在則會自動建立）\n>");
	fflush(stdin);
	scanf("%s",filename1);
	sprintf(filename2,"..\\Database\\2\\%s.etd2",filename1);
	//printf("%s\n",filename2);
	if((fptr = fopen(filename2,"r+b"))!=NULL){
		printf("開啟檔案成功\!\n");
		//fscanf(fptr,"[%d]",&num1);
		wordnum[0].datanum=0;
		fread(wordnum,sizeof(WORDDATANUM),1,fptr);
		num1=wordnum[0].datanum;
		BOOKnewword2:
		printf("\n此題庫檔案共%d筆題目:\n",num1);
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
		//printf("\n請輸入新英文句子(完整)：");
		wordpersoncheckstring("\n請輸入新英文句子(完整)：",wordstr[0].mainstr);
		//fflush(stdin);
		//gets(wordstr[0].mainstr);
		//printf("請輸入答案:");
		wordpersoncheckstring("請輸入答案:",wordstr[0].ans);
		//fflush(stdin);
		//gets(wordstr[0].ans);
		//==========================================
		printf("比對中...\n");
		if(word2strcheck(wordstr[0].mainstr,wordstr[0].ans) == 1){
			if(num1>0){
				for(i=0;i<num1;i++){
					if(strcmp(wordstr[0].mainstr,(wordstrn+i)->mainstr)==0){
						printf("您所輸入的句子已存在!是否重試");
						goto BOOKnewword2retry;
					}
				}
			}
		}
		else{
			printf("無法在句子中找到與答案相符合之單字...是否重試");
			goto BOOKnewword2retry;
		}
		//=========================================
		printf("比對完成，新增資料...\n");
		rewind(fptr);
		//fprintf(fptr,"[%d]",++num1);
		wordnum[0].datanum=++num1;
		fwrite(wordnum,sizeof(WORDDATANUM),1,fptr);
		fseek(fptr,0,SEEK_END);
		fwrite(wordstr,sizeof(WORDTR2),1,fptr);
		//==========================================
		printf("新增資料完成!是否繼續");
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
		printf("系統中無此檔案，已新增。\n");
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
	printf("英文測驗系統題庫管理程式>>修改填充題\n");
	//=================
	BOOKeditstart2:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\2\\%s.etd2",filename1);
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
			goto BOOKeditexit2;
		}
		BOOKeditword2:
		printf("\n此題庫檔案共%d筆題目:\n",num1);
		wordstrn=(WORDTR2 *) malloc(num1*sizeof(WORDTR2));
		fseek(fptr,-num1*sizeof(WORDTR2),SEEK_END);
		fread(wordstrn,sizeof(WORDTR2),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s, Ans:%s\n",i+1,(wordstrn+i)->mainstr,(wordstrn+i)->ans);
		}
		//==========================================
		printf("\n請輸入欲修改之英文句子編號：");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2);
		if(input2>0 && input2<=num1){
			printf("\n第%d筆資料，句子：%s,答案：%s\n",input2,(wordstrn+(input2-1))->mainstr,(wordstrn+(input2-1))->ans);
			//printf("請輸入修改後之英文句子：");
			//fflush(stdin);
			//gets(wordstrnew[0].mainstr);
			wordpersoncheckstring("請輸入修改後之英文句子：",wordstrnew[0].mainstr);
			//printf("請輸入修改後之答案：");
			//fflush(stdin);
			//gets(wordstrnew[0].ans);
			wordpersoncheckstring("請輸入修改後之答案：",wordstrnew[0].ans);
			//====================================
			printf("比對中...\n");
			if(word2strcheck(wordstrnew[0].mainstr,wordstrnew[0].ans) == 1){
				if(num1>0){
					for(j=0;j<num1;j++){
						if(((input2-1)!=j) && (strcmp(wordstrnew[0].mainstr,(wordstrn+j)->mainstr)==0)){
							printf("您所輸入的句子已存在!是否重試");
							goto BOOKeditword2retry;
						}
					}
				}
			}
			else{
				printf("無法在句子中找到與答案相符合之單字...是否重試");
				goto BOOKeditword2retry;
			}
			//====================================
			printf("比對完成，修改資料...\n");
			fseek(fptr,-(num1-(input2-1))*sizeof(WORDTR2),SEEK_END);
			fwrite(wordstrnew,sizeof(WORDTR2),1,fptr);
			printf("修改資料完成!是否繼續");
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
		//==========================================若無找到資料 
		free(wordstrn);
		if(wordpersoncheckyesno("輸入編號錯誤!是否重試?")==1){
			goto BOOKeditword2;
		}
		else{
			fclose(fptr);
			return;
		}
		//==========================================	
	}
	else{
		printf("開啟檔案失敗!...");
		BOOKeditexit2:
		if(wordpersoncheckyesno("是否離開?")==1){
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
	printf("英文測驗系統題庫管理程式>>刪除填充題\n");
	//=================
	BOOKdelstart:
	printf("\n請輸入題庫檔案名稱：\n>");
	fflush(stdin);
	scanf("%s",filename1);
	//printf("%s\n",filename1);
	sprintf(filename2,"..\\Database\\2\\%s.etd2",filename1);
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
		printf("\n此題庫檔案共%d筆題目:\n",num1);
		wordstr=(WORDTR2*) malloc(num1*sizeof(WORDTR2));
		fread(wordstr,sizeof(WORDTR2),num1,fptr);
		for(i=0;i<num1;i++){
			printf("%d.%s, Ans:%s\n",i+1,(wordstr+i)->mainstr,(wordstr+i)->ans);
		}
		//==========================================
		printf("請輸入欲刪除之英文句子編號：");
		fflush(stdin);
		//gets(input2);
		scanf("%d",&input2); 
		if(input2>0 && input2<=num1){
			printf("\n第%d筆資料，句子：%s,答案：%s\n",input2,(wordstr+(input2-1))->mainstr,(wordstr+(input2-1))->ans);
			if(wordpersoncheckyesno("是否確認刪除這筆資料?")==1){
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
				printf("\n刪除資料完成!\n");
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
		//==========================================若無找到資料 
		free(wordstr);
		if(wordpersoncheckyesno("輸入編號錯誤!是否重試?")==1){
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
