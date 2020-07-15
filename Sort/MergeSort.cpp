#include <stdlib.h>
//���÷ǵݹ�ʵ��

/**
* @Description: �������SR[i...m]��SR[m+1...n]�鲢Ϊ�����TR[i...n]������������Ŵ�0��ʼ
* @param SR - ���鲢����
* @param TR - �鲢�������
* @param i - ��ʼ����
* @param m - �ָ�����
* @param n - ��������
* @return NULL
*/
void Merge(int SR[],int TR[],int i,int m,int n)
{
	int k,j;
	for (j = m + 1, k = i; j <= n && i <= m; k++)
	{
		if (SR[i] <= SR[j])   //��֤�����ȶ���
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
	if (i <= m)
	{
		for (; i <= m; i++)
			TR[k++] = SR[i];
	}
	else if (j <= n)
	{
		for (; j <= n; j++)
			TR[k++] = SR[j];
	}
}

/**
* @Description: ���������鲢
* @param SR - ���鲢����
* @param TR - �鲢�������
* @param s - �鲢�����еĳ���
* @param n - ���鲢�����ܳ���
* @return NULL
*/
void MergePass(int SR[], int TR[], int s, int n)
{
	int i = 0;
	while (i < n - 2 * s)  //�����鲢
	{
		Merge(SR, TR, i, i + s - 1, i + 2 * s - 1);
		i += 2 * s;
	}
	if (i < n - s)  //���ʣ���������У��鲢�����������
	{
		Merge(SR, TR, i, i + s - 1, n-1);
	}
	else  //ֻʣ��һ������
	{
		for (int j = i; j < n; j++)
		{
			TR[j] = SR[j];
		}
	}
}


void MergeSort(int* dataRaw, int length)
{
	int* TR = (int*)malloc(sizeof(int) * length);
	int k = 1;
	while (k < length)
	{
		MergePass(dataRaw, TR, k, length);
		k = 2 * k;
		MergePass(TR, dataRaw, k, length);
		k = 2 * k;
	}
}