struct persondatamainstruct{
	int usernum;
};

typedef struct persondatamainstruct PERSONDATAMAIN;
//===========================
struct persondatauserstruct{
	char username[100];
	char password[100];
	int usermode;
};
typedef struct persondatauserstruct PERSONDATAUSER;

//===========================
