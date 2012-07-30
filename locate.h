#include "common.h"
#include "list.h"
#include "hashmap.h"
#define READ_BUFFER_SIZE 8192

struct log
{
	long time;//提交时间
	char *key;//基站或者wifi的key
	int x,y,pt;//此条日志提交的gps坐标，和精度
	int type;//类型，wifi为0，主基站为1，其他基站为2
};

