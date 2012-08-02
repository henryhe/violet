#include "common.h"
/*list的node结构定义*/
#ifndef list_include_flag
#define list_include_flag 
struct list_e{
	struct list_e *next;
	union 
		{//用union更加好扩展
		void *data;
		};
};

/*list的结构定义*/
struct list{
    size_t size;
    struct list_e *head;
};
# endif

extern struct list* list_create();

extern void list_clear( struct list *list );

extern void list_destory( struct list *list );

extern size_t list_size( const struct list *list );

extern void list_add( struct list *list,struct list_e *e );

extern struct list_e* list_delete( struct list *list, int index );

extern struct list_e* listnode_create( void *data );

extern struct list_e* list_get( struct list *list, int index );
