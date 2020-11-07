#include <x86intrin.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint16_t randSeed(uint32_t* seed){
    int generated = *seed * 0x41C64E6D + 0x6073;
    *seed = generated & 0xFFFFFFFF;
    int out = (generated & 0xFFFF0000) >> 16;
    return out;
}

__m256i vrandSeed(__m256i* seed){
    __m256i mul = _mm256_set1_epi32(0x41C64E6D);
    __m256i adv = _mm256_set1_epi32(0x6073);
    
    __m256i seedMask = _mm256_set1_epi32(0xFFFFFFFF);
    __m256i genMask = _mm256_set1_epi32(0xFFFF0000);
    __m256i generated = _mm256_mullo_epi32(*seed, mul);
    generated = _mm256_add_epi32(generated, adv);
    *seed = _mm256_and_si256(seedMask, generated);
    __m256i out = _mm256_and_si256(genMask, generated);
    out = _mm256_srli_epi32(out, 16);
    return out;

}

void shinyPrintData(uint32_t rand1, uint32_t rand2, uint32_t PID, int TID, int SID){
    int HID = (PID & 0xFFFF0000) >> 16;
    int LID = (PID & 0xFFFF);

    int sHID = HID & 0xFFF8;
    int sLID = LID & 0xFFF8;
    int sTID = TID & 0xFFF8;
    int sSID = SID & 0xFFF8;
    int shiny = 0;
    int sCheck = sHID ^ sLID ^ sTID ^ sSID;
    if(sCheck != 0)
        return;
    shiny = 1;

    char ntable[25][8] = {
        "Hardy",
        "Lonely",
        "Brave",
        "Adamant",
        "Naughty",
        "Bold",
        "Docile",
        "Relaxed",
        "Impish",
        "Lax",
        "Timid",
        "Hasty",
        "Serious",
        "Jolly",
        "Naive",
        "Modest",
        "Mild",
        "Quiet",
        "Bashful",
        "Rash",
        "Calm",
        "Gentle",
        "Sassy",
        "Careful",
        "Quirky"
    };

    int nature = PID % 25;
    int ability = PID & 1;
    int gender = PID & 0xFF;

    int deiv = (0x7C00 & rand1) >> 10;
    int ativ = (0x3E0 & rand1) >> 5;
    int hpiv = (0x1F & rand1);

    int sdiv = (0x7C00 & rand2) >> 10;
    int saiv = (0x3E0 & rand2) >> 5;
    int spiv = (0x1F & rand2);

    char buffer[512];
    sprintf(buffer,"%08X\t%s\t%s\t\t%d\t\t", PID, (shiny? "Yes":"No"), ntable[nature], ability);
    sprintf(buffer + strlen(buffer),"%d\t%d\t%d\t%d\t%d\t%d\t%c\t%c\t%c\t%c\n", hpiv, ativ, deiv, saiv, sdiv, spiv,(gender <=30?'F':'M'),(gender<=63?'F':'M'),(gender<=126?'F':'M'),(gender<=190?'F':'M'));
    printf("%s", buffer);

}

void printData(uint32_t rand1, uint32_t rand2, uint32_t PID, int TID, int SID){
    char ntable[25][8] = {
        "Hardy",
        "Lonely",
        "Brave",
        "Adamant",
        "Naughty",
        "Bold",
        "Docile",
        "Relaxed",
        "Impish",
        "Lax",
        "Timid",
        "Hasty",
        "Serious",
        "Jolly",
        "Naive",
        "Modest",
        "Mild",
        "Quiet",
        "Bashful",
        "Rash",
        "Calm",
        "Gentle",
        "Sassy",
        "Careful",
        "Quirky"
    };

    int nature = PID % 25;
    int ability = PID & 1;
    int gender = PID & 0xFF;

    int deiv = (0x7C00 & rand1) >> 10;
    int ativ = (0x3E0 & rand1) >> 5;
    int hpiv = (0x1F & rand1);

    int sdiv = (0x7C00 & rand2) >> 10;
    int saiv = (0x3E0 & rand2) >> 5;
    int spiv = (0x1F & rand2);

    int HID = (PID & 0xFFFF0000) >> 16;
    int LID = (PID & 0xFFFF);

    int sHID = HID & 0xFFF8;
    int sLID = LID & 0xFFF8;
    int sTID = TID & 0xFFF8;
    int sSID = SID & 0xFFF8;
    int shiny = 0;
    int sCheck = sHID ^ sLID ^ sTID ^ sSID;
    if(sCheck == 0)
        shiny = 1;
    char buffer[512];
    sprintf(buffer,"%08X\t%s\t%s\t\t%d\t\t", PID, (shiny? "Yes":"No"), ntable[nature], ability);
    sprintf(buffer + strlen(buffer),"%d\t%d\t%d\t%d\t%d\t%d\t%c\t%c\t%c\t%c\n", hpiv, ativ, deiv, saiv, sdiv, spiv,(gender <=30?'F':'M'),(gender<=63?'F':'M'),(gender<=126?'F':'M'),(gender<=190?'F':'M'));
    printf("%s", buffer);
}
