/**
*author hepan
*用于接受标准输入的日志，然后得到提交的数据，解析为各行都是有效数据的格式，格式如下
*时间 基站（wifi）号  x坐标  y坐标 pt  获取类型
*/
#include "locate.h"

//仅仅过滤掉不是提交数据的日志
int isneeded( char* line ) 
{//过滤掉不是提交数据的日志,根据是否包含“_x=”
	char *indicator = line;
	while ( *indicator != '\0' ) 
	{
		if(*indicator == '_' && *(indicator+1) == 'x' && *(indicator + 2) == '=')
			return TRUE; 
	indicator++;
	}
	return FALSE;
}

struct log *corlog( char *line )
{

	printf("%s",line);
	return NULL;

}

//截取一个字符串的字串，转化为int
int getint( char* ori, int from , int to)
{	
    int n = to - from + 1;
	ori += from;
	char* temp = ( char* ) malloc ( n + 1 );
	memcpy( temp, ori, n);
	*( temp + n) = '\0';
	int result = atoi( temp );
	free ( temp );
	return result;
}

//将格式如2012-07-15 00:00:00,063的字符串转化为1900年到该时间的秒数
long gettime( char* timeinfo )
{
	struct tm t;
    t.tm_year = getint( timeinfo, 0, 3 ) - 1900 ;
	t.tm_mon  = getint( timeinfo, 5, 6 ) - 1;
	t.tm_mday  = getint( timeinfo, 8, 9 );
	t.tm_hour = getint( timeinfo, 11, 12 );
	t.tm_min  = getint( timeinfo, 14, 15 );
	t.tm_sec  = getint( timeinfo, 17, 18 );
	t.tm_isdst = 0;
	time_t timep = mktime( &t );
    return timep;
}

struct log *tklog( char *line )
{
	char *temp = (char *)malloc(24);
	memcpy(temp,line,23);
    *(temp+23) = '\0';
	long time = gettime( temp );
    printf("%s",line);
	return NULL;

}


struct log *getlog( char *line, int logtype )
{	
	if(logtype == 0)
		return tklog( line );
	if(logtype == 1)
		return corlog( line );
	return NULL;
}

void deallog( struct log *log )
{


}


void freelog( struct log *log ){
	free( log->key );
    free( log );
}

void main(int argc,char *argv[])
{	int logtype = 0;
	time_t rawtime_start;
	struct tm* timeinfo;
	time(&rawtime_start);
	timeinfo = localtime(&rawtime_start);
	printf("read log start:%s",asctime(timeinfo));
	long int line_num = 0;
	char *line = ( char * )malloc(READ_BUFFER_SIZE);
	while( fgets( line, READ_BUFFER_SIZE, stdin ) != NULL )
	{
		line_num++;
		struct log *log;
		if( isneeded( line ) == TRUE )
		{
			log = getlog(line,logtype);
			if( log != NULL )
			{
				deallog(log);
				freelog(log);
			}
		}
	}  
	free(line);
	time_t rawtime_end;
	time(&rawtime_end);
	timeinfo = localtime(&rawtime_end);
	printf("read log   end:%s",asctime(timeinfo));
	printf("read lines : %ld\n",line_num);
}
