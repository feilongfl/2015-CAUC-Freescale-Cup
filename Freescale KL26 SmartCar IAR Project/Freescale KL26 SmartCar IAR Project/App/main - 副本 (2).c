/*!
*
* @file       main.c
* @brief      ��˼����������
* @author     ����
* @version    v0.1
* @date       2015-1-7
*/
/************************************************************************/
/* �ļ�����                                                             */
/************************************************************************/
#include "main.h"
#include "sd_driver.h"
#define BUFF_SIZE   100
/************************************************************************/
/* ȫ�ֱ�����ṹ��                                                     */
/************************************************************************/
uint32 Distance = 0;
/************************************************************************/
/*  �ⲿ���ú���                                                     */
/************************************************************************/
extern void UartHandler();
/************************************************************************/
/*                       ������                                         */
/************************************************************************/
unsigned char sdReturn;


void Sdinit()
{
	sdReturn = SD_Init();
	switch (sdReturn)
	{
	case 0:
		printf("No Err!\r\n");
		break;
	case  1:
		printf("timeout!\r\n");
		break;
	case 99:
		printf("other!\r\n");
		break;
	default:
		break;
	}
}


void main()
{
	while (1)
	{
		Sdinit();
		DELAY_MS(1000);
	}
}



/*
void main()
{

	FIL     fdst;   //�ļ�
	FATFS   fs;     //�ļ�ϵͳ

	uint32 size, sizetmp;
	int res;
	char *str = "��л��ѡ�� ɽ��Kinetis������ ��^_^\nɽ���ѧ123��̳:vcan123.com";
	uint8 buff[BUFF_SIZE];

	memset(buff, 0, BUFF_SIZE);

	f_mount(0, &fs);                                                               //�����ļ�ϵͳ

	//��ʼ�� SD�� �� f_open ��ִ��,Ŀǰ����ֻ֧�ִ�һ���ļ�(�� _FS_SHARE ����)��Ƶ�����ļ�������CPU��Դ
	res = f_open(&fdst, "0:/FireDemo.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);  //���ļ������û�оʹ���������д��

	if (res == FR_DISK_ERR)
	{
		printf("\nû����SD��??\n");
		return;
	}
	else if (res == FR_OK)
	{
		printf("\n�ļ��򿪳ɹ� \n");
	}
	else
	{
		printf("\n����ֵ�쳣%d",res);
		return;
	}

	printf("\n�ַ�������Ϊ:%d", strlen(str));

	f_puts(str, &fdst);                     //���ļ���д���ַ���

	f_sync(&fdst);                          //�ղ�д�������ݣ�ʵ�������ݲ�û�������д�룬��Ҫ���ô˺���ͬ�����߹ر��ļ����Ż�����д��

	size = f_size(&fdst);                   //��ȡ�ļ��Ĵ�С

	printf("\n�ļ���СΪ��%d \n", size);  //���ڴ�ӡ�ļ��Ĵ�С

	if (size > BUFF_SIZE)size = BUFF_SIZE;   //��ֹ���

	f_lseek(&fdst, 0);                      //��ָ��ָ���ļ�����
	f_read(&fdst, buff, size, (uint8*)&sizetmp);   //��ȡ

	printf("�ļ�����Ϊ��\n%s", (char const *)buff);

	f_close(&fdst);                         //�ر��ļ�

}*/