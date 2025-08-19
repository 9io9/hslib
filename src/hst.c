#include <stdlib.h>
#include <string.h>
#include "hst.h"
#include "ec.h"

Error hst_init(Hst* hst, int dsize, int cap, HashFn fhash, CopyFn fcopy) {
    if (hst == NULL || dsize <= 0 || cap <= 0 || fhash == NULL || fcopy == NULL) {
        return ERROR("hst == NULL or dsize <= 0 or cap <= 0 or fhash == NULL or fcopy == NULL", ECODE(HSLIB, HST, ARGV));
    }

    hst->cap = cap;
    hst->fcopy = fcopy;
    hst->fhash = fhash;
    hst->size = 0;
    hst->t = calloc(cap, dsize + sizeof(Hslot));

    return ERROR(NULL, 0);
}

Result hst_get(Hst* hst, void* data) {
    if (hst == NULL || data == NULL) {
        return RESULT_FAIL("hst == NULL or data == NULL", ECODE(HSLIB, HST, ARGV));
    }

    int islot = hst->fhash(hst->cap, data);

    if (!hst->t[islot].has_value) {
        return RESULT_FAIL("data not found for hash table", ECODE(HSLIB, HST, DNF));
    }

    hst->fcopy(data, hst->t[islot].d);

    return RESULT_SUC(i32, islot);
}

Error hst_put(Hst* hst, void* data) {
    if (hst == NULL || data == NULL) {
        return ERROR("hst == NULL or data == NULL", ECODE(HSLIB, HST, ARGV));
    }

    int islot = hst->fhash(hst->cap, data);

    hst->fcopy(hst->t[islot].d, data);

    return ERROR(NULL, 0);
}

Error hst_repl(Hst* hst, void* data, void* ndata) {
    if (hst == NULL || data == NULL || ndata == NULL) {
        return ERROR("hst == NULL or data == NULL or ndata == NULL", ECODE(HSLIB, HST, ARGV));
    }

    int islot = hst->fhash(hst->cap, data);

    hst->fcopy(hst->t[islot].d, ndata);

    return ERROR(NULL, 0);
}

Error hst_destroy(Hst* hst) {
    if (hst == NULL) {
        return ERROR("hst == NULL", ECODE(HSLIB, HST, ARGV));
    }

    if (hst->t != NULL) {
        free(hst->t);
    }

    memset(hst, 0, sizeof(Hst));

    return ERROR(NULL, 0);
}