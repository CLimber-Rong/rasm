#include"stdio.h"
#include"../mem.c"
main()
{
	/*
		�һ����ýӿڲ�ͨ�����ָ��������ݴ����ٳ����������֤�ӿ��Ƿ���bug 
		��������ASCII�������������֣�RASM!!
		��Rȡ���������һ�����١���ƴ������ĸ��        
	*/
	
	RASM_MOV_PACK src,dst;
	void* v1 = malloc(2);
	void* v2 = malloc(2);
	*(RASM_uWORD*)v1 = RASM_AH;
	*(RASM_WORD*)v2 = 'R';
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	/*REG <= NUM*/
		
	*(RASM_uWORD*)v1 = 0;
	*(RASM_uWORD*)v2 = RASM_AH;
	RASM_MOV_PACK_SET(&src,RASM_MPT_USM,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_REG,v2);
	RASM_MOV(src,dst);
	/*USM <= REG*/
	
	*(RASM_uWORD*)v1 = RASM_BL;
	*(RASM_uWORD*)v2 = 0;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_USM,v2);
	RASM_MOV(src,dst);
	printf("%c",RASM_REG[RASM_BX]);
	/*REG <= USM*/
	
	//NEXT ONE
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2  = 'A';
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	/*REG <= NUM*/
	*(RASM_uWORD*)v1 = RASM_REG_LH_SIZE + RASM_DX;
	*(RASM_WORD*)v2  = RASM_REG_LH_SIZE + RASM_AX;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_REG,v2);
	RASM_MOV(src,dst);
	printf("%c",RASM_REG[RASM_DX]);
	/*REG <= REG*/
	
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2  = 'S';
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	/*REG <= NUM*/
	*(RASM_uWORD*)v1 = RASM_REG_LH_SIZE + RASM_DX;
	*(RASM_WORD*)v2  = RASM_REG_LH_SIZE + RASM_AX;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_REG,v2);
	RASM_MOV(src,dst);
	printf("%c",RASM_REG[RASM_DX]);
	
	*(RASM_uWORD*)v1 = RASM_AL;
	*(RASM_WORD*)v2  = 'M';
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_NUM,v2);
	RASM_MOV(src,dst);
	/*REG <= NUM*/
	*(RASM_uWORD*)v1 = RASM_REG_LH_SIZE + RASM_DX;
	*(RASM_WORD*)v2  = RASM_REG_LH_SIZE + RASM_AX;
	RASM_MOV_PACK_SET(&src,RASM_MPT_REG,v1);
	RASM_MOV_PACK_SET(&dst,RASM_MPT_REG,v2);
	RASM_MOV(src,dst);
	printf("%c",RASM_REG[RASM_DX]);
	return 0;
}
