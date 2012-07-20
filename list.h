#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
/*list的node结构定义*/
typedef struct _listnode_t{
    struct _listnode_t *next;
    union {//用union更加好扩展
          void* data;
     };
}listnode_t;

/*list的结构定义*/
typedef struct _list_t{
    size_t size;
    listnode_t* head;
}list_t;

extern list_t* list_create();

extern void list_remove_all(list_t* list);

extern void list_destory(list_t *list);

extern size_t list_size(const list_t* list);

extern void list_add(list_t* list,listnode_t* listnode);

extern listnode_t* list_remove_node(list_t* list,int index);

extern listnode_t* listnode_create(void* node_data);

extern listnode_t* list_getnode(list_t* list,int index);
