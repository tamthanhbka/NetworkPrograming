#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "dllist.h"
#include "fields.h"
typedef struct _acc
{
    char username[127];
    char password[127];
    int status;
    int loginErr;
    int activeErr;
} * Account;
Account newAccount(char username[], char password[], int status);
Dllist makeAccList(char *filename);
Account checkAcc(Dllist list, char *username);
void addAcc(Dllist list, Account acc);
void updateData(Dllist list, char *filename);
void freeList(Dllist list);
int checkInput(char name[]);