/**
*author hepan
*用于接受标准输入的日志，然后得到提交的数据，解析为各行都是有效数据的格式，格式如下
*时间 基站（wifi）号  x坐标  y坐标 pt  获取类型
*/
#include "locate.h"

//返回日志来源，包含“&_x=”的日志判定为来源于定位，加上‘&’是因为cormorant日志里有些日志
//包含“lu=”的即判定为cormorant行为日志来的信息
int getsource( char* line ) 
{
	char *indicator = line;
	while ( *indicator != '\0' ) 
	{	
		//来自tk的日志
		if( *indicator == '&' && *( indicator + 1 ) == '_' && 
			*( indicator + 2 ) == 'x' && * ( indicator + 3 ) == '=' )
			return 1; 
		//来自corm的日志
		if( *indicator == 'l' && *( indicator + 1 ) == 'u' && *( indicator + 2 ) == '=' )
			return 2;
		indicator++;
	}
	return 0;
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
long gettime( char* line )
{
	char *timeinfo = (char *)malloc(24);
	memcpy(timeinfo,line,23);
    *(timeinfo+23) = '\0';
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

void dealpara( struct log* log, char* key, char* value )
{
	if ( strcmp( key, "wifi_mac[]" ) == 0 )
    {
		struct list_e* e = listnode_create( value );
		list_add( log->wifikeylist, e);
        free(key);
    } else if ( strcmp( key, "wifi_ss[]" ) == 0 )
            {
				struct list_e* e = listnode_create( value );
				list_add( log->wifisslist, e);
				free( key );
            } else if ( strcmp( key, "n8b_lac[]" ) == 0 )
                    {
						struct list_e* e = listnode_create( value );
						list_add( log->n8blaclist, e );
						free( key );
                    } else if ( strcmp( key, "n8b_ci[]" ) == 0 )
                            {
                                struct list_e* e = listnode_create( value );
                                list_add( log->n8bcilist, e);
                                free( key );
                            }else if ( strcmp( key, "n8b_ss[]" ) == 0 )
                                   {
                                        struct list_e* e = listnode_create( value );
                                        list_add( log->n8bsslist, e);
                                        free( key );
                                   }else{
											free( key );
											free( value );
											//hmap_put( log->paramp, key, strlen(key), value );
                                        }
}

struct log* tklog( char *line )
{
	//初始化log结构
	struct log* log = ( struct log* ) malloc ( sizeof( struct log ) );
	log->paramp = hmap_create();
	log->wifikeylist = list_create();
	log->wifisslist = list_create();
	log->n8blaclist = list_create();
	log->n8bcilist = list_create();
	log->n8bsslist = list_create();
	//获取时间
	log->time = gettime( line );
	//获取日志中大括号内的参数
	//用start和end两个指针查找key和value
	char *start = line + 32;//略过时间的部分
	while ( *(start-1) != '{' ) start ++;
	char *end = start;
	char *key,*value;
	int haskey = 0;
	while ( TRUE )
	{
		if ( *end == '=')
        {
			//某些特殊情况洗下，参数的值中有=
			if( *(start - 1) == '=' )
			{
				end++;
				continue;
			}
            int len = end - start;
            key = ( char* )malloc ( len + 1 );
            memcpy( key , start , len );
            * (key + len) = '\0';
            start = ++end;
			haskey = 1;
            continue;
        }
		if ( *end == '&')
        {
			//某些特殊情况洗下，参数的值中有&
			if( haskey == 0)
			{
				start = ++ end;
				continue;
			}
            int len = end -start;
            value = ( char* ) malloc ( len + 1 );
            memcpy( value , start , len );
            * (value + len) = '\0';
			dealpara( log, key, value );
			haskey = 0;
			//getchar();
            start = ++ end;
            continue;
        }
		 if( *end == '}' )
        {
            int len = end -start;
            value = ( char * ) malloc ( len + 1 );
            memcpy( value , start , len );
            * (value + len) = '\0';
            dealpara( log, key, value );
            break;
        }
		end++;
		
	}
	return log;

}


struct log* getlog( char *line, int source )
{	
	if( source == 1 )
		return tklog( line );
	if( source == 2 ) 
		return corlog( line );
	return NULL;
}

void deallog( struct log *log )
{
	//hmap_print( log-> paramp);

}

void freelog( struct log *log )
{
	hmap_destroy( log->paramp );
	list_destroy( log->wifikeylist );
	list_destroy( log->wifisslist );
	list_destroy( log->n8blaclist );
	list_destroy( log->n8bcilist );
	list_destroy( log->n8bsslist );
	free( log );
	log == NULL;
}

char* getnowtime()
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return asctime(timeinfo);
}

void main(int argc,char *argv[])
{	int logtype = 0;
	printf("read log start:%s",getnowtime());
	long int line_num = 0,log_num = 0;
	char *line = ( char * )malloc(READ_BUFFER_SIZE);
//	FILE *fp = fopen("tk_locate_log_optimus_test","r+");
//	FILE *fp = fopen("sample","r+");
	while( fgets( line, READ_BUFFER_SIZE, stdin ) != NULL )
	//while( fgets( line, READ_BUFFER_SIZE, fp ) != NULL )
	{
		
		line_num++;
		//printf("%ld    ",line_num);
		int source = getsource( line );
		if(  source > 0 )
		{
			printf("%s",line);
		struct log* log = getlog( line, source );
			if( log != NULL )
			{	
				log_num++;
				deallog(log);
				freelog(log);
			}
		}
	} 
	//fclose(fp);
	free(line);
	printf("read log   end:%s",getnowtime());
	printf("read lines : %ld\n",line_num);
	printf("read logs : %ld\n",log_num);
}
