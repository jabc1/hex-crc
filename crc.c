#include "stdio.h"
/*
Hex�ļ��ǿ�����¼��MCU�У���MCUִ�е�һ���ļ���ʽ������ü��±��򿪿ɷ��֣�
�����ļ�����Ϊ��λ��ÿ����ð�ſ�ͷ������ȫ��Ϊ16�����루��ASCII����ʽ��ʾ����
Hex�ļ����԰������µķ�ʽ���в�����������е����ݣ�
���� ��:1000080080318B1E0828092820280B1D0C280D2854��
���Ա�������0x10 0x00 0x08 0x00 0x80 0x31 0x8B 0x1E 0x08 0x28 0x09 0x28 0x20 0x28 0x0B 0x1D 0x0C 0x28 0x0D 0x28 0x54��
��һ���ֽ� 0x10��ʾ�������ݵĳ��ȣ�
�ڶ������ֽ� 0x00 0x08��ʾ�������ݵ���ʼ��ַ��
�����ֽ� 0x00��ʾ�������ͣ����������У�0x00��0x01��0x02��0x03��0x04��0x05��
'00' Data Rrecord��������¼���ݣ�HEX�ļ��Ĵ󲿷ּ�¼�������ݼ�¼
'01' End of File Record: ������ʶ�ļ������������ļ�����󣬱�ʶHEX�ļ��Ľ�β
'02' Extended Segment Address Record: ������ʶ��չ�ε�ַ�ļ�¼
'03' Start Segment Address Record:��ʼ�ε�ַ��¼
'04' Extended Linear Address Record: ������ʶ��չ���Ե�ַ�ļ�¼
'05' Start Linear Address Record:��ʼ���Ե�ַ��¼
Ȼ�������ݣ����һ���ֽ� 0x54ΪУ��͡�
У��͵��㷨Ϊ������0x54ǰ����16��������ۼӺ�(���ƽ�λ)������� = 0x100 - �ۼӺ�
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
	char hex[]=":1000080080318B1E0828092820280B1D0C280D28";//:1000080080318B1E0828092820280B1D0C280D2854--->����һ��������hex���ݣ��������crc�պ����
	AnalyseHEX(hex,sizeof(hex));
}