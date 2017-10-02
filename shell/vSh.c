#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include "vLib.h"
#include "vSh.h"
#include "vToke.h"

#define MAXBUF 1000
#define LINE 80

int main(int argc, char** argv, char** envp) {
    char buf[MAXBUF];

    int len;        // length of command user types in
    int i;          // counter
    int j;
    int status;
    int wc;
    int pid;
    int pid2;

    char** cmd;     // the tokenized command
    char** dir;     // the tokenized directories in path

    char* cmdStr;   // string that the user types in as the command
    char* cmdTst;   // command that will be appended to environment variable
    char* prompt;   // the ps1 environment variable
    char* tmp;

    char* path = getenv("PATH"); // the path environment variable

    dir = vToke(path, ':');

    while(1) {
        if(cmd != NULL) {
            vFree(cmd);
            cmd = NULL;
        }
        // print prompt
        /*
        // prints the value of what is in PS1, but doesn't properly substitute
        // the variables.
        prompt = getenv("PS1");
        len = vLen(prompt);
        write(1, prompt, len);
        */

        write(1, "--> ", 4);

        // read in command
        len = read(0, buf, (size_t)MAXBUF);

        // if command is empty, start from the beginning
        if(len == 1) {
            continue;
        }

        //terminate command
        buf[len-1] = '\0';
        cmdStr = buf;

        // special case: command is exit
        if(vCmp(cmdStr, "exit")) {
            exit(0);
        }

        // special case: command has a pipe
        if(chkPipe(cmdStr)) {
            doPipe(cmdStr, dir, envp);
            continue;
        }

        // special case: command is to run in background
        if (chkBackground(cmdStr)) {
            doBackground(cmdStr, dir, envp);
            continue;
        }

        // tokenize the command
        cmd = vToke(cmdStr, ' ');

        // special case: cd
        if(vCmp(cmd[0], "cd")) {
            status = chdir(cmd[1]);
            if (status < 0) {
                fprintf(stderr, "%s\n", "Directory not found");
            }
            continue;
        }

        for(i = 0; cmd[i] != '\0'; i++) {
            fprintf(stderr, "%s\n", cmd[i]);
        }

        // loop through all the posibilities of the command
        // if none of them work, say command not found
        j = 0;
        int rc = fork();
        if (rc < 0) {
            // fork failed, exit
            exit(1);
        } else if (rc == 0) {
            // child
            int returnVal = execve(cmd[0], &cmd[0], envp);
            tmp = vConcat("/", cmd[0]);
            for (j = 0; dir[j] != '\0'; j++) {
                cmdTst = vConcat(dir[j], tmp);
                cmd[0] = cmdTst;
                returnVal = execve(cmd[0], &cmd[0], envp);
            }
            fprintf(stderr, "Command not found\n");
            exit(0);
        } else {
        // parent
            int wc = wait(NULL);
        }

        cmdStr = NULL;

    }  // end of while

    return 0;

}  // end of main

int chkPipe(char* str) {
    char* tmp;
    for (tmp = str; *tmp; tmp++) {
        if (*tmp == '|') {
            return 1;
        }
    }
    return 0;
}  // end of chkPipe

int chkBackground(char* str) {
    char* tmp;
    for (tmp = str; *tmp; tmp++) {
        if (*tmp == '&') {
            return 1;
        }
    }
    return 0;
}  // end of chckBackground

void doPipe(char* cmdStr, char** dir, char** envp) {
    int piper[2];

    char** cmds;
    char** cmd1;
    char** cmd2;

    char* tmp;
    char* cmdTst;

    int i, j;
    int fork1;
    int fork2;

    cmds = vToke(cmdStr, '|');

    if (pipe(piper) == -1) {
        fprintf(stderr, "%s\n", "no pipey");
    }

    fork1 = fork();
    if (fork1 < 0) {
        fprintf(stderr, "%s\n", "no forkey 1");

    } else if (fork1 == 0) {
        // older child
        cmd1 = vToke(cmds[0], ' ');

        close(piper[0]);
        dup2(piper[1], 1);
        close(piper[1]);

        int return1 = execve(cmd1[0], &cmd1[0], envp);
        tmp = vConcat("/", cmd1[0]);
        for (i = 0; dir[i] != '\0'; i++) {
            cmdTst = vConcat(dir[i], tmp);
            cmd1[0] = cmdTst;
            return1 = execve(cmd1[0], &cmd1[0], envp);
        }
        fprintf(stderr, "Command not found\n");
        exit(0);

    } else {
        // parent
        // do nothing
    }

    fork2 = fork();
    if (fork2 < 0) {
        fprintf(stderr, "%s\n", "no forkey 2");
    } else if (fork2 == 0) {
        // younger child
        cmd2 = vToke(cmds[1], ' ');

        close(piper[1]);
        dup2(piper[0], 0);
        close(piper[0]);

        int return2 = execve(cmd2[0], &cmd2[0], envp);
        tmp = vConcat("/", cmd2[0]);
        for (j = 0; dir[j] != '\0'; j++) {
            cmdTst = vConcat(dir[j], tmp);
            cmd2[0] = cmdTst;
            return2 = execve(cmd2[0], &cmd2[0], envp);
        }
        fprintf(stderr, "Command not found\n");
        exit(2);
    } else {
        // parent again does nothing.
    }

    close(piper[0]);
    close(piper[1]);
    wait(NULL);
    wait(NULL);

    vFree(cmds);
    vFree(cmd1);

}

void doBackground(char* cmdStr, char** dir, char** envp) {
    char** noAmp = vToke(cmdStr, '&');
    char** cmd = vToke(noAmp[0], ' ');

    char* tmp;
    char* cmdTst;
    int j;
    int rc = fork();
    if (rc < 0) {
        // fork failed, exit
        exit(1);
    } else if (rc == 0) {
        // child
        int returnVal = execve(cmd[0], &cmd[0], envp);
        tmp = vConcat("/", cmd[0]);
        for (j = 0; dir[j] != '\0'; j++) {
            cmdTst = vConcat(dir[j], tmp);
            cmd[0] = cmdTst;
            returnVal = execve(cmd[0], &cmd[0], envp);
        }
        fprintf(stderr, "Command not found\n");
        exit(0);
    } else {
    // parent
        // no waiting
    }

    vFree(noAmp);
    vFree(cmd);
}
