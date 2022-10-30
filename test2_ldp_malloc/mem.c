#define _GNU_SOURCE

#include "mem.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <unistd.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <malloc.h>
#include <pthread.h>



struct mem_calls {
    void* (*malloc)(size_t sz);
    void (*free)(void* ptr);
};
struct mem_calls real_memcall;


static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static void init_preload(void)
{
    static int init;
    // quick check without lock
    if (init) {
        return;
    }

    pthread_mutex_lock(&mut);
    if (init) {
        goto out;
    }

    real_memcall.malloc = dlsym(RTLD_NEXT, "malloc");
    real_memcall.free = dlsym(RTLD_NEXT, "free");
    init = 1;
out:
    pthread_mutex_unlock(&mut);
}

void* malloc(size_t sz){
    init_preload();
    fprintf(stderr,"[malloc] request:%lu\n",sz);
    return real_memcall.malloc(sz);
}
void free(void* ptr){
    init_preload();
    fprintf(stderr,"[free] free\n");
    real_memcall.free(ptr);
}
