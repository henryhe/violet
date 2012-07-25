#include "hashmap.h"

hashmap_e_t* hashmap_e_create(char* key,void* value){
    hashmap_e_t* hashmap_e = (hashmap_e_t*)malloc(sizeof(hashmap_e_t));
    hashmap_e->key = key;
    hashmap_e->value = value;
    hashmap_e->next = NULL;
    return hashmap_e;
}

hashmap_t* hashmap_create(){   
    hashmap_t* hashmap = (hashmap_t*) malloc (sizeof(hashmap_t));
    hashmap->size = 0;
    hashmap->hashmap_em = (hashmap_e_t **)calloc(KEY_SIZE,sizeof(hashmap_e_t *));
}

void hashmap_destroy(hashmap_t * mp){
    int i;
    for(i = 0;i < KEY_SIZE; i++){
        mp->size = mp->size - hashmap_elementsbykey_destroy(mp->hashmap_em[i]);
    }
    hashmap_e_t** temp = mp->hashmap_em;
    for(i = 0;i < KEY_SIZE; i++) {
       free(*temp++);
    }
    assert(mp->size == 0);
    free(mp->hashmap_em);
    free(mp);
}

//释放每个key下的element
int hashmap_elementsbykey_destroy(hashmap_e_t * hashmap_e_key){
    hashmap_e_t* pos = hashmap_e_key;
    if(pos == NULL)
        return 0;
    int i =0;
     while(pos->next){
        hashmap_e_key = pos->next;
        free(pos->key);
        free(pos->value);
        free(pos);
        i++;
        pos = hashmap_e_key;
    }
    
    free(pos->key);
    free(pos->value);
    free(pos);
    i++;
    return i;
}

long hash_string(const char *key,int len){
    long h = 0;
    int i,off=0;
    for(i = 0; i < len; i ++){
        h = 31*h + key[off++];
    }
    return h%KEY_SIZE;
}

void hashmap_put(hashmap_t* mp, char * key,int key_len,void * value){
    assert(key && key_len>0);
    long hash = hash_string(key,key_len);
    //判断是否已经放入hashmap中，如果放入则替换内容
    hashmap_e_t* hashmap_e = mp->hashmap_em[hash];
    while(hashmap_e != NULL){
        if(strcmp(key,hashmap_e->key) == 0){
            void* temp = hashmap_e->value;
            hashmap_e->value = value;
            if(temp != value)
                free(temp);
            return;
        }
        hashmap_e = hashmap_e->next;
    }
    //没有放入，则添加
    hashmap_e = hashmap_e_create(key,value);
    //把新元素放到每个key队列的头部
    hashmap_e->next = mp->hashmap_em[hash];
    mp->hashmap_em[hash]= hashmap_e;
    mp->size++;
}

void* hashmap_get(hashmap_t* mp,char *key,int key_len){
    assert(key && key_len>0);
    long hash = hash_string(key,key_len);
    hashmap_e_t* hashmap_e = mp->hashmap_em[hash];
    while(hashmap_e != NULL){
        if(strcmp(key,hashmap_e->key) == 0)
            return hashmap_e->value;
        hashmap_e = hashmap_e->next;
    }
    return NULL;
}

void print(hashmap_t* mp){
    int i;
    for(i=0;i<KEY_SIZE;i++){
        hashmap_e_t* hashmap_e= mp->hashmap_em[i];
        while(hashmap_e){
             printf("%s:%s ",hashmap_e->key,(char *)hashmap_e->value);
             hashmap_e = hashmap_e->next;
        }
    }

    printf("\n");

}



int main(){
   
}
