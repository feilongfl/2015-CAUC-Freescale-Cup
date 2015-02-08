/*!
*
* @file       main.c
* @brief      飞思卡尔主程序
* @author     飞龙
* @version    v0.1
* @date       2015-1-7
*/
/************************************************************************/
/* 文件包含                                                             */
/************************************************************************/
#include "main.h"
#include "sd_driver.h"
#define BUFF_SIZE   100
/************************************************************************/
/* 全局变量或结构体                                                     */
/************************************************************************/
uint32 Distance = 0;
/************************************************************************/
/*  外部引用函数                                                     */
/************************************************************************/
extern void UartHandler();
/************************************************************************/
/*                       主函数                                         */
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

	FIL     fdst;   //文件
	FATFS   fs;     //文件系统

	uint32 size, sizetmp;
	int res;
	char *str = "感谢您选用 山外Kinetis开发板 ！^_^\n山外初学123论坛:vcan123.com";
	uint8 buff[BUFF_SIZE];

	memset(buff, 0, BUFF_SIZE);

	f_mount(0, &fs);                                                               //挂载文件系统

	//初始化 SD卡 在 f_open 上执行,目前代码只支持打开一个文件(由 _FS_SHARE 配置)，频繁打开文件会消耗CPU资源
	res = f_open(&fdst, "0:/FireDemo.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);  //打开文件，如果没有就创建，带读写打开

	if (res == FR_DISK_ERR)
	{
		printf("\n没插入SD卡??\n");
		return;
	}
	else if (res == FR_OK)
	{
		printf("\n文件打开成功 \n");
	}
	else
	{
		printf("\n返回值异常%d",res);
		return;
	}

	printf("\n字符串长度为:%d", strlen(str));

	f_puts(str, &fdst);                     //往文件里写入字符串

	f_sync(&fdst);                          //刚才写入了数据，实际上数据并没真正完成写入，需要调用此函数同步或者关闭文件，才会真正写入

	size = f_size(&fdst);                   //获取文件的大小

	printf("\n文件大小为：%d \n", size);  //串口打印文件的大小

	if (size > BUFF_SIZE)size = BUFF_SIZE;   //防止溢出

	f_lseek(&fdst, 0);                      //把指针指向文件顶部
	f_read(&fdst, buff, size, (uint8*)&sizetmp);   //读取

	printf("文件内容为：\n%s", (char const *)buff);

	f_close(&fdst);                         //关闭文件

}*/