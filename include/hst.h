#ifndef _LJW_HSLIB_HST_H_

#define _LJW_HSLIB_HST_H_

#include <stdbool.h>
#include "chdrs/result.h"
#include "chdrs/fn.h"

typedef int (*HashFn) (int, void*);

typedef struct {
    bool has_value;
    char d[];
}Hslot;

typedef struct {
    int cap;
    int size;
    Hslot* t;
    HashFn fhash;
    CopyFn fcopy;
}Hst;

Error hst_init(Hst* hst, int dsize, int cap, HashFn fhash, CopyFn fcopy);
Result hst_get(Hst* hst, void* data);
Error hst_put(Hst* hst, void* data);
Error hst_repl(Hst* hst, void* data, void* ndata);
Error hst_destroy(Hst* hst);

#endif