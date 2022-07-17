/*
	Name: Rong
	Copyright: Rong
	Author: Rong
	Date: 07/07/22 14:25
	Description: Write CPU here
*/

#include"mem.c"

/*Arithmetic operation section*/
RASM_BOOL RASM_ADD(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_SUB(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_MUL(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_DIV(RASM_MOV_PACK,RASM_MOV_PACK);
/*Logical operation section*/
RASM_BOOL RASM_OR(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_AND(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_NOT(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_XOR(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_SAL(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_SAR(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_SHL(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_SHR(RASM_MOV_PACK,RASM_MOV_PACK);
RASM_BOOL RASM_CMP(RASM_MOV_PACK,RASM_MOV_PACK);
/*Oh my god!I need to write so many function!!*/

/*OK...Let's go!*/

RASM_BOOL RASM_ADD(RASM_MOV_PACK src,RASM_MOV_PACK dst)
{
	RASM_WORD addn = 0;
	//LET ADDN = DST.VAL
	//THEN LET SRC+=ADDN
	//I'M SO CLEVER :-)
	if(dst.type==RASM_MPT_REG){
		if(*(RASM_uWORD*)(dst.val)<RASM_REG_SIZE)	return RASM_FALSE;
		if(*(RASM_uWORD*)(dst.val)<RASM_REG_LH_SIZE){
			//low-high level
			if(*(RASM_uWORD*)(dst.val)%2==0){
				//low level
				addn = (RASM_BYTE)(RASM_REG[*(RASM_uWORD*)(dst.val)/2]);
			}else{
				//high level
				addn = (RASM_BYTE)(RASM_REG[*(RASM_uWORD*)(dst.val)/2]>>8);
			}
		}else{
			//a reg
			addn = (RASM_WORD)(RASM_REG[*(RASM_uWORD*)(dst.val)]);
		}
	}else
	if(dst.type==RASM_MPT_NUM){
		addn = *(RASM_WORD*)dst.val;
	}
	//NOW I WIIL LET SRC+=ADDN
	//DONT FORGET CARRY-FLAG
	//I'M SO TIERD SO I WANT TO HAVE A LITTLE REST...
	
	//HAVING REST...
	
	//OK GUYS I HAVE A TWO-DAY REST,AND LET'S GO!
	if(src.type!=RASM_MPT_REG)	return RASM_FALSE;
	//ONLY REG+=REG OR REG+=NUM
	if(*(RASM_uWORD*)(src.val)<RASM_REG_LH_SIZE){
		//LOW-HIGH LEVEL
		if(*(RASM_uWORD*)(src.val)%2==0){
			//LOW LEVEL
			RASM_WORD tmp;
			tmp = (RASM_BYTE)RASM_REG[*(RASM_uWORD*)(src.val)/2];
			tmp += (RASM_BYTE)(addn);
			printf("%x ",tmp);
			RASM_REG[RASM_CF] = (RASM_WORD)((RASM_uWORD)tmp>>8);	
			tmp = (RASM_BYTE)tmp;
			tmp += RASM_REG[*(RASM_uWORD*)(src.val)/2] - (RASM_BYTE)RASM_REG[*(RASM_uWORD*)(src.val)];
			RASM_REG[*(RASM_uWORD*)(src.val)/2] = tmp;
		}
	}
}

//TEST MAIN
main()
{
	RASM_MOV_PACK src,dst;
	void* v1 = malloc(2);
	void* v2 = malloc(2);
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2  = (RASM_BYTE)(-1);
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_ADD(src,dst);
	
	*(RASM_uWORD*)v1 = 	RASM_AL;
	*(RASM_WORD*)v2  = (RASM_BYTE)(1);
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_ADD(src,dst);
	printf("%d",RASM_REG[RASM_CF]);
	return 0;
}
