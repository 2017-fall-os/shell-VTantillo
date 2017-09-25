#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
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

char *vGetPath(char **envp) {
  char *path = envp[26];
  char **pathToke = vToke(path, '=');
  char *files = pathToke[1];
  return files;
  
}

int main(int argc, char** argv, char** envp) {
  char buf[MAXBUF];

  char **cmd;  // the tokenized command
  char **dir;  // the tokenized directories in path
  
  char *cmdStr;
  char *exitStr = "exit";
  
  char *path = vGetPath(envp); // the path environment variable

  int len;
  int i;

  dir = vToke(path, ':');
  
  while(1) {
    // print prompt
    write(1, "$ ", 2);
    
    // read in command
    len = read(0, buf, (size_t)MAXBUF);
    
    // if command is empty, start from the beginning
    if(len == 1) {
      continue;
    }

    //terminate command
    buf[len-1] = '\0';
    cmdStr = buf;
    
    // check if the command is exit 
    if(vCmp(cmdStr, exitStr)) {
      exit(0);
    }
    
    // tokenize the command
    cmd = vToke(cmdStr, ' ');

    // 

    
    int rc = fork();
    if (rc < 0) {
      // fork failed, exit
      exit(1);
    } else if (rc == 0) {
      // child
      int returnVal = execve(cmd[0], &cmd[0], envp);
      write(1, "Command not found\n", 18);
      exit(0);
    } else {
      // parent
      int wc = wait(NULL);
    }
    
    vFree(cmd);
    cmd = NULL;
  }  // end of while
  
  return 0;
}  // end of main
