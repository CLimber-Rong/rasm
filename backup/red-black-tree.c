/*
 * Write red-black-tree here
*/
#include<stdio.h>
#include<stdlib.h>
typedef char* RASM_STRING;
typedef char  RASM_BOOL;
#define RASM_BOOL_TRUE 1
#define RASM_BOOL_FALSE 0
#define RASM_BOOL_ISBOOL(VALUE) VALUE!=0?1:0
struct RASM_RED_BLACK_TREE{
	RASM_BOOL val;							//isbool
	struct RASM_RED_BLACK_TREE* next[1+10+26+26];	//'_'+'0'...'9'+'A'...'Z'+'a'...'z' = 1+10+26+26
};

struct RASM_RED_BLACK_TREE RASM_CONST_VAR[1+26+26];	//No number

//char => tree.val
char RASM_CHAR2TREE_VAL(char c)
{
	if(c=='_')			return 0;
	if('0'<=c&&c<='9')	return 1+c-'0';
	if('A'<=c&&c<='Z')	return 1+10+c-'A';
	if('a'<=c&&c<='z')	return 1+10+26+c-'a';
	else				return -1;
}
//new node
struct RASM_RED_BLACK_TREE* RASM_NEW_RED_BLACK_TREE()
{
	return (struct RASM_RED_BLACK_TREE*)malloc(sizeof(struct RASM_RED_BLACK_TREE));
}
//find string in tree
RASM_BOOL RASM_TREE_FIND(RASM_STRING s)
{
	//check the string
	int headn = 0;
	while(s[headn]!='\0'){
		if(RASM_CHAR2TREE_VAL(s[headn])==-1)	return RASM_BOOL_FALSE;
		headn++;
	}
	headn = 0;
	struct RASM_RED_BLACK_TREE rbt = RASM_CONST_VAR[RASM_CHAR2TREE_VAL(s[headn])];
	for(headn=1;s[headn]!='\0';headn++){
		if(rbt.next[RASM_CHAR2TREE_VAL(s[headn])]!=NULL)	rbt = *rbt.next[RASM_CHAR2TREE_VAL(s[headn+1])];
		else												return RASM_BOOL_FALSE;
	}
	headn++;
	return rbt.val;
}
RASM_BOOL RASM_TREE_NEW(RASM_STRING s)
{
	int n = 0;
	struct RASM_RED_BLACK_TREE rbt;
	//check string
	while(s[n]!='\0'){
		if(RASM_CHAR2TREE_VAL(s[n])==-1)	return RASM_BOOL_FALSE;
		n++;
	}
	n = 0;
	rbt = RASM_CONST_VAR[RASM_CHAR2TREE_VAL(s[n])];
	n++;
	while(s[n]!='\0'){
		if(rbt.next[RASM_CHAR2TREE_VAL(s[n])]==NULL){
			struct RASM_RED_BLACK_TREE* tmp = (struct RASM_RED_BLACK_TREE*)malloc(sizeof(struct RASM_RED_CLACK_TREE));
			tmp.val = RASM_BOOL_FALSE;
			memset(tmp.next,NULL,sizeof(tmp.next));
			rbt.next[RASM_CHAR2TREE_VAL(s[n])] = tmp;
		}
		rbt = rbt.next[RASM_CHAR2TREE_VAL(s[n])];
	}
	rbt.val = RASM_BOOL_TRUE;
	return RASM_BOOL_TRUE;
}
main()
{
	printf("%d\n",RASM_TREE_NEW("Hello_world"));
	printf("%d\n",RASM_TREE_FIND("Hello_world"));
	return 0; 
}
