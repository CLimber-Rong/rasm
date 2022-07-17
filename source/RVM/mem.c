/*
 * Write register and memory here
*/
#include"stdio.h"

#include"macro.c"
#include"custom.c"

typedef int 			RASM_DWORD;
typedef unsigned int	RASM_uDWORD; 
typedef short 			RASM_WORD;
typedef unsigned short 	RASM_uWORD;
typedef char 			RASM_BYTE;

enum RASM_REG_ENUM{
	RASM_AX=0,RASM_BX,RASM_CX,RASM_DX,								//master reg
	RASM_EAX,RASM_EBX,RASM_ECX,RASM_EDX,							//extra
	RASM_EX,RASM_FX,RASM_GX,										//extra
	RASM_PBP,RASM_PEP,RASM_RBP,RASM_REP,							//parameter point and return-val point
	RASM_CF,RASM_LF,RASM_ZF,RASM_SF,								//carry flag,logic flag,zero flag,sign flag
	RASM_INBP,RASM_INEP,RASM_OUBP,RASM_OUEP,RASM_APIB,RASM_APIE,	//IO-point
	RASM_REG_SIZE													//size
};

enum RASM_REG_LH_ID{
	RASM_AL=0,RASM_AH,
	RASM_BL,RASM_BH,
	RASM_CL,RASM_CH,
	RASM_DL,RASM_DH,
	RASM_REG_LH_SIZE
};

enum RASM_MOV_PACK_TYPE{
	RASM_MPT_USM = 0,												//user-memory
	RASM_MPT_REG,													//reg
	RASM_MPT_NUM													//number
};

typedef struct{
	int type;
	void* val;
}RASM_MOV_PACK;

typedef struct{
	RASM_uDWORD topn;
	RASM_WORD data[RASM_STACK_TOP_MAX_NUM];
}RASM_STACK_TYPE;

RASM_WORD RASM_REG[RASM_REG_SIZE-1];								//register
RASM_BYTE RASM_MEM[RASM_USER_MEM_PARTITION][64*1024] = {0}; 		//memory
RASM_BYTE RASM_CODE[RASM_CODE_MEM_PARTITION]; 						//code memory
RASM_STACK_TYPE RASM_STACK;											//stack
RASM_uDWORD RASM_CS;												//running address
RASM_uDWORD RASM_LP;												//label point
RASM_uDWORD RASM_MEM_NP = 0;										//now partition

RASM_BOOL  RASM_MOV_PACK_SET(RASM_MOV_PACK*,int,void*);
RASM_BOOL  RASM_INTO(RASM_uWORD);
RASM_BOOL  RASM_MOV(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL  RASM_MOVL(RASM_MOV_PACK);
RASM_BOOL  RASM_DB(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL  RASM_SETLP(RASM_MOV_PACK); 
RASM_BOOL  RASM_PUSH(RASM_MOV_PACK);
RASM_BOOL  RASM_POP(RASM_MOV_PACK);

RASM_BOOL RASM_MOV_PACK_SET(RASM_MOV_PACK* src,int type,void* val)
{
	if(src==NULL)	return RASM_FALSE;
	else{
		src->type = type;
		src->val  = val;
		return RASM_TRUE;
	}
	return RASM_FALSE;
}

RASM_BOOL RASM_INTO(RASM_uWORD part)
{
	if(part>RASM_USER_MEM_PARTITION){
		return RASM_FALSE;
		//I FEEL SO TIRED WHEN I WRITE HERE
		//NUT I KNOW, I WILL BE THE WINNER!
	}else{
		RASM_MEM_NP = part;
		return RASM_TRUE;
	}
	return RASM_FALSE;	//I DONT KNOW WHY I NEED TO RETURN HERE....:-)
	//OK GUYS,THE FUNCTION OF INTO IS SO EASY,R1GHT? ;-)
}

RASM_BOOL RASM_MOV(RASM_MOV_PACK src,RASM_MOV_PACK dst)
{
	/*
		type:
			0:user-mem
			1:reg
			2:num
	*/
	/**/
	if(src.type==0){
		if(dst.type==1){
			if(*(RASM_uWORD*)(dst.val)<=RASM_DX*2){
				if(*(RASM_uWORD*)(dst.val)%2==1)
					RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(src.val)] = (RASM_BYTE)(RASM_REG[*(RASM_uWORD*)(dst.val)/2]>>8);
				else
					RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(src.val)] = (RASM_BYTE)(RASM_REG[*(RASM_uWORD*)(dst.val)/2]);
			}else{
				return RASM_FALSE;
			}
		}else{
			return RASM_FALSE;
		}
	}else
	if(src.type==1){
		if(dst.type==0){
			//mem
			if(*(RASM_uWORD*)(src.val)<=RASM_REG_LH_SIZE-1){
				if(*(RASM_uWORD*)(src.val)%2==0){
					RASM_WORD tmp = 0;
					tmp += (RASM_WORD)((RASM_BYTE)(RASM_REG[*(RASM_uWORD*)(src.val)/2]>>8));
					tmp += (RASM_WORD)RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(dst.val)];
					RASM_REG[*(RASM_uWORD*)(src.val)/2] = tmp;
				}else{
					RASM_WORD tmp = 0;
					tmp += (RASM_BYTE)(RASM_REG[*(RASM_uWORD*)(src.val)]);
					tmp += (RASM_WORD)(RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(dst.val)]<<8);
					RASM_REG[*(RASM_uWORD*)(src.val)/2] = tmp;
				}
			}else{
				return RASM_FALSE;
			}
		}else
		if(dst.type==1){
			//reg
			if(*(RASM_uWORD*)(dst.val)>=RASM_REG_LH_SIZE){
				RASM_REG[*(RASM_uWORD*)(src.val)-RASM_REG_LH_SIZE] = RASM_REG[*(RASM_uWORD*)(dst.val)-RASM_REG_LH_SIZE];
			}else{
				return RASM_FALSE;
			}
		}else
		if(dst.type==2){
			if(*(RASM_uWORD*)(src.val)<=RASM_DX*2){
				if(*(RASM_uWORD*)(src.val)%2==1){
					RASM_WORD tmp = *(RASM_BYTE*)(dst.val);
					tmp = tmp<<8;
					/*tmp = tmp<<8;
					tmp+=(RASM_BYTE)RASM_REG[*(RASM_uWORD*)(src.val)];
					RASM_REG[*(RASM_uWORD*)(src.val)] = tmp;*/
					RASM_WORD tmp2 = RASM_REG[*(RASM_uWORD*)(src.val)];
					tmp2 = tmp2<<8;
					tmp2 = tmp2>>8;
					RASM_REG[*(RASM_uWORD*)(src.val)/2] = tmp + tmp2;
				}else{
					RASM_WORD tmp = RASM_REG[*(RASM_uWORD*)(src.val)];
					tmp = tmp>>8;
					tmp = tmp<<8;
					tmp+= *(RASM_BYTE*)(dst.val);
					RASM_REG[*(RASM_uWORD*)(src.val)/2] = tmp;
				}
			}else{
				return RASM_FALSE;
			}
		}else
		return RASM_FALSE;
	}else	return RASM_FALSE;
	return RASM_TRUE;	//that's ok
}

RASM_BOOL RASM_MOVL(RASM_MOV_PACK src)
{
	if(*(RASM_uWORD*)(src.val)>=64*1024-1)	return RASM_FALSE;	//out addr
	RASM_BYTE* anay_p = (RASM_BYTE*)&RASM_LP;
	if(src.type==0){
		//I wrte it by hands but dont use loop for fastest
		RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(src.val) + 0] = *anay_p;	anay_p++;
		RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(src.val) + 1] = *anay_p;	anay_p++;
		RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(src.val) + 2] = *anay_p;	anay_p++;
		RASM_MEM[RASM_MEM_NP][*(RASM_uWORD*)(src.val) + 3] = *anay_p;	anay_p++;
		anay_p = NULL;
		return RASM_TRUE;
	}
	return RASM_FALSE;
}

RASM_BOOL RASM_DB(RASM_MOV_PACK src,RASM_MOV_PACK dst)
{
	RASM_uWORD addr = *(RASM_uWORD*)src.val;
	if(addr>64*1024-1)	return RASM_FALSE;
	char c = *(char*)dst.val;
	RASM_MEM[RASM_MEM_NP][addr] = c;
	return RASM_TRUE;
}

RASM_BOOL RASM_SETLP(RASM_MOV_PACK src)
{
	if(*(RASM_uWORD*)(src.val)>=64*1024)	return RASM_FALSE;
	RASM_uDWORD tmp 		= 0;
	RASM_BYTE*	tmp_ptr 	= (RASM_BYTE*)(src.val);
	tmp += (RASM_uWORD)*(RASM_BYTE*)(tmp_ptr); tmp<<=8; tmp_ptr++;
	tmp += (RASM_uWORD)*(RASM_BYTE*)(tmp_ptr); tmp<<=8; tmp_ptr++;
	tmp += (RASM_uWORD)*(RASM_BYTE*)(tmp_ptr); tmp<<=8; tmp_ptr++;
	tmp += (RASM_uWORD)*(RASM_BYTE*)(tmp_ptr);
	RASM_LP = tmp;
	return RASM_TRUE;
}

RASM_BOOL RASM_PUSH(RASM_MOV_PACK dst)
{
	//CHECK STACK OUT
	if(RASM_STACK.topn>=RASM_STACK_TOP_MAX_NUM||*(RASM_uWORD*)(dst.val)>=RASM_REG_SIZE)			
		return RASM_FALSE;
	/*DON'T THINK THIS SENTENCE IS LONG,IJUST CHECK THE DEST'S TYPE AND STACK OUT AND REG-ID*/
	//OK GUYS LETS WRITE PUSH(NO!!I DONT WANT TO WRITE IT)
	RASM_STACK.data[RASM_STACK.topn] = RASM_REG[*(RASM_uWORD*)(dst.val)];
	RASM_STACK.topn++;
}

RASM_BOOL RASM_POP(RASM_MOV_PACK src)
{
	if(RASM_STACK.topn==0)	return RASM_FALSE;
	if(src.type==0){
		RASM_STACK.data[RASM_STACK.topn-1] = 0;
		RASM_STACK.topn--;
		return RASM_TRUE;
		//just pop
	}else{
		RASM_REG[*(RASM_uWORD*)(src.val)] = RASM_STACK.data[RASM_STACK.topn-1];
		RASM_STACK.topn--;
		return RASM_TRUE;
	}
}

