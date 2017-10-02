#include <stdlib.h>

#include "vLib.h"

int vCmp(char* str1, char* str2) {
    int i;
    char* t1 = str1;
    char* t2 = str2;
    for (i = 0; t1[i] != '\0'; i++) {
        if(t1[i] != t2[i]) {
            return 0;
        }
    }
    return 1;

} // end of vCmp

void vFree(char** cmd) {
    int i;
    for (i = 0; cmd[i] != '\0'; i++) {
        free(cmd[i]);
        cmd[i] = NULL;
    }
    free(cmd);
    cmd = NULL;
} // end of vFree

char* vConcat(char* str1, char* str2) {
    char* t1;
    char* t2;
    char* new;

    int len1;
    int len2;

    for (t1 = str1; *t1; t1++)
    ;
    for (t2 = str2; *t2; t2++)
    ;
    len1 = t1 - str1;
    len2 = t2 - str2;

    char* newStr = (char *)malloc(len2 + len1 + 1);
    new = newStr;
    for (t1 = str1; *t1; t1++, new++) {
        *new = *t1;
    }
    for (t2 = str2; *t2; t2++, new++) {
        *new = *t2;
    }
    new++;
    *new = '\0';
    return newStr;

} // end of vConcat

char* vCopy(char *str) {
    char *strP;
    char *strEnd;
    char *copy;
    char *copyP;

    int length;

    for (strEnd = str; *strEnd; strEnd++)
    ;

    length = strEnd - str + 1;
    copy = copyP = (char *)malloc(length);
    for(strP = str; *strP; strP++) {
        *copyP = *strP;
        copyP++;
    }
    copyP = 0;
    return copy;

} // end of vCopy

int vLen(char* str) {
    int len = 0;
    char* tmp;

    for (tmp = str; *tmp; tmp++)
    ;

    len = tmp - str;
    return len;
}
