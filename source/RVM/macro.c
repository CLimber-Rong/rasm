/*
 * Write macro here
*/

//#include"stdio.h"

#include"stdlib.h"
#include"string.h"

#define NULL ((void*)0)
#define RASM_TRUE  1
#define RASM_FALSE 0
typedef char  RASM_BOOL;
typedef char* RASM_STRING;

typedef struct RASM_RBT_TYPE{
	RASM_BOOL isdef;
	void* val;
	struct RASM_RBT_TYPE* next[1+10+26+26];
}RASM_MACRO_NODE;

RASM_MACRO_NODE* RASM_MACRO[1+26+26];

RASM_BOOL			RASM_MACRO_CHECK(RASM_STRING s);
RASM_BOOL			RASM_MACRO_INIT(RASM_MACRO_NODE*[1+26+26]);
RASM_BOOL 			RASM_MACRO_DEF(RASM_MACRO_NODE*[1+26+26],RASM_STRING,void*);
RASM_MACRO_NODE* 	RASM_MACRO_GET(RASM_MACRO_NODE*[1+26+26],RASM_STRING);
RASM_BOOL			RASM_MACRO_UNDEF(RASM_MACRO_NODE*[1+26+26],RASM_STRING);

RASM_BOOL RASM_MACRO_CHECK(RASM_STRING s)
{
	if( !(s[0]=='_'||('a'<=s[0]&&s[0]<='z')||('A'<=s[0]&&s[0]<='Z') ))	return RASM_FALSE;
	int i = 1;
	while(s[i]!='\0'){
		if( !(s[i]=='_'||('a'<=s[i]&&s[i]<='z')||('0'<=s[i]&&s[i]<='9')||('A'<=s[i]&&s[i]<='Z') ))	return RASM_FALSE;
		i++;
	}
	return RASM_TRUE;
}

RASM_BOOL RASM_MACRO_INIT(RASM_MACRO_NODE* src[1+26+26])
{
	int i;
	for(i=0;i<1+26+26;i++){
		src[i] = (RASM_MACRO_NODE*)malloc(sizeof(RASM_MACRO_NODE));
		if(src[i]==NULL)	return RASM_FALSE;
		src[i]->isdef = RASM_FALSE;
		int j;
		for(j=0;j<1+26+25;j++){
			src[i]->next[i] = NULL;
			src[i]->val     = NULL;
		}
	}
	return RASM_TRUE;
}

RASM_BOOL RASM_MACRO_DEF(RASM_MACRO_NODE* src[1+26+26],RASM_STRING key,void* val)
{
	if(!RASM_MACRO_CHECK(key))	return RASM_FALSE;
	RASM_MACRO_NODE* node = NULL;
	/*START DEF*/
	if(key[0]=='_')				node = src[0];
	if('a'<=key[0]<='z')		node = src[key[0]-'a'+1];
	if('A'<=key[0]<='Z')		node = src[key[0]-'A'+1+26];
	int i = 1;
	while(key[i]!='\0'){
		int id = 0;
		if('0'<=key[i]&&key[i]<='9')	id = 1+10+key[i] - '0';
		if('a'<=key[i]&&key[i]<='z')	id = 1+key[i]-'a';
		if('A'<=key[i]&&key[i]<='Z')	id = 1+26+10+key[i]-'A';
		if(node->next[id]==NULL){
			node->next[id] = (RASM_MACRO_NODE*)malloc(sizeof(RASM_MACRO_NODE));
			if(node->next[id]==NULL)	return RASM_FALSE;
			//set to null
			node->next[id]->val = NULL;
			int i;
			for(i=0;i<1+10+26+26;i++)	node->next[id]->next[i] = NULL;
			node->next[id]->isdef = RASM_FALSE;
		}
		node = node->next[id];
		i++;
	}
	node->val = val;
	node->isdef = RASM_TRUE;
	return RASM_TRUE;
}

RASM_MACRO_NODE* RASM_MACRO_GET(RASM_MACRO_NODE* src[1+26+26],RASM_STRING key)
{
	if(!RASM_MACRO_CHECK(key))	return NULL;
	RASM_MACRO_NODE* node = NULL;
	/*START DEF*/
	if(key[0]=='_')				node = src[0];
	if('a'<=key[0]<='z')		node = src[key[0]-'a'+1];
	if('A'<=key[0]<='Z')		node = src[key[0]-'A'+1+26];
	int i = 1;
	while(key[i]){
		int id = 0;
		if('0'<=key[i]&&key[i]<='9')	id = 1+10+key[i] - '0';
		if('a'<=key[i]&&key[i]<='z')	id = 1+key[i]-'a';
		if('A'<=key[i]&&key[i]<='Z')	id = 1+26+10+key[i]-'A';
		if(node->next[id]==NULL){
			return NULL;
		}
		node = node->next[id];
		i++;
	}
	if(node->isdef==RASM_FALSE)	return NULL;
	return node;
}

RASM_BOOL RASM_MACRO_UNDEF(RASM_MACRO_NODE* src[1+26+26],RASM_STRING s)
{
	RASM_MACRO_NODE* node = RASM_MACRO_GET(src,s);
	if(node==NULL)	return RASM_FALSE;
	free(node->val);		//free it!
	node->isdef = RASM_FALSE;		//Reflag
}
