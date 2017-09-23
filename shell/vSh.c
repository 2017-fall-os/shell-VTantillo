#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "vToc.h"
#include "vSh.h"

#define MAXBUF 1000

int vCmp(char *str1, char *str2) {
  int i;
  char *t1 = str1;
  char *t2 = str2;
  for (i = 0; t1[i] != '\0'; i++) {
    if(t1[i] != t2[i]) {
      return 0;
    }
  }
  return 1;
}

void vFree(char **cmd) {
  int i;
  for (i = 0; cmd[i] != '\0'; i++) {
    free(cmd[i]);
  }
  free(cmd);
}

int main(int argc, char** argv, char** envp) {
  char **cmd;
  char *cmdStr;
  char buf[MAXBUF];
  int len;
  int i;
  char *exit2 = "exit";
  char *exitStr = "exit";
  while(1) {
    // Print prompt
    write(1, "$ ", 2);
    // Read in command
    len = read(0, buf, (size_t)MAXBUF);
    buf[len] = '\0';
    cmdStr = buf;
    // Tokenize on spaces
    cmd = vToc(cmd[0], ' ');
    int compare;
    compare = vCmp(cmdStr, exitStr);
    printf("%d\n", compare);
    // Check if the command is exit
    if(compare) {
      exit(0);
    }
    for(i = 0; cmd[i] != '\0'; i++) {
      printf("%s\n", cmd[i]);
    }

    free(cmd);
  }
  return 0;
}
