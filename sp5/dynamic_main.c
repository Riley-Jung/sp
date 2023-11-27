#include <stdio.h>
#include <string.h>
#include "kvs.h"
#include <dlfcn.h>

#define MAX_NUM 100
#define KEY_VAL_SIZE 50

int main(){

    void* handle;
    kvs_t* (*open)();
    int (*close)(kvs_t*);
    int (*set)(kvs_t*, const char*, const char*);
    char* (*get)(kvs_t*, const char*);

    handle = dlopen("./libkvs.so", RTLD_LAZY);
    if(!handle){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    open = dlsym(handle, "open");
    close = dlsym(handle, "close");
    get = dlsym(handle, "get");
    set = dlsym(handle, "set");
    
    kvs_t* kvs = open();    //kvs 열기

	if(!kvs) {  //kvs열리지 않았을 때 에러 처리
		printf("Failed to open kvs\n");
		return -1;
	}

    FILE *fp;
    FILE *answer;
    char line[MAX_NUM]; // 최대 100글자의 줄을 읽을 수 있는 버퍼
    char *tk;
    char getKey[KEY_VAL_SIZE]; // "get"의 콤마 뒤 내용 저장
    char setKey[KEY_VAL_SIZE]; // "set"의 콤마 뒤 내용 저장
    char setValue[KEY_VAL_SIZE]; // "set"의 다음 토큰 내용 저장

    const char* queryFile = "query.dat";
    const char* answerFile = "answer.dat";
    
    fp = fopen(queryFile, "r"); // query.dat 읽기 모드로 열기
    answer = fopen(answerFile, "w");  //answer.dat 쓰기 모드로 생성


    if (!(fp = fopen(queryFile, "r")) || !(answer = fopen(answerFile,"w"))) { //파일 열기 오류처리
        printf("failed to load file\n");
        return 1;
    }
    

    while (fgets(line, MAX_NUM, fp) != NULL) {
        
        tk = strtok(line, ","); // 콤마로 라인 구분 
        
        if (strcmp(tk, "get") == 0) {   //get인 경우
            
            tk = strtok(NULL, ",");
            strcpy(getKey, tk);     // "get"인 경우, 콤마 뒤 key를 이용해 kvs에서 value 찾기
            
            char* result = get(kvs, getKey);

            if(result == NULL)  fprintf(answer, "-1\n");   
            else{fprintf(answer, "%s", result);}
        } 

        
        else if (strcmp(tk, "set") == 0) {  //set인 경우

            tk = strtok(NULL, ",");
            strcpy(setKey, tk);

            tk = strtok(NULL, ",");
            strcpy(setValue, tk);

            set(kvs, setKey, setValue); // kvs에 key와 value 저장          
        }
    }

    fclose(fp); // 파일 닫기
    fclose(answer); //파일 닫기
	close(kvs); //kvs 닫기
	
	return 0;
}
