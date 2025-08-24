#ifndef _LJW_HSLIB_STRH_H_

#define _LJW_HSLIB_STRH_H_

int swhash(int cap, void* str); // string weight hash
int sshash(int cap, void* str); // simple string hash
int sihash(int cap, void* str); // string as integers hash

#endif