/**
 *author hepan
 *des 在list基础上实现hashmap，为了统一，要求所有key为char*类型，value不限制
 */
#include "common.h"
#include "list.h"

#ifndef hashmap_include_flag
#define hashmap_include_flag
typedef struct _hashmap_element_t{
    char* key;
    void* value;
    struct  _hashmap_element_t* next; 
} hashmap_e_t;

typedef struct _hashmap_t{
    size_t size;
    hashmap_e_t ** hashmap_em;
}hashmap_t;
#define KEY_SIZE 1024
#endif

extern hashmap_e_t* hashmap_e_create(char*key,void* value);

extern hashmap_t* hashmap_create();

extern void hashmap_destroy(hashmap_t* mp);
//释放一个key下的所有元素，并返回返回的元素数目
int hashmap_elementsbykey_destroy(hashmap_e_t* mp_e_bykey);

extern void hashmap_put(hashmap_t* mp, char *key,int key_len,void * value);

extern void* hashmap_get(hashmap_t* mp,char* key,int key_len);
