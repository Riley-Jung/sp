#include "kvs.h"

int close(kvs_t* kvs)
{
	if(kvs == NULL){	//kvs가 이미 NULL인 경우
		return 0;
	}

	while(kvs->db != NULL){
		
		node_t* nxt = kvs->db->next;
		free(kvs->db);	//kvs->db 할당 해제
		kvs->db = nxt;
	}

	free(kvs);	//kvs할당 해제
	printf("closed\n");
	return 0;
}
