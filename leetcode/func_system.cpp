#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void *memcpy(void* dst, const void* src, unsigned int size){
    if(dst == NULL || src == NULL || size == 0) return NULL;
    char *psrc = (char*)src;
    char *pdst = (char*)dst;
    //考虑重合的情况
    if(pdst > psrc && pdst < psrc + size){
        pdst = pdst + size - 1;
        psrc = psrc + size - 1;
        while(size--) *pdst-- = *psrc--;
    }else{
        while(size--) *pdst++ = *psrc++;
    }
    return dst;
}