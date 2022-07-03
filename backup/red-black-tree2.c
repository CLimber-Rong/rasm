/*
 * Write red-black-tree here
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
typedef char* RASM_STRING;
typedef char  RASM_BOOL;
#define RASM_TRUE  1
#define RASM_FALSE 0
#define NULL ((void *)0)
struct RASM_RBT{
	RASM_STRING key;
	RASM_BOOL is_save;
	struct RASM_RBT* next[1+10+26+26];
	/*
	 0:_
	 1...10:0...9
	 11...37:A...Z
	 37...53:a...z
	*/
};
struct RASM_RBT RASM_MACRO[1+26+26];	//no number
char RASM_RBT_VAL(char c)
{
	//Let char =>RBT.next[]
	if(c=='_')				return 0;
	if('0'<=c&&c<='9')		return 1+c-'0';
	if('A'<=c&&c<='Z')		return 1+26+c-'A';
	if('a'<=c&&c<='z')		return 1+26+26+c-'a';
	else					return -1;
}

RASM_STRING RASM_RBT_GET(RASM_STRING s)
{
	if(1<=RASM_RBT_VAL(s[0])&&RASM_RBT_VAL(s[0])<=10)	return NULL;
	//check s[0] is number or others
	int i;
	for(i=1;s[i]!='\0';i++){
		if(RASM_RBT_VAL(s[i])==-1)	return NULL;
		printf("%d\n",RASM_RBT_VAL(s[i]));
	}
	i = 1;
	struct RASM_RBT* rbt = &RASM_MACRO[RASM_RBT_VAL(s[0])];
	while(s[i]!='\0'){
		printf("Now-ADDR %p\n",rbt->next[RASM_RBT_VAL(s[i])]);
		if(rbt->next[RASM_RBT_VAL(s[i])]==NULL)	return NULL;
		rbt = rbt->next[RASM_RBT_VAL(s[i])];
		i++;
	}
	printf("*");
	if(rbt->is_save==RASM_FALSE)	return NULL;
	else						return rbt->key; 
}
RASM_BOOL RASM_RBT_CREATE(RASM_STRING s)
{
	if(1<=RASM_RBT_VAL(s[0])&&RASM_RBT_VAL(s[0])<=10)	return RASM_FALSE;
	//check s[0] is number or others
	int i;
	for(i=1;s[i]!='\0';i++){
		if(RASM_RBT_VAL(s[i])==-1)	return RASM_FALSE;
		printf("%d\n",RASM_RBT_VAL(s[i]));
	}
	i = 1;
	struct RASM_RBT* rbt = &RASM_MACRO[RASM_RBT_VAL(s[0])];
	while(s[i]!='\0'){
		if(rbt->next[RASM_RBT_VAL(s[i])]==NULL){
			struct RASM_RBT newNode;
			newNode.is_save = RASM_FALSE;
			newNode.key = NULL;
			memset(newNode.next,0,sizeof(newNode.next));
			rbt->next[RASM_RBT_VAL(s[i])] = &newNode;
		}
		printf("ADDR %p\n",rbt->next[RASM_RBT_VAL(s[i])]);
		rbt = rbt->next[RASM_RBT_VAL(s[i])];
		i++;
	}
	rbt->is_save = RASM_TRUE;
	rbt->key = s;
	return RASM_TRUE;
}

main()
{
	printf("%d\n",RASM_RBT_CREATE("HelloWorld"));
	printf("%p\n",RASM_MACRO[57].next[64]);
	printf("%d",RASM_RBT_GET("HelloWorld"));
	return 0;
}
