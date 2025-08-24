#include <stdio.h>
#include <stdlib.h>
#include "hst.h"

int i32hash(int c, void* d) {
    int di = *(int*)d;

    return di % c;
}

void i32copy(void* d, void* s) {
    *(int*)d = *(int*)s;
}

static void ferr(Error* e) {
    if (e->message != NULL) {
        fprintf(stderr, "ecode %d: line %u function %s file %s for %s\n", e->ec, e->line, e->function, e->file, e->message);
        exit(1);
    }
}

static void fres(Result* r) {
    if (!r->has_value) {
        ferr(&r->result.error);
    }
}

int main(int argc, char* argv[]) {
    Hst hst;

    Error error = hst_init(&hst, sizeof(int), 10, i32hash, i32copy);

    ferr(&error);

    int d = 30;

    hst_put(&hst, &d);

    ferr(&error);

    Result r = hst_get(&hst, &d);

    fres(&r);

    error = hst_destroy(&hst);

    ferr(&error);

    return 0;
}