#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <x86intrin.h>
#include "PIDGen_Util.h"
#include "PIDGen_pthread.h"

int Sonly = 0;

int main(int argc, char** argv){
    if(argc != 1){
        for(int i = 1; i < argc; i++){
            if(!strcmp(argv[i], "-s"))
                Sonly = 1;
        }
    }
    int TID;
    printf("TID:");
    scanf("%d", &TID);
    int SID;
    printf("SID:");
    scanf("%d", &SID);
    int method;
    printf("Method:");
    scanf("%d",&method);

    int threads;
    printf("Threads:");
    scanf("%d", &threads);

    int threadIter;
    printf("Thread Iterations:");
    scanf("%d", &threadIter);

    int maxIter;
    printf("Max Iterations:");
    scanf("%d", &maxIter);

    printf("PID\t\tShiny\tNature\t\tAbility\t\tHP\tATK\tDEF\tSPA\tSPD\tSPE\t1/8 F\t1/4 F\t1/2 F\t3/4 F\n");
    PIDGen_init(threads, threadIter, maxIter, TID, SID, method, Sonly);
}
