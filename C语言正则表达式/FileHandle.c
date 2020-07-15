#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "FileHandle.h"

//#include<time.h>
//#include<dos.h>
//#include<conio.h>
//#include <windows.h>
//#include <direct.h>


static int calc_file_len(char *instr) //�������������Լ����ļ����ĳ���
{
	int len = 0;
	char *index = instr;
	while (*index != '\0')
	{
		index++;
		len++;
	}
	return len+1;
}
void SearchDir(const char* search_cond, char(*file_name)[MAX_FILE_NAME_LEN], int *len)
{
	struct _finddata_t data;
	long hnd = _findfirst(search_cond, &data);    // �����ļ�����������ʽchRE��ƥ���һ���ļ�
	if (hnd < 0)
	{
		perror(search_cond);
	}
	int  nRet = (hnd < 0) ? -1 : 1;
	while (nRet >= 0)
	{
		if (data.attrib == _A_SUBDIR)  // �����Ŀ¼
		{
			printf("   [%s]*\n", data.name);
		}
		else
		{
			*len += 1;
			memcpy(file_name[0] + 1, &data.name, MAX_FILE_NAME_LEN); //�ļ�������
			*file_name[0] = calc_file_len(data.name); //�ļ����ȼ����д��
			file_name++;
		}
		nRet = _findnext(hnd, &data);
	}
	_findclose(hnd);     // �رյ�ǰ���
}
