// C++test1.cpp : 定义控制台应用程序的入口点。
//
#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <direct.h>
#include"string.h"

char * Ch_path(char ch[40]);
struct Wuyuan * Creat(char name[40]);
struct Wuyuan * ComparePcap(char name[40]);
char * Itoa_name();
char * Ch_path(char ch[40]);
void AnalyPcap();
void TCP(struct Wuyuan *p);
void Butten1();
char *Get_name(char p1[300]);
void Butten2();
void Butten3();
void Butten4();

typedef int _Int16;
typedef unsigned long  _Int32;

FILE * pfile;
char ch_path[260] = "";
long Filelen = 0, flen = 0, n_pcap = 0;

struct TCPhead
{
	//数据bao在总文件中位置
	_Int32 f_size;
	//抓包长度
	_Int32 cap_len;
	//tcp  ip头长度
	_Int16 iphdr_len;
	_Int16 tcphdr_len;
	_Int16 s_port;
	_Int16 d_port;
	//tcp序号
	_Int32 tcpseq;
	//tcp确认号
	_Int32 tcpack;
	//控制字段CTL
	_Int16 CTL;
	struct TCPhead  *next;
};
struct Wuyuan
{
	//包个数
	_Int32 num;
	//协议
	_Int16 protocol;
	_Int32 caplen;
	_Int16 s_port;
	_Int16 d_port;
	char wu_name[40];
	char path[300];
	struct TCPhead *TCPhead;
	struct TCPhead *tcp_head;
	struct Wuyuan *next;
}*wu_head = NULL, *wu_p = NULL;

char * Ch_path(char ch[40])
{
	static char ch_name[300];
	memset(ch_name, 0, 300);
	strcat(ch_name, ch_path);
	strcat(ch_name, "\\");
	strcat(ch_name, ch);
	strcat(ch_name, ".pcap");
	return ch_name;
}
struct Wuyuan * Creat(char name[40])
{

	int i = 0, q = 0, a[4] = { 0 };
	long caplen = 0;
	FILE *fp;
	struct Wuyuan *pw = NULL, *p = NULL;
	p = (struct Wuyuan *)malloc(sizeof(struct Wuyuan));
	memset(p, 0, sizeof(struct Wuyuan));

	fseek(pfile, flen + 8, 0);
	fread(&(p->caplen), 4, 1, pfile);
	fseek(pfile, flen + 39, 0);
	fread(&(p->protocol), 1, 1, pfile);

	fseek(pfile, flen + 50, 0);
	for (i = 0; i < 4; i++)
		fread(&a[i], 1, 1, pfile);
	p->s_port = (a[0] << 8) + a[1];
	p->d_port = (a[2] << 8) + a[3];
	strcpy((p->path), Ch_path(name));
	strcpy(p->wu_name, name);

	if (n_pcap == 0)
		wu_head = p;
	else
		wu_p->next = p;
	wu_p = p;
	wu_p->next = NULL;

	n_pcap++;
	return p;
}
struct Wuyuan * ComparePcap(char name[40])
{
	struct Wuyuan *P = NULL;
	P = wu_head;
	while (P != NULL)
	{
		if (strcmp(P->wu_name, name) == 0)
			return P;
		else
			P = P->next;
	}
	return P;
}
//五元组转换成字符
char * Itoa_name()
{
	int i, b[13] = { 0 }, a[13] = { 0 };
	_Int32 s_ip = 0, d_ip = 0;
	char ch[3] = "";
	static char ch_ip[40];
	memset(ch_ip, 0, 40);

	fseek(pfile, flen + 39, 0);
	fread(&a[0], 1, 1, pfile);
	fseek(pfile, flen + 42, 0);
	for (i = 1; i < 13; i++)
	{
		fread(&a[i], 1, 1, pfile);
		b[i] = a[i];
	}
	s_ip = (a[1] << 24) + (a[2] << 16) + (a[3] << 8) + a[4];
	d_ip = (a[5] << 24) + (a[6] << 16) + (a[7] << 8) + a[8];
	//输出
	/*printf("\n");
	for (i = 0; i < 13; i++)
	printf("%0*x ", 2, a[i]);*/
	if (s_ip < d_ip)
	{
		a[5] = b[9];
		a[6] = b[10];
		for (i = 7; i < 11; i++)
			a[i] = b[i - 2];
	}
	else
	{
		for (i = 1; i < 5; i++)
			a[i] = b[i + 4];
		a[5] = b[11];
		a[6] = b[12];
		for (i = 7; i < 11; i++)
			a[i] = b[i - 6];
		a[11] = b[9];
		a[12] = b[10];
	}
	if (a[0] == 6)
		strcat(ch_ip, "TCP");
	else if (a[0] == 17)
		strcat(ch_ip, "UDP");
	else
		strcat(ch_ip, "UNK");

	for (i = 1; i < 13; i++)
	{
		itoa(a[i], ch, 16);
		if (ch[1] == '\0')
		{
			ch[1] = ch[0];
			ch[0] = '0';
		}
		strcat(ch_ip, ch);
	}
	return ch_ip;
}

void AnalyPcap()
{
	_Int16   proper = 0, i = 0, a[4] = { 0 };
	_Int32 caplen = 0;
	char wu_name[40] = "0";
	struct Wuyuan  *p = NULL;

	fseek(pfile, flen + 39, 0);
	fread(&proper, 1, 1, pfile);
	fseek(pfile, flen + 8, 0);
	fread(&caplen, 4, 1, pfile);

	strcpy(wu_name, Itoa_name());
	if (proper == 17)
		Creat(wu_name);
	else
	{
		p = ComparePcap(wu_name);
		if (p == NULL)
			p = Creat(wu_name);
		p->TCPhead = (struct TCPhead *)malloc(sizeof(struct TCPhead));
		memset(p->TCPhead, 0, sizeof(struct TCPhead));
		p->TCPhead->cap_len = caplen;
		p->TCPhead->s_port = p->s_port;
		p->TCPhead->d_port = p->d_port;
		TCP(p);
	}

	flen = flen + 16 + caplen;
}
void TCP(struct Wuyuan *P)
{
	struct TCPhead *p1 = NULL, *p2 = NULL, *p = NULL;
	int i = 0, a[10] = { 0 };
	long long b1 = 0, b2 = 0;
	p = P->TCPhead;
	P->num++;
	fseek(pfile, flen + 30, 0);
	fread(&i, 1, 1, pfile);
	p->iphdr_len = 4 * (i & 15);
	fseek(pfile, flen + 34 + p->iphdr_len, 0);
	for (i = 0; i < 10; i++)
		fread(&a[i], 1, 1, pfile);
	p->tcpseq = (a[0] << 24) + (a[1] << 16) + (a[2] << 8) + a[3];
	p->tcpack = (a[4] << 24) + (a[5] << 16) + (a[6] << 8) + a[7];
	p->f_size = flen;
	p->tcphdr_len = (a[8] >> 4) * 4;
	p->CTL = a[9] & 31;
	if (P->num == 1)
	{
		p->next = NULL;
		P->tcp_head = p;
	}
	else
	{
		p1 = P->tcp_head;
		b1 = (long long)p->tcpseq + (long long)p->tcpack;
		b2 = (long long)p1->tcpseq + (long long)p1->tcpack;
		if (b1 < b2)
		{
			P->tcp_head = p;
			p->next = p1;
		}
		else
		{
			while (p1->next != NULL)
			{
				p2 = p1->next;
				b1 = (long long)p->tcpseq + (long long)p->tcpack;
				b2 = (long long)p2->tcpseq + (long long)p2->tcpack;
				if (b1 < b2)
				{
					p1->next = p;
					p->next = p2;
					break;
				}
				else
					p1 = p2;
			}
			if (p1->next == NULL)
			{
				p1->next = p;
				p->next = NULL;
			}
		}
	}
}

void Butten1()
{
	FILE *fp, *fp1, *fp2;
	_Int32 i = 0;
	_Int16   q = 0;
	struct TCPhead *tp;
	char txt_path[300] = "0";

	strcpy(txt_path, ch_path);
	strcat(txt_path, "\\result1.txt");
	fp1 = fopen(txt_path, "w");
	wu_p = wu_head;
	while (wu_p != 0)
	{



		if (wu_p->protocol == 17)
		{
			fprintf(fp1, "%s.pcap\r\n", wu_p->wu_name);
			fp = fopen(wu_p->path, "wb");
			fseek(pfile, flen, 0);
			for (i = 0; i < wu_p->caplen + 16; i++)
			{
				fread(&q, 1, 1, pfile);
				fwrite(&q, 1, 1, fp);
			}
			fclose(fp);
		}

		if (wu_p->protocol == 6)
		{
			fprintf(fp1, "%s_0.pcap\r\n", wu_p->wu_name);
			fp = fopen(wu_p->path, "wb");
			tp = wu_p->tcp_head;
			while (tp != NULL)
			{

				fseek(pfile, tp->f_size, 0);
				for (i = 0; i < tp->cap_len + 16; i++)
				{
					fread(&q, 1, 1, pfile);
					fwrite(&q, 1, 1, fp);
				}
				tp = tp->next;
			}
			fclose(fp);
		}
		wu_p = wu_p->next;
	}
	fclose(fp1);
}
char *Get_name(char p1[300])
{
	_Int16 i = 0, j = 0, num1 = 0;
	for (i = 0, j = 0, num1 = 0; i < 300 && p1[i] != '\0'; i++, j++)
	{
		p1[j] = p1[i];
		if (p1[j] == ' '&&num1<2)
		{
			num1++;
			if (num1 == 2)
			{
				p1[j] = '\0';
				break;
			}
		}
		if (p1[j] == '/' || p1[j] == '\\')
			j = 3;
	}
	for (j = 0; j < 300 && p1[j] != '\0'; j++)
	{
		if (p1[j] == '?' || p1[j] == '\n' || p1[j] == ':' || p1[j] == '%' || p1[j] == ',')
		{
			p1[j] = '\0';
			break;
		}

	}
	for (j = 0; j < 300 && p1[j] != '\0'; j++)
	if (p1[j] == '.')
	{
		if (j < 80)
			break;
		else
		{
			for (j = 4; j <28; j++, i++)
				p1[j] = p1[i - 20];
			p1[28] = '\0';
			break;
		}
	}
	return p1;
}
void Butten2()
{
	FILE *fp, *fp1;
	_Int32 i = 0, q = 0, j = 0;
	_Int16  num1 = 0, num2 = 0, p[4] = { 0 };
	struct TCPhead *tp, *tp_head = NULL;
	char txt_path[400] = "0", p1[300] = "0", p2[4] = "0";

	strcpy(txt_path, ch_path);
	strcat(txt_path, "\\result2.txt");
	fp1 = fopen(txt_path, "w");

	wu_p = wu_head;
	while (wu_p != 0)
	{

		if (wu_p->protocol == 6 && (wu_p->d_port == 80 || wu_p->s_port == 80))
		{
			tp = wu_p->tcp_head;
			while (tp != NULL)
			{
				fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
				fread(p1, 300, 1, pfile);
				if (p1[0] == 'G'&&p1[1] == 'E'&&p1[2] == 'T')
				{
					tp_head = tp;
					strcpy(p1, Get_name(p1));

					for (j = 0, p1[100] = '\0'; j < 100 && p1[j] != '\0'; j++)
					{
						if (p1[j] == '.')
							p1[j] = '_';

					}
					strcpy(txt_path, ch_path);
					strcat(txt_path, "/");
					strcat(txt_path, p1);
					strcat(txt_path, ".txt");
					fp = fopen(txt_path, "wb");


					if (fp != NULL)
					{
						fprintf(fp1, "%s.pcap -> %s.txt\r\n", wu_p->wu_name, p1);
						num2 = 0;
						tp = tp_head;
						while (tp != NULL)
						{
							fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
							for (i = 0; i < tp->cap_len - tp->tcphdr_len - 34; i++)
							{
								fread(&p[3], 1, 1, pfile);
								fwrite(&p[3], 1, 1, fp);
								if (num2 < 2)
								{

									if (p[3] == 10 && p[2] == 13 && p[1] == 10 && p[0] == 13)
										num2++;
									p[0] = p[1];
									p[1] = p[2];
									p[2] = p[3];
									if (num2 == 2)
										fputs("\r\n\r\n\r\n", fp);
								}

							}
							tp = tp->next;
							if (tp == NULL)
								break;
							fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
							fread(p1, 3, 1, pfile);
							if (p1[0] == 'G'&&p1[1] == 'E'&&p1[2] == 'T')
								break;
						}
						fclose(fp);
					}
					else
						tp = tp->next;
				}
				else
					tp = tp->next;
			}
		}
		wu_p = wu_p->next;
	}
	fclose(fp1);
}

void Butten3()
{
	FILE *fp, *fp1;
	_Int32 i = 0, q = 0, j = 0;
	_Int16  num1 = 0, num2 = 0, p[4] = { 0 };
	struct TCPhead *tp, *tp_head = NULL;
	char txt_path[400] = "0", p1[300] = "0", p2[300] = "0";

	strcpy(txt_path, ch_path);
	strcat(txt_path, "/result3.txt");
	fp1 = fopen(txt_path, "wb");

	wu_p = wu_head;
	while (wu_p != 0)
	{

		if (wu_p->protocol == 6 && (wu_p->d_port == 80 || wu_p->s_port == 80))
		{
			tp = wu_p->tcp_head;
			while (tp != NULL)
			{
				fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
				fread(p1, 300, 1, pfile);
				if (p1[0] == 'G'&&p1[1] == 'E'&&p1[2] == 'T')
				{
					tp_head = tp;
					strcpy(p1, Get_name(p1));

					for (j = 0, p1[100] = '\0'; j < 100 && p1[j] != '\0'; j++)
					{
						p2[j] = p1[j + 4];
						if (p1[j] == '.')
							p1[j] = '_';
					}
					strcpy(txt_path, ch_path);
					strcat(txt_path, "/");
					strcat(txt_path, p2);
					fp = fopen(txt_path, "wb");

					if (fp != NULL)
					{
						fprintf(fp1, "%s.txt->%s \r\n", p1, p2);
						num2 = 0;
						tp = tp_head;
						while (tp != NULL)
						{
							fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
							for (i = 0; i < tp->cap_len - tp->tcphdr_len - 34; i++)
							{
								fread(&p[3], 1, 1, pfile);
								if (num2>1)
									fwrite(&p[3], 1, 1, fp);
								if (num2 < 2)
								{
									if (p[3] == 10 && p[2] == 13 && p[1] == 10 && p[0] == 13)
										num2++;
									p[0] = p[1];
									p[1] = p[2];
									p[2] = p[3];
								}

							}
							tp = tp->next;
							if (tp == NULL)
								break;
							fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
							fread(p1, 3, 1, pfile);
							if (p1[0] == 'G'&&p1[1] == 'E'&&p1[2] == 'T')
								break;
						}
						fclose(fp);
					}
					else
						tp = tp->next;
				}
				else
					tp = tp->next;
			}
		}
		wu_p = wu_p->next;
	}
	fclose(fp1);
}

void Butten4()
{
	FILE  *fp1;
	_Int32 i = 0, q = 0, j = 0;
	_Int16  num1 = 0;
	struct TCPhead *tp;

	char txt_path[400] = "0", p[1000] = "0", p1[8] = "0", p2[100] = "0";
	strcpy(txt_path, ch_path);
	strcat(txt_path, "\\result4.txt");
	fp1 = fopen(txt_path, "w");
	wu_p = wu_head;
	while (wu_p != 0)
	{

		if (wu_p->protocol == 6 && (wu_p->d_port == 80 || wu_p->s_port == 80))
		{
			tp = wu_p->tcp_head;
			while (tp != NULL)
			{
				fseek(pfile, tp->f_size + 50 + tp->tcphdr_len, 0);
				fread(p, 1000, 1, pfile);
				if (p[0] == 'G'&&p[1] == 'E'&&p[2] == 'T')
				{

					for (i = 0, p1[0] = '\0'; i < 1000 && p[i] != '\0'; i++)
					{
						if (p[i] == '\n')
							memcpy(p1, p + i + 1, 7 * sizeof(char));
						if (strcmp(p1, "Referer") == 0)
						{
							memcpy(p2, p + i + 10, 100 * sizeof(char));
							break;
						}
					}
					
					for (i = 0, j = 0, num1 = 0; i<100 && p2[i] != '\0'; i++)
					{
						p2[j] = p2[i];
						if (p2[i] == '/' || p2[i] == '\\')
							j = -1;
						if (p2[i] == '\n' || p2[i] == ' ')
						{
							p2[j] = '\0';
							break;
						}
						j++;
					}
					
					for (j = 0; j < 100 && p2[j] != '\0'; j++)
					if (p2[j] == '?' || p2[j] == '\n' || p2[j] == ':')
					{
						p2[j] = '\0';
						break;
					}
					strcpy(p, Get_name(p));
					for (j = 0; j < 100 && p[j] != '\0'; j++)
						p[j] = p[j + 4];
					if (p != NULL&&p2 != NULL)
						fprintf(fp1, "%s <- %s\n", p2, p);
					tp = tp->next;
				}
				else
					tp = tp->next;
			}
		}
		wu_p = wu_p->next;
	}
	fclose(fp1);
}

int Filepath(char str[260], char str1[260])
{
	sprintf(ch_path, "%s", str1);
	pfile = fopen(str, "rb");
	if (pfile == 0)
		return 0;
	fseek(pfile, 0, SEEK_END);
	Filelen = ftell(pfile);
	flen = 24;
	while (flen < Filelen)
	{
		AnalyPcap();
	}
	return 1;
}
