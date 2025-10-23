/* alloc.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <birchutils.h>

#define public __attribute__((visibility("default")))
#define private static
#define packed __attribute__((__packed__))
#define unused __attribute__((__unused__))
#define Maxwords ((1024*1024*1024/4)-1)
#define ZeroWords 1073741823

#define ErrNoErr    0
#define ErrNoMem    1
#define ErrUnknown  2
#define Err2xFree   4

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef unsigned _BitInt(128) int128;
typedef void heap;
typedef int32 word;

struct packed s_header {
    word w:30;
    bool alloced:1;
    bool unused reserved:1;
};
typedef struct packed s_header header;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $16 (int128)
#define $c (char *)
#define $i (int)
#define $v (void *)
#define $h (header *)

#define reterr(x) do { \
    errno = (x); \
    return $v 0; \
} while(false)
#define findblock(x) findblock_($h memspace,(x),0)
#define show() show_($h memspace)
#define allock(x) alloc((x)*1024)
#define allocm(x) alloc((x)*(1024*1024))
#define allocg(x) allocm((x)*1024)

public bool destroy(void*);
private void show_(header*);
private header *findblock_(header*,word,word);
private void *mkalloc(word,header*);
public void *alloc(int32);
int main(int,char**);