#include <stdlib.h>
#include <stdio.h>

#include "vLib.h"

int main(int argc, char** argv) {
    int length;
    char* arg;

    arg = argv[1];
    length = vLen(arg);

    printf("Length of arguemnt = %d\n", length);
    return 0;
}
