#include"cpu.c" 

main()
{
	/*
	 * MAKE A LITTLE PROGRAM
	 
	MOV AH, 0XF0
	MOV AL, 0X02
	MOV EAX,AX
	MOV AH, 0X0F
	MOV AL, 0XFF
	ADD AX, EAX
	*/
	//INIT
	RASM_MOV_PACK src,dst;
	void *v1,*v2;
	v1 = malloc(2);
	v2 = malloc(2);
	//MOV AH, 0XF0
	*(RASM_uWORD*)v1 = RASM_AH;
	*(RASM_WORD*)v2 = 0xf0;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	//MOV AL, 0X02
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2 = 0x02;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	//MOV EAX,AX
	*(RASM_uWORD*)v1 = RASM_REG_LH_SIZE+RASM_EAX;
	*(RASM_uWORD*)v2 = RASM_REG_LH_SIZE+RASM_AX;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_REG,v2);
	RASM_MOV(src,dst);
	//MOV AH, 0X0F
	*(RASM_uWORD*)v1 = RASM_AH;
	*(RASM_WORD*)v2 = 0x0f;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	//MOV AL, 0XFF
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2 = 0xff;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	printf("AX=%x\n",(RASM_uWORD)RASM_REG[RASM_AX]);
	printf("EAX=%x\n",(RASM_uWORD)RASM_REG[RASM_EAX]);
	//ADD AX,EAX
	*(RASM_uWORD*)v1 = RASM_REG_LH_SIZE+RASM_AX;
	*(RASM_uWORD*)v2 = RASM_REG_LH_SIZE+RASM_EAX;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_REG,v2);
	RASM_ADD(src,dst);
	printf("EAX+AX=%x\n",RASM_REG[RASM_AX]);
	printf("CF=%x\n",RASM_REG[RASM_CF]);
	return 0;
}
