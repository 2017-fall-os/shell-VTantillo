#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "vToke.h"
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
  char *exitStr = "exit";
  
  while(1) {
    // print prompt
    write(1, "$ ", 2);
    
    // read in command
    len = read(0, buf, (size_t)MAXBUF);
    // if command is empty, start from the beginning
    if(len == 1) {
      continue;
    }
    buf[len-1] = '\0';
    cmdStr = buf;
    
    // check if the command is exit 
    if(vCmp(cmdStr, exitStr)) {
      exit(0);
    }
    
    // tokenize the command
    cmd = vToke(cmdStr, ' ');
    for (i = 0; cmd[i] != '\0'; i++) {
      printf("%s\n", cmd[i]);
    }
    
  }
  return 0;
}
