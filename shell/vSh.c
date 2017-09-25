#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "vToke.h"
#include "vSh.h"

#define MAXBUF 1000

int main(int argc, char** argv, char** envp) {
  char buf[MAXBUF];

  char** cmd;  // the tokenized command
  char** dir;  // the tokenized directories in path

  char* cmdStr;  // string that the user types in as the command
  char* exitStr = "exit";
  char* cmdTst;  // command that will be appended to environment variable

  char* path = vGetPath(envp); // the path environment variable

  int len;  // length of command user types in
  int i;  // counter

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
    char* tmp = cmd[0];
    // loop through all the posibilities of the command
    // if none of them work, say command not found

    int rc = fork();
    if (rc < 0) {
      // fork failed, exit
      exit(1);
    } else if (rc == 0) {
      // child
      int returnVal = execve(cmd[0], &cmd[0], envp);
      exit(0);
    } else {
      // parent
      int wc = wait(NULL);
    }

    int j;
    tmp = vConcat("/", tmp);
    for (j = 0; dir[j] != '\0'; j++) {
      cmdTst = vConcat(dir[j], tmp);
      cmd[0] = cmdTst;
      int rd = fork();
      if (rd , 0) {
	exit(1);
      } else if (rd == 0) {
	int retVal = execve(cmd[0], &cmd[0], envp);
	exit(0);
      } else {
	int wd = wait(NULL);
      }
    }

    vFree(cmd);
    cmd = NULL;
  }  // end of while
  return 0;
}  // end of main

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
  }
  free(cmd);
} // end of vFree

char* vGetPath(char** envp) {
  char* path = envp[26];
  char** pathToke = vToke(path, '=');
  char* files = pathToke[1];
  return files;

} // end of vGetPath

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
