#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>

int set(kvs_t* kvs, const char* skey, const char* svalue) {

    node_t* newNode = (node_t*)malloc(sizeof(node_t));  // 메모리 할당
    if (!newNode) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 0;  
    }

    newNode->value = (char*)malloc(strlen(svalue) + 1); //value 메모리 할당
    if (!newNode->value) {
        fprintf(stderr, "Failed to allocate memory\n");
        free(newNode);  
        return 0;       
    }

    strcpy(newNode->key, skey); //값 복사
    strcpy(newNode->value, svalue);

    newNode->next = kvs->db; //기존 노드의 앞에 추가
    kvs->db = newNode;
    kvs->items++;

    return 1;
}
