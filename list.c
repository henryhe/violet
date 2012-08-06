/*
 *author hepan
 * 实现list的基本功能，基本数据机构声明在list.h里
 * 
 */

#include "list.h"
//分配空间，创建一个空的list
struct list *list_create()
{
	struct list *list = ( struct list * )malloc( sizeof( struct list ) );
	list->size = 0;
	list->head = NULL;
	return list;
}
//从list中删除一个node，并返回这个node
struct list_e *list_delete( struct list *list, int index )
{
	struct list_e * node = NULL;
    if( list->size <= 0 )
		return NULL;
	assert(index < list->size);
	struct list_e *pos = list->head;
	int i;
	//将指针知道要移除的node的前一个node, 若要删除的是head，则pos也指向第一个
	for( i=0; i < index - 1 && pos->next != NULL ; i++ )
		pos = pos->next;
	if( index == 0 )
	{//删除head
		node = pos;
		pos = pos->next;
		node->next = NULL;
		list->head = pos;
	}else{
		node = pos->next;
		pos->next = node->next;
		node->next = NULL;
	}
	list->size--;
	assert(list->size >= 0);
	return node;
}
//往list尾添加一个node
void list_add( struct list *list,struct list_e *node )
{
	struct list_e *pos = list->head;
	if( pos == NULL )
		list->head = node;
	else{
		while( pos->next != NULL )
			pos = pos->next;
		pos->next = node;
	}
	list->size ++;
}

struct list_e *listnode_create( void *data )
{
	struct list_e *node = ( struct list_e * )malloc( sizeof( struct list_e ) );
	node->next = NULL;
	node->data = data;
	return node;
}

size_t list_size( const struct list *list )
{
	return list->size;
}


void list_print( struct list* list )
{
	struct list_e* e = list->head;
    printf("list:");
	while ( e )
	{
		printf("%s ",(char *)e->data);
		e = e->next;
	}
	printf("\n");
}
//销毁整个list
void list_destroy( struct list *list ){
//	list_print( list );
	struct list_e *node;
	while ( list->head )
	{
		node = list->head;
		list->head = list->head->next;
		free(node->data);
		free(node);
		list->size--;
		assert(list->size >= 0);
	}
   free(list);
}

//得到list某个index的元素,如果越界返回NULL
struct list_e *list_get( struct list *list, int index )
{
	if(index >= list->size || index < 0)
		return NULL;
	struct list_e *node = list->head;
	int i;
	for( i=0; i < index && node->next != NULL; i++ )
		node = node->next;
	return node;
}



int test_main(){
	while(1){
		struct list* list = list_create();
		int i;
		for( i = 0; i < 10; i++)
		{
			char *p = (char *) malloc(10);
			strcpy(p,"123456789\0");
			struct list_e* e = listnode_create( p );
			list_add( list, e);
		}
		list_print( list );
		list_destroy( list );
	}


}
