/*
	Name: Rong
	Copyright: Rong
	Author: Rong
	Date: 07/07/22 14:25
	Description: Write CPU here
*/
//#include"stdio.h"

#include"mem.c"

/*Arithmetic operation section*/
RASM_BOOL RASM_ADD(RASM_MOV_PACK,RASM_MOV_PACK);		//COMPLETE - 22/7/18
RASM_BOOL RASM_SUB(RASM_MOV_PACK,RASM_MOV_PACK);		//COMPLETE - 22/7/20
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
	}else	return RASM_FALSE;
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
	return RASM_FALSE;
	//OHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
	//I DONE IT!!!
	//(EXCITED)
}

RASM_BOOL RASM_SUB(RASM_MOV_PACK src,RASM_MOV_PACK dst)
{
	//OK Let's go
	/* ---中文讲解--- 
	* 首先我们先来讲述算法
	* 其实我最关心的还是小的数字减去大的数字，这样结果会是负数
	* 我通过证明得知，其实只要再向前借位，就会得到负数，这很神奇
	* 比如0000|0001减去0000|0010，这个时候应该借位，所以这个算式变成了1|0000|0001 - 0000|0010
	* 此时你会发现结果是1111|1111，也就是-1，这个时候答案正确
	* 再来说说进位寄存器，这很好理解，当产生借位时，进位寄存器被借掉了，所以此时他是0
	* 如果没产生借位，进位寄存器是1
	* 你会发现，进位寄存器总是与我们的预期相反，所以我们只要把进位寄存器取反即可 
	* 当然，证明过程很复杂，我有空再写到文档里
	* （这个注释写的我好累） 
	*/
	/* ---English Annotation---
	* So let's talk about algorithms first
	* Actually, what I care about most is subtracting a large number from a small number, so I get a negative number
	* I just proved that if I borrow further, I actually get a negative number, which is amazing
	* 0000|0001 minus 0000|0010, for example, should a borrow this time, so the formula into 1|0000|0001 - 0000|0010
	* At this stage, you will find that the result is 1111|1111, which is -1, this time the answer is right
	* And now,carry-flag = 0 when the answer is negative
	* And now,carry-flag = 1 when the answer is positive
	* You will find:It's the opposite of the answer!
	* So carry-flag = !(carry-flag)
	* of course, that process is complicated, I'm free to write in the document
	*/
	
	/*
	 * Let subn   = dst,
	 * Let result = src - subn
	 * count carry-flag
	*/
	RASM_WORD subn = 0;
	RASM_DWORD result = 0x10000;
	/*
	 * 0x10000 is carry-flag
	 * Cause 0x10000 = 0b1|0000|0000
	*/
	//First,Let sunb = dst
	if(dst.type==RASM_MPT_USM)	return RASM_FALSE;
	if(dst.type==RASM_MPT_REG){
		//reg
		if(*(RASM_uWORD*)(dst.val)>=(RASM_REG_LH_SIZE+RASM_REG_SIZE))	return RASM_FALSE;
		if(*(RASM_uWORD*)(dst.val)<RASM_REG_LH_SIZE){
			//low-high level
			if(*(RASM_uWORD*)(dst.val)%2==0){
				//low-level
				subn = RASM_REG[*(RASM_uWORD*)(dst.val)/2] & 0x00ff;
			}else{
				//high-level
				subn = RASM_REG[*(RASM_uWORD*)(dst.val)/2] & 0xff00;
			}
		}else{
			//whole reg
			subn = RASM_REG[*(RASM_uWORD*)(dst.val)-RASM_REG_LH_SIZE];
		}
	}else if(dst.type==RASM_MPT_NUM){
		subn = *(RASM_WORD*)(dst.val);
	}else	return RASM_FALSE;
	//Second Let result = src - subn
	if(src.type==RASM_MPT_REG){
		//reg
		if(*(RASM_uWORD*)(src.val)>=(RASM_REG_LH_SIZE+RASM_REG_SIZE))	return RASM_FALSE;
		if(*(RASM_uWORD*)(src.val)<RASM_REG_LH_SIZE){
			//low-high level
			if(*(RASM_uWORD*)(src.val)%2==0){
				//low-level
				result += RASM_REG[*(RASM_uWORD*)(src.val)/2] & 0x00ff;
				result -= (subn&0X00ff);
				RASM_REG[*(RASM_uWORD*)(src.val)/2] = (RASM_REG[*(RASM_uWORD*)(src.val)/2]&0xff00)+(result&0x00ff);
				RASM_REG[RASM_CF] = !(result & 0x10000);
				return RASM_TRUE;
			}else{
				//high-level
				result += ((RASM_uWORD)(RASM_REG[*(RASM_uWORD*)(src.val)/2] & 0xff00)>>8);
				result -= (subn & 0x00ff);
				RASM_REG[*(RASM_uWORD*)(src.val)/2] = (RASM_REG[*(RASM_uWORD*)(src.val)/2]&0x00ff)+(RASM_uWORD)(result<<8);
				RASM_REG[RASM_CF] = !(result&0x10000);
				return RASM_TRUE;
			}
		}else{
			//whole reg
			result += RASM_REG[*(RASM_uWORD*)(src.val)-RASM_REG_LH_SIZE];
			result -=(subn & 0xffff);
			RASM_REG[*(RASM_uWORD*)(src.val)-RASM_REG_LH_SIZE] = (RASM_WORD)result;
			RASM_REG[RASM_CF] = !(result&0xffff);
			return RASM_TRUE;
		}
	}else{
		return RASM_FALSE;
	}
	return RASM_FALSE;;
}
