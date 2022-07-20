#include"cpu.c"
#include"stdio.h"

main()
{
	/*
	 * ADD AL 5
	 * SUB AL 6
	 * PRINT AX
	 * PRINT CF
	*/
	//init
	RASM_MOV_PACK src,dst;
	void *v1,*v2;
	v1 = malloc(2);
	v2 = malloc(2);
	//ADD AL 5
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2  = 5;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_ADD(src,dst);
	//SUB AL 6
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2  = 6;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_SUB(src,dst);
	printf("AX=%d\n",RASM_REG[RASM_AX]);
	printf("CF=%d\n",RASM_REG[RASM_CF]);
	return 0;
}
