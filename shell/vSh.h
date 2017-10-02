#ifndef ShellDef
#define ShellDef

int chkPipe(char* str);
void doPipe(char* str, char** dir, char** envp);
int chkBackground(char* str);
void doBackground(char* cmdStr, char** dir, char** envp);

#endif
