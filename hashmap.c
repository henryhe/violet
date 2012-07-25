#include "hashmap.h"
//创建一个元素
struct hmap_e * hmap_e_create( char* key, void* value )
{
	struct hmap_e *e = ( struct hmap_e * )malloc(sizeof(struct hmap_e));
	e->key = key;
	e->value = value;
	e->next = NULL;
	return e;
}

struct hmap * hmap_create()
{
	struct hmap *mp = (struct hmap * ) malloc (sizeof(struct hmap));
	mp->size = 0;
	mp->em = (struct hmap_e ** )calloc(KEY_SIZE,sizeof(struct hmap_e * ));
}

void hmap_destroy( struct hmap *mp)
{
	int i;
	for( i = 0; i < KEY_SIZE; i++ )
	{
		mp->size -= hmap_key_destroy( mp->em[i] );
	}
	struct hmap_e **temp = mp->em;
	for( i = 0; i < KEY_SIZE; i++)
	{
		free(*temp++);
	}
	assert( mp->size == 0 );
	free( mp->em );
	free(mp);
}

//释放每个key下的element
int hmap_key_destroy( struct hmap_e *key )
{
	struct hmap_e *pos = key;
	struct hmap_e *next = key;
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
	return h%KEY_SIZE;
}

void hmap_put( struct hmap *mp, char *key, int key_len, void * value )
{
	assert(key && key_len>0);
	long hash = hash_string( key,key_len );
	//判断是否已经放入hashmap中，如果放入则替换内容
    struct hmap_e *e = mp->em[hash];
	while ( e != NULL)
	{
		if(strcmp( key, e->key ) == 0)
		{
			void* temp = e->value;
			e->value = value;
			if ( temp != value )
				free( temp );
			return;
		}
		e = e->next;
	}
    //没有放入，则添加
	e = hmap_e_create( key, value );
	//把新元素放到每个key队列的头部
	e->next = mp->em[hash];
	mp->em[hash] = e;
	mp->size++;
}

void* hmap_get( struct hmap *mp, char *key, int key_len )
{
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

void print( struct hmap *mp )
{
	int i;
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



int main(){
   
}
