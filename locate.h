#include "common.h"
#include "list.h"
#include "hashmap.h"
#define READ_BUFFER_SIZE 1024*21*5

struct log
{//一条log的结构
	long time;
	struct hmap* paramp;//基本参数的map
    struct list* wifikeylist;//wifi mac地址的list
	struct list* wifisslist;//sifi 信号的list和key一一对应
	struct list* n8blaclist;//基站laclist
	struct list* n8bcilist;//基站ci的list
	struct list* n8bsslist;//基站信号的list
};


struct record
{//一条有效的记录
	long time;//提交时间
	char* key;//基站或者wifi的key
	int x,y,pt;//此条日志提交的gps坐标，和精度
	int type;//类型，wifi为0，主基站为1，其他基站为2
	int avai;
	char* e;
};

