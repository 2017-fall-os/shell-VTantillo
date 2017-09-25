#ifndef ShellDef
#define ShellDef

int vCmp(char* str1, char* str2);
void vFree(char** vector);
char* vGetPath(char** envp);
char* vConcat(char* str1, char* str2);

#endif
