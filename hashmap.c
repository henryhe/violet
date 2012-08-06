#include "hashmap.h"
#include <stdlib.h>
//创建一个元素
struct hmap_e* hmap_e_create( char* key, void* value )
{
	struct hmap_e *e = ( struct hmap_e * )malloc( sizeof( struct hmap_e ) );
	e->key = key;
	e->value = value;
	e->next = NULL;
	return e;
}

struct hmap*  hmap_create()
{
	struct hmap* mp = (struct hmap * ) malloc ( sizeof( struct hmap ) );
	mp->size = 0;
	int i;
	for( i = 0; i < KEY_SIZE ; i++)
	{
		mp->em[i] = NULL;
	}
	return mp;
}

void hmap_print( struct hmap *mp )
{
	int i;
	printf("to print :\n");
	printf("map size :%d ", (int)mp->size );
	for( i = 0; i < KEY_SIZE; i++ )
	{
		struct hmap_e *e= mp->em[i];
		while( e )
		{
			printf("%s:%s ", e->key, (char *)e->value );
			e = e->next;
		}
	}
	
	printf("\n");
	
}

void hmap_destroy( struct hmap *mp)
{
//	hmap_print(mp);
	int i;
	for( i = 0; i < KEY_SIZE; i++ )
	{
		mp->size -= hmap_key_destroy( mp->em[i] );
	}
	assert( mp->size == 0 );
	free( mp );
}

//释放每个key下的element
int hmap_key_destroy( struct hmap_e *key )
{
	struct hmap_e *pos = key;
	struct hmap_e *next = pos;
	int count = 0;//计数器：返回free的元素个数
	while ( pos )
	{	
		next = pos->next;
		free( pos->key );
		free( pos->value );
		free( pos );
		count++;
		pos = next;
	}
	return count;
}

long hash_string( const char *key, int len )
{
	long h = 0;
	int i,off = 0;
	for( i = 0; i < len; i++ )
		h = 31*h + key[off++];
	if(	h < 0 ) 
		h = 0; 
	return h%KEY_SIZE;
}

struct hmap_e* hmap_get_e( struct hmap *mp, char *key )
{
	int key_len = strlen( key );
	assert(key && key_len>0);
	long hash = hash_string(key,key_len);
	struct hmap_e* e = mp->em[hash];
	while ( e )
	{
		if( strcmp( key, e->key ) == 0)
			return e;
        e = e->next;
	}
	return NULL;
}

void hmap_put( struct hmap *mp, char *key, int key_len, void * value )
{

	assert(key && key_len>0);
    long hash = hash_string( key,key_len );
//	printf(" put %s  %ld :%s \n " ,key,hash,(char *) value);
    //判断是否已经放入hashmap中，如果放入则替换内容
	struct hmap_e* e  = hmap_get_e( mp, key );
	if( e != NULL )
	{
		printf(" leak \n");
		if ( e->value != value )
		{
			free( key );
			free( e->value );
			e->value = value;
		}else{
			free( key );
			free( value );
		}
		return;
	}
    //没有放入，则添加
	e = hmap_e_create( key, value );
    //把新元素放到每个key队列的头部
    e->next = mp->em[hash];
    mp->em[hash] = e;
    mp->size++;
}

void* hmap_get( struct hmap *mp, char *key )
{
	int key_len = strlen( key );
	assert(key && key_len>0);
	long hash = hash_string(key,key_len);
	struct hmap_e *e = mp->em[hash];
	while ( e )
	{
		if( strcmp( key, e->key ) == 0)
			return e->value;
        e = e->next;
	}
	return NULL;
}

void ltest_main(){
	while( 1 )
	{
		struct hmap* mp = hmap_create();
		int i;
		for(i = 0; i<10;i++)
		{
			char *p = (char *) malloc(2);
			sprintf(p,"%d",2);
			printf("p:%s\n",p);
			char *q = (char *)malloc(8);
			strcpy(q,"abcdefg\0");
//			free(p);
//			free(q);
			hmap_put( mp , p , strlen(p), q);
			hmap_print( mp );
		}
		hmap_destroy(mp);
	}
}

