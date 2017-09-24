#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "vToke.h"

#define BUFLEN 2000

char **vToke(char *str, char delim) {
    char tmpBuf[BUFLEN];

    int numTokens = 0;
    int tokensCounted = 0;

    char lastChar = delim;

    char *strP;
    char *strEnd;

    char *tmpP;
    char *tmpEnd;

    char **tokens;
    char **tokensP;
    char **tokensEnd;

    // set string pointers;
    for (strEnd = str; *strEnd; strEnd++) {
        ;
    }

    numTokens = countTokens(str, delim);
    // create tokens array
    tokens = (char **)calloc((numTokens + 1), sizeof(char *));
    tokensEnd = tokens + numTokens;
    tokens[numTokens] = 0;

    // insert tokens into array
    for (tokensP = tokens; tokensP < tokensEnd; tokensP ++) {
        for (strP = str; strP != strEnd; strP++) {
            if (*strP == delim && lastChar == delim) {
                // multiple demimeters
                lastChar = *strP;

            } else if (*strP != delim && lastChar != delim) {
                // middle of a token
                *tmpP = *strP;
                tmpP ++;
                lastChar = *strP;

            } else if (*strP != delim && lastChar == delim) {
                // beginning of a token
                tmpP = tmpBuf;  // reset
                *tmpP = *strP;
                tmpP ++;
                lastChar = *strP;

            } else if (*strP == delim && lastChar != delim) {
                // end of a token
                *tmpP = 0;
                *tokensP = vCopy(tmpBuf);
                tokensP ++;
                lastChar = *strP;
            }
        }
        *tmpP = 0;
        *tokensP = vCopy(tmpBuf);
        tokensP ++;
    }
    return tokens;
}

int countTokens(char *str, char delim) {
    char *strP;     // string pointer
    char *strEnd;   // pointer to the end of the string

    char lastChar = delim;  // the last character read

    int numTokens = 0;  // the number of tokens found

    // Find end of string
    for (strEnd = str; *strEnd; strEnd++){
        ;
    }

    for (strP = str; strP != strEnd; strP ++) {
        if (*strP == delim && lastChar == delim) {
            // multiple demimeters
            lastChar = *strP;

        } else if (*strP != delim && lastChar != delim) {
            // middle of a token
            lastChar = *strP;

        } else if (*strP != delim && lastChar == delim) {
            // beginning of a token
            lastChar = *strP;
            numTokens ++;

        } else if (*strP == delim && lastChar != delim) {
            // end of a token
            lastChar = *strP;
        }
    }
    return numTokens;
}

char *vCopy(char *str) {
    char *strP;
    char *strEnd;
    char *copy;
    char *copyP;

    int length;

    for (strEnd = str; *strEnd; strEnd++){
        ;
    }

    length = strEnd - str + 1;
    copy = copyP = (char *)malloc(length);
    for(strP = str; *strP; strP++) {
        *copyP = *strP;
        copyP++;
    }
    copyP = 0;
    return copy;
}
