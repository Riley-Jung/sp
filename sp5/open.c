#include "kvs.h"

kvs_t* open(){
	kvs_t* kvs = (kvs_t*) malloc (sizeof(kvs_t));	//kvs생성

	if(kvs) kvs->items = 0;
	printf("opened\n");

	return kvs;
}
