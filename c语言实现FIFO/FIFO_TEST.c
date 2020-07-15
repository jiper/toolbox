#include <stdio.h>
#include "FIFO.h"
#include <stdint.h>

typedef int32_t TestType;


int main()
{
		
	//����1������FIFO
	int Length = 0,space =0;
	FIFO MyFifo = {sizeof(TestType),10};
	pFIFO pMyFifo = &MyFifo;
	TestType Data[10] = {0};
	CreateFIFO(&MyFifo);
	memcpy(Data, MyFifo.FIFO_Buff, 10);

	//����2��д��
	Length = GetBuffOccupation(&MyFifo);
	space = GetBuffSpace(&MyFifo);
	TestType dataInput[5] = { 0,1,2,3,4 };
	if (SuperWrite(&MyFifo, dataInput, 5) == FIFO_ERROR)
	{
		return -1;
	}
	memcpy(Data, MyFifo.FIFO_Buff, 10);
	Length = GetBuffOccupation(&MyFifo);
	space = GetBuffSpace(&MyFifo);

	//����3����һ��������
	TestType dataOut[10];
	SuperRead(pMyFifo, dataOut, 3);
	Length = GetBuffOccupation(&MyFifo);
	space = GetBuffSpace(&MyFifo);
	memcpy(Data, MyFifo.FIFO_Buff, 10);

	//����4��д��β������
	if (SuperWrite(&MyFifo, dataInput, 5) == FIFO_ERROR)
	{
		return -1;
	}
	Length = GetBuffOccupation(&MyFifo);
	space = GetBuffSpace(&MyFifo);
	memcpy(Data, MyFifo.FIFO_Buff, 10);

	//����5����ȡ���е�����
	if (SuperRead(&MyFifo, dataOut, 7) == FIFO_ERROR)
	{
		return -1;
	}
	Length = GetBuffOccupation(&MyFifo);
	space = GetBuffSpace(&MyFifo);
	memcpy(Data, MyFifo.FIFO_Buff, 10);


	printf("hello world!\n");
	return 0;
}
