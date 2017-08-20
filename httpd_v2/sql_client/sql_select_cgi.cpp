#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql_api.h"

#define SIZE 1024

static void select_data(char* data)
{
	//提取参数
	char* arr[5];
	int i=0;
	char* start = data;
	while(*start)
	{
		if(*start == '=')
		{
			arr[i] = start+1;
			i++;
		}
		else if(*start == '&')
		{
			*start = '\0';
		}
		else
		{}
		start++;
	}
	arr[i] = NULL;
	
	string str;
	int j=0;
	for(; j<i-1; j++)
	{
		if(j == 2)
		{
			str += arr[j];
//			str += ",";
			continue;
		}
//		str += "\'";
		str += arr[j];
//		str += "\'";
		if(j == i-1)
			break;
//		str += ",";
		cout<<endl;		
	}

	cout<<str.c_str()<<endl;
	mysqlapi s;
	s.sql_connect();
	s.sql_select(str);
}

int main()
{
	//获取环境变量
	//GET->query_string    POST->CONTENT-LENGTH
	char method[SIZE];
	char content_len[SIZE];
	char data[SIZE];

	if( getenv("METHOD") )
	{
		strcpy(method, getenv("METHOD"));
	}
	else
	{
		cout<<"METHOD is no exist!"<<endl;
		return 1;
	}

	if(strcasecmp(method,"GET") == 0)
	{
		if( getenv("QUERY-STRING"))
		{
			strcpy(data, getenv("QUERY-STRING"));
		}
		else
		{
			cout<<"QUERY-STRING is not exist!"<<endl;
		}
	}
	else
	{
		//是POST方法就从内存读取content_length个字符------参数
		int i=0;
		strcpy(content_len, getenv("CONTENT-LENGTH"));
		int len=atoi(content_len);
		char ch='\0';
		for(; i<len; i++)
		{
			read(0, &ch, 1);
			data[i] = ch;
		}
		data[i] = '\0';
	}

	select_data(data);

	return 0;
}

