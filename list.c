/*
 *author hepan
 * 实现list的基本功能，基本数据机构声明在list.h里
 * 
 */

#include "list.h"
//分配空间，创建一个空的list
list_t* list_create(){
  list_t* list =(list_t *)malloc(sizeof(list_t));
  list->size = 0;
  list->head = NULL;
  return list;
}
//从list中删除一个node，并返回这个node
listnode_t* list_remove_node(list_t* list,int index){
   listnode_t* node = NULL;
   if(list->size > 0){//如果list不为空,则删除
     assert(index < list->size);
     int i = 0;
     listnode_t* pos = list->head;
     //将指针知道要移除的node的前一个node, 若要删除的是head，则pos也指向第一个
     for(;i < index - 1 && pos->next != NULL ; i++)
       pos = pos->next;
     if(index == 0){//删除head
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
   }
   return node;
}
//往list尾添加一个node
void list_add(list_t* list,listnode_t * node){
    listnode_t* pos = list->head;
    if(pos == NULL)
       list->head = node;
    else{
        while(pos->next != NULL)
            pos = pos->next;
       pos->next = node;
    }
    list->size ++;
}

listnode_t* listnode_create(void* data){
    listnode_t* node = (listnode_t *) malloc(sizeof(listnode_t));
    node->next = NULL;
    node->data = data;
    return node;
}

size_t list_size(const list_t* list){
    return list->size;
}

//销毁整个list
void list_destroy(list_t* list,listnode_t* n98){
    listnode_t* node;
    while(list->head){
        node = list->head;
        list->head = list->head->next;
//        printf("free:%d  %x\n",*(int *)node->data,node) ;
        free(node->data);
        free(node);
        list->size--;
        assert(list->size >= 0);
    }
//   free(n98);
//   free(n98->data);
// printf("free again:%d  %x\n",*(int *)(n98->data),n98) ;
   free(list);
}
//得到list某个index的元素,如果越界返回NULL
listnode_t* list_getnode(list_t* list,int index){
  if(index >= list->size || index < 0)
     return NULL;
  listnode_t* node = list->head;
  int i = 0;
  for(;i < index && node->next != NULL ; i++)
       node = node->next;
  return node;
}

