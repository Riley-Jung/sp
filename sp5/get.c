#include "kvs.h"

char* get(kvs_t* kvs, const char* key) {
    
    node_t* tmp = kvs->db;
    
    while (tmp != NULL) {
        
        if (strcmp(tmp->key, key) == 0) return tmp->value;
        tmp = tmp->next;
    }

    return NULL;}

