#include <stdlib.h>
#include <pthread.h>
#include <x86intrin.h>
#include "PIDGen_Util.h"
#include <stdio.h>

void *PIDGen_thread(void* arg){
    int* things = (int*)arg;
    int taskIndex = things[0];
    int taskIter = things[1];
    int maxIter = things[2];
    int TID = things[3];
    int SID = things[4];
    int method = things[5];
    int Sonly = things[6];
    free(arg);
    int start = 8 * taskIndex * taskIter;
    for(int i = start; i < start + 8*taskIter;i+=8){
        __m256i seedV = _mm256_set_epi32(8*i,8*i+1,8*i+2,8*i+3,8*i+4,8*i+5,8*i+6,8*i+7);
        for(int iter = 0; iter < maxIter; iter++){
            __m256i randomV1 = vrandSeed(&seedV);
            uint32_t* firstRNG = (uint32_t*) &randomV1;
            __m256i randomV2 = vrandSeed(&seedV);
            uint32_t* secondRNG = (uint32_t*) &randomV2;
            __m256i randomV3 = vrandSeed(&seedV);
            uint32_t* thirdRNG = (uint32_t*) &randomV3;
            __m256i randomV4 = vrandSeed(&seedV);
            uint32_t* fourthRNG = (uint32_t*) &randomV4;
            __m256i randomV5 = vrandSeed(&seedV);
            uint32_t* fifthRNG = (uint32_t*) &randomV5;
        
            for(int j = 0; j < 8; j++){
                uint32_t PID = firstRNG[j] + (secondRNG[j] << 16);
                if(method == 1){
                    Sonly?shinyPrintData(thirdRNG[j], fourthRNG[j], PID, TID, SID):printData(thirdRNG[j], fourthRNG[j], PID, TID, SID);
                }
                else if(method == 2){
                    Sonly?shinyPrintData(fourthRNG[j], fifthRNG[j], PID, TID, SID):printData(fourthRNG[j], fifthRNG[j], PID, TID, SID);
                }
                else if(method == 4){
                    Sonly?shinyPrintData(thirdRNG[j], fifthRNG[j], PID, TID, SID):printData(thirdRNG[j], fifthRNG[j], PID, TID, SID);
                }
            }
        }
    }
    pthread_exit(NULL);
}

void PIDGen_init(int threads, int taskIter, int maxIter, int TID, int SID, int method, int Sonly){
    pthread_t* tid = malloc(threads * sizeof(pthread_t));
    for(int i = 0; i < threads; i++){
        int* args = malloc(sizeof(int) * 7);
        args[0] = i;
        args[1] = taskIter;
        args[2] = maxIter;
        args[3] = TID;
        args[4] = SID;
        args[5] = method;
        args[6] = Sonly;
        pthread_create(&tid[i], NULL, PIDGen_thread, args);
    }
    for(int i = 0; i < threads; i++){
        pthread_join(tid[i], NULL);
    }
    free(tid);
}
