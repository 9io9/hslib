#include <stdlib.h>
#include "algo/strh.h"

#define RSEED 10324

int swhash(int cap, void* str) {
    srand(RSEED);

    int h = 0;
    char* s = str;

    while (s[0] != '\0') {
        int rdw = rand() % 255;

        h = h + s[0] * rdw % cap;

        ++s;
    }

    return h;
}

int sshash(int cap, void* str) {
    int h = 0;
    char* s = str;

    while (s[0] != '\0') {
        h = h + s[0] % cap;
        ++s;
    }

    return h;
}

int sihash(int cap, void* str) {
    int h = 0;
    int ws[4] = { 1 << 24, 1 << 16, 1 << 8, 1 };
    int iws = 0;
    char* s = str;

    while (s[0] != '\0') {
        h = h + ((s[0] % cap) * (ws[iws] % cap) % cap) % cap;
        ++s;
    }

    return h;
}