#include <stdlib.h>
#include <unistd.h>
#include "vToc.h"

#define MAXBUF 1024

// Tokenizes the given string 'str' and returns an array with pointers to each
// token
char **vToc(char *str, char delim) {
    char **vector;
    char *tmp;
    int i, j;       // counters
    int numWords;   // number of tokens in the string
    int wordLen;    // length of the word being processed
    int letters;    // number of characters that have been processed

    numWords = countWords(str, delim);
    vector = (char **)calloc((numWords + 1), sizeof(char *));

    i = 0;
    tmp = str;
    while (i != numWords) {
        // find the beginning of the token
        while (*tmp == delim || *tmp == '\0') {
            tmp++;
        }
        // find length of token
        wordLen = wordLength(tmp, delim);
        // create storage for the token
        vector[i] = (char *)malloc(wordLen + 1);
        // copy token
        j = 0;
        while (j != wordLen) {
            vector[i][j] = *tmp;
            j++;
            tmp++;
        }
        vector[i][j + 1] = '\0';
        i++;
    }
    return vector;
}

 // Given a pointer to the string, the function returns the number of words in
 // the string seperated by the delimeter.
int countWords(char *str, char delim) {

    int words;
    words = 0;

    char lastChar;
    lastChar = delim;

    char *cur;
    cur = str;

    while (*cur != '\0') {
        if (*cur == delim && lastChar == delim) {   // Multiple spaces
            lastChar = *cur;
            cur++;

        } else if (*cur != delim && lastChar != delim) {    // Middle of a word
            lastChar = *cur;
            cur ++;

        } else if (*cur != delim && lastChar == delim) {    // Beginning
            lastChar = *cur;
            words ++;
            cur ++;

        } else if (*cur == delim && lastChar != delim) {    // End of a word
            lastChar = *cur;
            cur ++;
        }
    }

    return words;
}

// Given a pointer to the beginning of a word, the function returns the length
// of the word up to the delimeter but not including.
int wordLength(char *str, char delim) {
    int length = 0;

    char *cur;
    cur = str;

    while(*cur != delim && *cur != '\0') {
        length ++;
        cur++;
    }

    return length;
}
