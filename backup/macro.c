/*
 * Write macro here
 * I want to use red-black-tree to do it
 * but there is a lot of bug in my program,so I want to use linked-list to do it
 * Let's go!!:-) 
*/ 

/*
 * LITTLE INTRODUCTION
 * IF YOU WANT TO YOU MACRO YOU MUST TO CALL RASM_MACRO_INIT() FIRST!!!!
 * YOU CAN CALL RASM_MACRO_CHECK TO CHECK IF THE STRING IS RIGHT! 
 * YOU CAN CALL RASM_MACRO_GET(RASM_STRING) TO GET THE INDEX IN LINKED-LIST AND THE NODE!
 * YOU CAN CALL RASM_MACRO_DEF(RASM_STRING) TO DEFINE MACRO!
 * IF YOU WANT TO UNDEFINE A MACRO ,YOU SHOULD CALL RASM_MACRO_UNDEF(RASM_STRING) TO DO IT!
*/
//#include"stdio.h"		//THIS LINE OF CODE FOR DEBUG:-)
#include"string.h"
#include"stdlib.h"

#define NULL ((void *)0)
#define RASM_TRUE 1
#define RASM_FALSE 0
typedef char RASM_BOOL;
typedef char* RASM_STRING;

typedef struct{
	RASM_STRING key;
	RASM_STRING val;
}RASM_KEY_VAL;

typedef struct RASM_LINKED_LIST_TYPE{
	RASM_KEY_VAL* data[64];
	short number;
	struct RASM_LINKED_LIST_TYPE* next;
}RASM_NODE;

typedef struct{
	short index;
	RASM_NODE* llist;
}RASM_NODE_INFO;

RASM_NODE* RASM_MACRO = NULL;

RASM_BOOL RASM_MACRO_INIT(void);
RASM_BOOL RASM_MACRO_CHECK(RASM_STRING);
RASM_NODE_INFO* RASM_MACRO_GET(RASM_STRING);
RASM_BOOL RASM_MACRO_DEF(RASM_STRING,RASM_STRING);
RASM_BOOL RASM_MACRO_UNDEF(RASM_STRING);

RASM_BOOL RASM_MACRO_INIT(void)
{
	RASM_MACRO = (RASM_NODE*)malloc(sizeof(RASM_NODE));
	if(RASM_MACRO==NULL)	return RASM_FALSE;
	RASM_MACRO->next = NULL;
	RASM_MACRO->number = 0;
	return RASM_TRUE;
}

RASM_BOOL RASM_MACRO_CHECK(RASM_STRING s)
{
	if(!(('a'<=s[0]&&s[0]<='z')||('A'<=s[0]&&s[0]<='Z')||(s[0]=='_')))	return RASM_FALSE;
	int i;
	for(i=1;s[i]!='\0';i++){
		if(('0'<=s[i]&&s[i]<='9')||('a'<=s[i]&&s[i]<='z')||('A'<=s[i]&&s[i]<='Z')||(s[i]=='_'))	continue;
		else																					return RASM_FALSE;
	}
	return RASM_TRUE;
} 

RASM_NODE_INFO* RASM_MACRO_GET(RASM_STRING s)
{
	if(!RASM_MACRO_CHECK(s))	return NULL;
	RASM_NODE* p = RASM_MACRO;
	short start = 0,end = 64-1;
	while(p!=NULL){
		//binary search
		start = 0;
		end = p->number-1;
		while(start<=end&&end<=(p->number-1)){
			int mid = start + (end-start)/2;
			if(strcmp(p->data[mid]->key,s)==0){
				RASM_NODE_INFO* rni = (RASM_NODE_INFO*)malloc(sizeof(RASM_NODE_INFO));
				if(rni==NULL)	return NULL;
				rni->index = mid;
				rni->llist = p;
				return rni;
			}else if (strcmp(s,p->data[mid]->key)<0) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
		}
		p = p->next;
	}
	return NULL;
}

RASM_BOOL RASM_MACRO_DEF(RASM_STRING key,RASM_STRING val)
{
	if(!RASM_MACRO_CHECK(key))	return RASM_FALSE;
	RASM_NODE* p = RASM_MACRO;
	while(p->number==64&&p->next!=NULL)	p = p->next;
	if(p->next==NULL){
		p->next = (RASM_NODE*)malloc(sizeof(RASM_NODE));
		if(p->next==NULL)		return RASM_FALSE;
		p = p->next;
		p->number = 1;
		RASM_KEY_VAL* rkv = (RASM_KEY_VAL*)malloc(sizeof(RASM_KEY_VAL));
		if(rkv==NULL)			return RASM_FALSE;
		rkv->key = (RASM_STRING)malloc(strlen(key));
		strcpy(rkv->key,key);
		rkv->val = (RASM_STRING)malloc(strlen(val));
		strcpy(rkv->val,val);
		p->data[0] = rkv;
		return RASM_TRUE;
	}else{
		p->number++;
		RASM_KEY_VAL* rkv = (RASM_KEY_VAL*)malloc(sizeof(RASM_KEY_VAL));
		if(rkv==NULL)			return RASM_FALSE;
		rkv->key = (RASM_STRING)malloc(strlen(key));
		strcpy(rkv->key,key);
		rkv->val = (RASM_STRING)malloc(strlen(val));
		strcpy(rkv->val,val);
		p->data[p->number-1] = rkv;
		int i = p->number-1;
		while(i!=0&&strcmp(p->data[i-1]->key,p->data[i]->key)>0){
			RASM_KEY_VAL* tmp = p->data[i-1];
			p->data[i-1] = p->data[i];
			p->data[i] = tmp;
			i--;
		}
		return RASM_TRUE;
	}
	return RASM_FALSE;	//I don't know why I need to return it :-(
}

RASM_BOOL RASM_MACRO_UNDEF(RASM_STRING s)
{
	
	//SOMETHING BUG IN IT!!
	RASM_NODE_INFO* rni = RASM_MACRO_GET(s);
	if(rni==NULL)	return RASM_FALSE;
	RASM_NODE* rn = rni->llist;
	free(rn->data[rni->index]);
	rn->number--;
	int i=rni->llist->number;
	while(i!=0&&rni->index<=i){
		RASM_KEY_VAL* tmp = rn->data[i-1];
		rn->data[i-1] = rn->data[i];
		rn->data[i] = tmp;
		i--;
	}
}

/*main()
{
	int i,j,n,m;
	scanf("%d%d",&n,&m);
	
	RASM_MACRO_INIT();
	
	RASM_STRING s1 = (RASM_STRING)malloc(50);
	RASM_STRING s2 = (RASM_STRING)malloc(50);
	
	for(i=1;i<=n;i++){
		scanf("%s",s1);
		scanf("%s",s2);
		RASM_MACRO_DEF(s1,s2);
	}
	
	for(j=1;j<=m;j++){
		scanf("%s",s1);
		RASM_NODE_INFO* rni = RASM_MACRO_GET(s1);
		RASM_NODE* llist = rni->llist;
		puts(llist->data[rni->index]->val);
	}
}*/
