#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include ".\\ETSprogramin.h"
//====================================
char *getfilestr(char*);
int adddata(int ,char *,char *);
//====================================
WORDTRNODE *Word1NodeFirst=NULL; //資料庫-鍵結串列(單字) 
WORDTR2NODE *Word2NodeFirst=NULL; //資料庫-鏈結串列(填充)  
WORDTR3NODE *Word3NodeFirst=NULL; //資料庫-鏈結串列(選擇)  
WORDTR4NORMAL *Word4NormalNodeFirst=NULL; //資料庫-鍵結串列(閱讀-標頭綜合) 
WORDTR4NODE *Word4NodeFirst=NULL; //資料庫-鍵結串列(閱讀-選擇) 
int Word1totnum=0,Word2totnum=0,Word3totnum=0,Word4totnum=0,Word4choosetotnum=0; //資料庫-各題型總題數紀錄  
//====================================

int searchfile(int mode){
	DIR * dir;
    DIR * dir2;
    struct dirent * ptr;
    int i,j,k;
    char pathname[999];
    char filenamestr[30];
    char filenamestr2[5];
    //==========================================
    switch(mode){
    	case 1:
    		j=1;
    		k=4;
    		break;
    	default:
    		j=mode-1;
    		k=mode-1;
	}
    //==========================================
    for(i=j;i<=k;i++){
    	sprintf(pathname,"..\\Database\\%d",i);
    	dir =opendir(pathname);
	    while((ptr = readdir(dir))!=NULL) {
	        sprintf(pathname,"..\\Database\\%d\\%s",i,ptr->d_name);
	        if((dir2 = opendir(pathname))==NULL) {  //開啟時不為資料夾之形式 
	            //printf("%s: file(%s)\n", ptr->d_name,getfilestr(pathname));
	            sprintf(filenamestr,"%s",getfilestr(pathname));
	            sprintf(filenamestr2,"etd%d",i);
	            if(strcmp(filenamestr,filenamestr2)==0){
	            	if(adddata(i,pathname,ptr->d_name)==1){
	            		return 1;
					}
				}
	        } else {
	            closedir(dir2);
	        }
	    }
	    closedir(dir);
	}
	return 0;
}

char *getfilestr(char *pathname){
	int i,j,num;
	num=strlen(pathname);
	for(i=num-1;i>=0;i--){
		if(pathname[i]=='.'){
			return &pathname[i+1];
		}
	}
}

int adddata(int num,char *pathname,char *filenamestr){
	FILE *fptr;
	int num1,k,i;
	extern int Word1totnum,Word2totnum,Word3totnum,Word4totnum,Word4choosetotnum;
	//===============================
	WORDTR *Word1File;
	WORDTR2 *Word2File;
	WORDTR3 *Word3File;
	WORDTR4MAIN *Word4mainFile;
	WORDTR4 *Word4File;
	WORDDATANUM wordnum[1];
	//===============
	extern WORDTRNODE *Word1NodeFirst;
	extern WORDTR2NODE *Word2NodeFirst;
	extern WORDTR3NODE *Word3NodeFirst;
	extern WORDTR4NORMAL *Word4NormalNodeFirst;
	WORDTRNODE *Word1NodePre,*Word1NodeNow;
	WORDTR2NODE *Word2NodePre,*Word2NodeNow;
	WORDTR3NODE *Word3NodePre,*Word3NodeNow;
	WORDTR4NORMAL *Word4NormalNodePre,*Word4NormalNodeNow;
	//================================
	switch(num){
		case 1:
			if((fptr = fopen(pathname,"rb"))!=NULL){
				//fscanf(fptr,"[%d]",&num1);
				wordnum[0].datanum=0;
				fread(wordnum,sizeof(WORDDATANUM),1,fptr);
				num1=wordnum[0].datanum;
				Word1File=(WORDTR *) malloc(num1*sizeof(WORDTR));
				fread((Word1File),sizeof(WORDTR),num1,fptr);
				Word1totnum+=num1;
				//======================================
				Word1NodeNow=Word1NodeFirst;
				while(Word1NodeNow!=NULL){
					Word1NodePre=Word1NodeNow;
					Word1NodeNow=Word1NodeNow->next;
				}
				for(k=0;k<num1;k++){
					Word1NodeNow=(WORDTRNODE *) malloc(sizeof(WORDTRNODE));
					sprintf(Word1NodeNow->eng,"%s",(Word1File+k)->eng);
					sprintf(Word1NodeNow->chi,"%s",(Word1File+k)->chi);
					sprintf(Word1NodeNow->databasename,"%s",filenamestr);
					Word1NodeNow->datanum=k+1;
					Word1NodeNow->next=NULL;
					if(Word1NodeFirst==NULL){
						Word1NodeFirst=Word1NodeNow;
					}
					else{
						Word1NodePre->next=Word1NodeNow;
					}
					Word1NodePre=Word1NodeNow;
				}
				/*=============================
				Word1NodeNow=Word1NodeFirst;
				while(Word1NodeNow!=NULL){
					printf("En:%s,Ch:%s\n",Word1NodeNow->eng,Word1NodeNow->chi);
					Word1NodePre=Word1NodeNow;
					Word1NodeNow=Word1NodeNow->next;
				}
				//======================================*/ 
				fclose(fptr);
				free(Word1File);
			}
			else{
				printf("開啟檔案失敗!請檢查您的資料庫檔案...\n");
				return 1;
			}
			break;
		case 2:
			if((fptr = fopen(pathname,"rb"))!=NULL){
				//fscanf(fptr,"[%d]",&num1);
				wordnum[0].datanum=0;
				fread(wordnum,sizeof(WORDDATANUM),1,fptr);
				num1=wordnum[0].datanum;
				Word2File=(WORDTR2 *) malloc(num1*sizeof(WORDTR2));
				fread((Word2File),sizeof(WORDTR2),num1,fptr);
				Word2totnum+=num1;
				//======================================
				Word2NodeNow=Word2NodeFirst;
				while(Word2NodeNow!=NULL){
					Word2NodePre=Word2NodeNow;
					Word2NodeNow=Word2NodeNow->next;
				}
				for(k=0;k<num1;k++){
					Word2NodeNow=(WORDTR2NODE *) malloc(sizeof(WORDTR2NODE));
					sprintf(Word2NodeNow->mainstr,"%s",(Word2File+k)->mainstr);
					sprintf(Word2NodeNow->ans,"%s",(Word2File+k)->ans);
					sprintf(Word2NodeNow->databasename,"%s",filenamestr);
					Word2NodeNow->datanum=k+1;
					Word2NodeNow->next=NULL;
					if(Word2NodeFirst==NULL){
						Word2NodeFirst=Word2NodeNow;
					}
					else{
						Word2NodePre->next=Word2NodeNow;
					}
					Word2NodePre=Word2NodeNow;
				}
				/*=============================
				Word2NodeNow=Word2NodeFirst;
				while(Word2NodeNow!=NULL){
					printf("句子:%s,答案:%s\n",Word2NodeNow->mainstr,Word2NodeNow->ans);
					Word2NodePre=Word2NodeNow;
					Word2NodeNow=Word2NodeNow->next;
				}
				//======================================*/ 
				fclose(fptr);
				free(Word2File);
			}
			else{
				printf("開啟檔案失敗!請檢查您的資料庫檔案...\n");
				return 1;
			}
			break;
		case 3:
			if((fptr = fopen(pathname,"rb"))!=NULL){
				//fscanf(fptr,"[%d]",&num1);
				wordnum[0].datanum=0;
				fread(wordnum,sizeof(WORDDATANUM),1,fptr);
				num1=wordnum[0].datanum;
				Word3File=(WORDTR3 *) malloc(num1*sizeof(WORDTR3));
				fread((Word3File),sizeof(WORDTR3),num1,fptr);
				Word3totnum+=num1;
				//======================================
				Word3NodeNow=Word3NodeFirst;
				while(Word3NodeNow!=NULL){
					Word3NodePre=Word3NodeNow;
					Word3NodeNow=Word3NodeNow->next;
				}
				for(k=0;k<num1;k++){
					Word3NodeNow=(WORDTR3NODE *) malloc(sizeof(WORDTR3NODE));
					sprintf(Word3NodeNow->question,"%s",(Word3File+k)->question);
					sprintf(Word3NodeNow->a1,"%s",(Word3File+k)->a1);
					sprintf(Word3NodeNow->a2,"%s",(Word3File+k)->a2);
					sprintf(Word3NodeNow->a3,"%s",(Word3File+k)->a3);
					sprintf(Word3NodeNow->a4,"%s",(Word3File+k)->a4);
					Word3NodeNow->answer=(Word3File+k)->answer;
					sprintf(Word3NodeNow->databasename,"%s",filenamestr);
					Word3NodeNow->datanum=k+1;
					Word3NodeNow->next=NULL;
					if(Word3NodeFirst==NULL){
						Word3NodeFirst=Word3NodeNow;
					}
					else{
						Word3NodePre->next=Word3NodeNow;
					}
					Word3NodePre=Word3NodeNow;
				}
				/*=============================
				Word3NodeNow=Word3NodeFirst;
				k=1;
				while(Word3NodeNow!=NULL){
					printf("%d:%s\n",k++,Word3NodeNow->question);
					printf("(A)%s\n",Word3NodeNow->a1);
					printf("(B)%s\n",Word3NodeNow->a2);
					printf("(C)%s\n",Word3NodeNow->a3);
					printf("(D)%s\n",Word3NodeNow->a4);
					printf("答案:(%c)\n\n",(Word3NodeNow->answer)+64);
					Word3NodePre=Word3NodeNow;
					Word3NodeNow=Word3NodeNow->next;
				}
				//======================================*/ 
				fclose(fptr);
				free(Word3File);
			}
			else{
				printf("開啟檔案失敗!請檢查您的資料庫檔案...\n");
				return 1;
			}
			break;
		case 4:
			if((fptr = fopen(pathname,"rb"))!=NULL){
				Word4mainFile=(WORDTR4MAIN *) malloc(sizeof(WORDTR4MAIN));
				Word4mainFile->questionnum=0;
				fread(Word4mainFile,sizeof(WORDTR4MAIN),1,fptr);
				num1=Word4mainFile->questionnum;
				//Word4File=(WORDTR4 *) malloc(num1*sizeof(WORDTR4));
				//fread((Word4File),sizeof(WORDTR4),num1,fptr);
				Word4totnum+=1;
				Word4choosetotnum+=num1;
				//======================================
				Word4NormalNodeNow=Word4NormalNodeFirst;
				while(Word4NormalNodeNow!=NULL){
					Word4NormalNodePre=Word4NormalNodeNow;
					Word4NormalNodeNow=Word4NormalNodeNow->next;
				}
				//============================
				Word4NormalNodeNow=(WORDTR4NORMAL *) malloc(sizeof(WORDTR4NORMAL));
				sprintf(Word4NormalNodeNow->filename,"%s",Word4mainFile->filename);
				Word4NormalNodeNow->questionnum=Word4mainFile->questionnum;
				sprintf(Word4NormalNodeNow->databasefilename,"%s",filenamestr);
				Word4NormalNodeNow->next=NULL;
				if(Word4NormalNodeFirst==NULL){
					Word4NormalNodeFirst=Word4NormalNodeNow;
				}
				else{
					Word4NormalNodePre->next=Word4NormalNodeNow;
				}
				Word4NormalNodePre=Word4NormalNodeNow;
				/*=============================
				Word4NormalNodeNow=Word4NormalNodeFirst;
				k=1;
				while(Word4NormalNodeNow!=NULL){
					printf("%d:%s>>>文本檔案(%s)\n",k++,Word4NormalNodeNow->databasefilename,Word4NormalNodeNow->filename);
					printf("共%d題\n",Word4NormalNodeNow->questionnum);
					Word4NormalNodePre=Word4NormalNodeNow;
					Word4NormalNodeNow=Word4NormalNodeNow->next;
				}
				//======================================*/ 
				fclose(fptr);
				//free(Word4File);
				free(Word4mainFile);
			}
			else{
				printf("開啟檔案失敗!請檢查您的資料庫檔案...\n");
				return 1;
			}
			break;
	}
	return 0;
}

void nodedatafree(void){
	extern WORDTRNODE *Word1NodeFirst;
	extern WORDTR2NODE *Word2NodeFirst;
	extern WORDTR3NODE *Word3NodeFirst;
	extern WORDTR4NORMAL *Word4NormalNodeFirst;
	WORDTRNODE *Word1NodePre,*Word1NodeNow;
	WORDTR2NODE *Word2NodePre,*Word2NodeNow;
	WORDTR3NODE *Word3NodePre,*Word3NodeNow;
	WORDTR4NORMAL *Word4NormalNodePre,*Word4NormalNodeNow;
	//=============================
	extern WORDTR4NODE *Word4NodeFirst;
	extern WORDTRNODEEX *Word1NodeExFirst;
	extern WORDTR2NODEEX *Word2NodeExFirst;
	extern WORDTR3NODEEX *Word3NodeExFirst;
	extern WORDTR4NORMALEX *Word4NormalNodeExFirst;
	WORDTR4NODE *Word4NodePre,*Word4NodeNow;
	WORDTRNODEEX *Word1NodeExPre,*Word1NodeExNow;
	WORDTR2NODEEX *Word2NodeExPre,*Word2NodeExNow;
	WORDTR3NODEEX *Word3NodeExPre,*Word3NodeExNow;
	WORDTR4NORMALEX *Word4NormalNodeExPre,*Word4NormalNodeExNow;
	//===============================
	while(Word1NodeFirst!=NULL){
		Word1NodeNow=Word1NodeFirst;
		Word1NodeFirst=Word1NodeNow->next;
		free(Word1NodeNow);
	}
	//==============
	while(Word2NodeFirst!=NULL){
		Word2NodeNow=Word2NodeFirst;
		Word2NodeFirst=Word2NodeNow->next;
		free(Word2NodeNow);
	}
	//==============
	while(Word3NodeFirst!=NULL){
		Word3NodeNow=Word3NodeFirst;
		Word3NodeFirst=Word3NodeNow->next;
		free(Word3NodeNow);
	}
	//==============
	while(Word4NormalNodeFirst!=NULL){
		Word4NormalNodeNow=Word4NormalNodeFirst;
		Word4NormalNodeFirst=Word4NormalNodeNow->next;
		free(Word4NormalNodeNow);
	}
	//=====================================================
	while(Word1NodeExFirst!=NULL){
		Word1NodeExNow=Word1NodeExFirst;
		Word1NodeExFirst=Word1NodeExNow->next;
		free(Word1NodeExNow);
	}
	//============== 
	while(Word2NodeExFirst!=NULL){
		Word2NodeExNow=Word2NodeExFirst;
		Word2NodeExFirst=Word2NodeExNow->next;
		free(Word2NodeExNow);
	}
	//============== 
	while(Word3NodeExFirst!=NULL){
		Word3NodeExNow=Word3NodeExFirst;
		Word3NodeExFirst=Word3NodeExNow->next;
		free(Word3NodeExNow);
	}
	//============== 
	while(Word4NodeFirst!=NULL){
		Word4NodeNow=Word4NodeFirst;
		Word4NodeFirst=Word4NodeNow->next;
		free(Word4NodeNow);
	}
	//=============
	while(Word4NormalNodeExFirst!=NULL){
		Word4NormalNodeExNow=Word4NormalNodeExFirst;
		Word4NormalNodeExFirst=Word4NormalNodeExNow->next;
		free(Word4NormalNodeExNow);
	}
}
