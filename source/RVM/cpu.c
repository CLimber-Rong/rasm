/*
	Name: Rong
	Copyright: Rong
	Author: Rong
	Date: 07/07/22 14:25
	Description: Write CPU here
*/
#include"stdio.h"

#include"mem.c"

/*Arithmetic operation section*/
RASM_BOOL RASM_ADD(RASM_MOV_PACK,RASM_MOV_PACK);		//COMPLETE - 22/7/18
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
		if(*(RASM_uWORD*)(dst.val)>=RASM_REG_LH_SIZE+RASM_REG_SIZE)	return RASM_FALSE;
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
			addn = (RASM_WORD)(RASM_REG[*(RASM_uWORD*)(dst.val)-RASM_REG_LH_SIZE]);
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
	if(*(RASM_uWORD*)(src.val)>=(RASM_REG_LH_SIZE+RASM_REG_SIZE))	return RASM_FALSE;
	//ONLY REG+=REG OR REG+=NUM
	if(*(RASM_uWORD*)(src.val)<RASM_REG_LH_SIZE){
		//LOW-HIGH LEVEL
		if(*(RASM_uWORD*)(src.val)%2==0){
			//LOW LEVEL
			/*
			 * GET LOW-LEVEL TO TMP
			 * ADD NUM TO TMP
			 * COUNT CARRY-FLAG
			 * MOV LOW-LEVEL TMP
			*/
			RASM_WORD tmp = 0;
			/*I'M SO STUPID
			 * 0X00FF & REG = REG'S LOW-LEVEL
			 * 0XFF00 & REG = REG'S HIGH-LEVEL
			 * AHHHHHHHHHH,I FORGOT IT!!
			 * OK LET IT PASS
			 * OPTIMIZE IT TOGETHER NEXT TIME......
			*/
			//GET LOW-LEVEL TO TMP
			tmp += RASM_REG[*(RASM_uWORD*)(src.val)] & 0x00ff;
			//ADD NUM TO TMP
			tmp += addn & 0x00ff;
			//COUNT CARRY-FLAG
			RASM_REG[RASM_CF] = ((RASM_uWORD)tmp)>>8;
			//MOV LOW-LEVEL TMP
			RASM_REG[*(RASM_uWORD*)(src.val)/2] = (RASM_REG[*(RASM_uWORD*)(src.val)/2] & 0xff00) + (tmp & 0x00ff);
			//RETURN TRUE
			return RASM_TRUE;
		}else{
			//HIGH-LEVEL
			RASM_WORD tmp = 0;
			//GET HIGH-LEVEL TO TMP
			tmp += (RASM_uWORD)(RASM_REG[*(RASM_uWORD*)(src.val)/2] & 0xff00)>>8;
			//ADD NUM TO TMP
			tmp += addn & 0x00ff;
			//COUNT CARRY-FLAG
			RASM_REG[RASM_CF] = ((RASM_uWORD)tmp)>>8;
			//MOV HIGH-LEVEL TMP
			RASM_REG[*(RASM_uWORD*)(src.val)/2] = (RASM_REG[*(RASM_uWORD*)(src.val)/2] & 0x00ff) + ((tmp & 0x00ff)<<8);
			//RETURN TRUE
			return RASM_TRUE;
			/*OHHH! IN FINALLY I COMPLETE IT!!*/
		}
	}else{
		//WHOLE REG
		/*
		 * MOV REG TO TMP
		 * ADD NUM TO TMP
		 * COUNT CARRY-FLAG
		 * MOV REG TMP
		*/
		RASM_DWORD tmp = 0;
		//MOV REG TO TMP
		tmp += (RASM_REG[*(RASM_uWORD*)(src.val)-RASM_REG_LH_SIZE] & 0xffff);
		//ADD NUM TO TMP
		tmp += (addn & 0xffff);
		//COUNT CARRY-FLAG
		RASM_REG[RASM_CF] = (RASM_WORD)(tmp>>16);
		//MOV REG TMP
		RASM_REG[*(RASM_uWORD*)(src.val)-RASM_REG_LH_SIZE] = (RASM_WORD)tmp; 
		//RETURN TRUE;
		return RASM_TRUE;
	}
	//OHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
	//I DONE IT!!!
	//(EXCITED)
}
