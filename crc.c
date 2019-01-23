#include "stdio.h"
/*
Hex文件是可以烧录到MCU中，被MCU执行的一种文件格式。如果用记事本打开可发现，
整个文件以行为单位，每行以冒号开头，内容全部为16进制码（以ASCII码形式显示）。
Hex文件可以按照如下的方式进行拆分来分析其中的内容：
例如 “:1000080080318B1E0828092820280B1D0C280D2854”
可以被看作“0x10 0x00 0x08 0x00 0x80 0x31 0x8B 0x1E 0x08 0x28 0x09 0x28 0x20 0x28 0x0B 0x1D 0x0C 0x28 0x0D 0x28 0x54”
第一个字节 0x10表示本行数据的长度；
第二、三字节 0x00 0x08表示本行数据的起始地址；
第四字节 0x00表示数据类型，数据类型有：0x00、0x01、0x02、0x03、0x04、0x05。
'00' Data Rrecord：用来记录数据，HEX文件的大部分记录都是数据记录
'01' End of File Record: 用来标识文件结束，放在文件的最后，标识HEX文件的结尾
'02' Extended Segment Address Record: 用来标识扩展段地址的记录
'03' Start Segment Address Record:开始段地址记录
'04' Extended Linear Address Record: 用来标识扩展线性地址的记录
'05' Start Linear Address Record:开始线性地址记录
然后是数据，最后一个字节 0x54为校验和。
校验和的算法为：计算0x54前所有16进制码的累加和(不计进位)，检验和 = 0x100 - 累加和
*/
unsigned char AnalyseHEX(char hex[],int len)
{
	unsigned char i=1;
	unsigned char data;
	int cc=0;
	char temp[2];
	do
	{
		temp[0] = hex[i++];
		temp[1] = hex[i++];
		sscanf(temp,"%x",&data);
		cc += data;
	} while (i<(len-2));
	cc%=256;
	cc=0x100-cc;
	temp[0] = hex[i++];
	temp[1] = hex[i++];
	sscanf(temp,"%x",&data);
	printf("cc=0x%02x\r\n",cc);
	return (cc==data)?1:0;
}

int main()
{
//	char hex[]="::020000040000FA";//:1000080080318B1E0828092820280B1D0C280D2854
	char hex[]=":1000080080318B1E0828092820280B1D0C280D28";//:1000080080318B1E0828092820280B1D0C280D2854--->这是一天完整的hex内容，计算出来crc刚好相等
	AnalyseHEX(hex,sizeof(hex));
}