#include "common.h"
#include "list.h"


typedef struct _hashmap_element_t{
    char* key;
    char* value;
    struct  _hashmap_element_t* next; 
} hashmap_e_t;

typedef struct _hashmap_t{
    size_t size;
    mp_e_t ** mp_element;
}hashmap_t;


extern hashmap_e_t* hashmap_create();

extern void hashmap_destroy(hashmap_t* mp);
