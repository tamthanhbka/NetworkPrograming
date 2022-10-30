// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdio_ext.h>
#include "lib/dllist.h"
#include "lib/acc.h"

void menu();
int main(int argc, char *argv[])
{
    Dllist accList;
    accList = makeAccList(argv[1]);
    Account acc = NULL;
    int scan;
    do
    {
        menu();
        scan = 0;
        scanf("%d", &scan);
        __fpurge(stdin);
        switch (scan)
        {
        case 1:
            char name[127];
            printf("Input your username:");
            gets(name);
            __fpurge(stdin);
            if (checkInput(name))
            {
                puts("Input is not invalid!");
                break;
            }
            if (checkAcc(accList, name))
            {
                printf("Account already exists!\n");
                break;
            }
            acc = (Account)malloc(sizeof(struct _acc));
            printf("Input your password:");
            gets(acc->password);
            __fpurge(stdin);
            if (checkInput(acc->password))
            {
                puts("Input is not invalid!");
                break;
            }
            acc = newAccount(name, acc->password, 2);
            addAcc(accList, acc);
            updateData(accList, argv[1]);
            printf("Successful registration. Activation required!\n");
            acc = 0;
            break;
        case 2:
            char nameAct[127];
            printf("Input your username:");
            gets(nameAct);
            __fpurge(stdin);
            if (checkInput(nameAct))
            {
                puts("Input is not invalid!");
                break;
            }
            acc = checkAcc(accList, nameAct);
            if(acc == 0){
                puts("Account is not exist!");
                break;
            }
            if (acc->status == 1)
            {
                printf("Account was actived!\n");
                acc = 0;
                break;
            }
            if (acc->status == 0)
            {
                printf("Account was blocked!\n");
                acc = 0;
                break;
            }
            char pass[127];
            printf("Input your password:");
            gets(pass);
            __fpurge(stdin);
            if (checkInput(pass))
            {
                puts("Input is not invalid!");
                acc = 0;
                break;
            }
            if (strcmp(pass, acc->password) != 0)
            {
                printf("Password is incorrect!\n");
                acc->loginErr++;
                if (acc->loginErr > 3)
                {
                    puts("Account is blocked!");
                    acc->status = 0;
                    updateData(accList, argv[1]);
                }
                acc = 0;
                break;
            }
            char activeCode[127];
            printf("Input your active code:");
            gets(activeCode);
            __fpurge(stdin);
            if (checkInput(activeCode))
            {
                puts("Input is not invalid!");
                acc = 0;
                break;
            }
            if (strcmp(activeCode, argv[2]) != 0)
            {
                puts("Account is not activated!\nActive code is incorrect!");
                acc->activeErr++;
                if (acc->activeErr > 4)
                {
                    puts("Account is blocked!");
                    acc->status = 0;
                    updateData(accList, argv[1]);
                }
                acc = 0;
                break;
            }
            acc->status = 1;
            puts("Account is actived!");
            updateData(accList, argv[1]);
            acc = 0;
            break;
        case 3:
            if (acc != 0)
            {
                printf("Already signin with account %s!\nPlease signout to use this function!\n", acc->username);
                break;
            }
            char nameSg[127];
            printf("Input your username:");
            gets(nameSg);
            __fpurge(stdin);
            if (checkInput(nameSg))
            {
                puts("Input is not invalid!");
                break;
            }
            acc = checkAcc(accList, nameSg);
            if (acc == 0)
            {
                puts("Account is not exist!");
                break;
            }
            if (acc->status == 2)
            {
                puts("Account is not activated");
                acc = 0;
                break;
            }
            if (acc->status == 0)
            {
                printf("Account was blocked!\n");
                acc = 0;
                break;
            }
            // if (acc->loginErr == 1)
            // {
            //     printf("Account %s is sign in!\n", acc->username);
            //     break;
            // }
            char passSg[127];
            printf("Input your password:");
            gets(passSg);
            __fpurge(stdin);
            if (checkInput(passSg))
            {
                puts("Input is not invalid!");
                acc =0;
                break;
            }
            if (strcmp(passSg, acc->password) != 0)
            {
                printf("Password is incorrect!\n");
                acc->loginErr++;
                if (acc->loginErr > 3)
                {
                    puts("Account is blocked!");
                    acc->status = 0;
                    updateData(accList, argv[1]);
                }
                acc = 0;
                break;
            }
            printf("Hello %s!", acc->username);
            break;
        case 4:
            if (acc == 0)
            {
                printf("You is not sign in!\n");
                break;
            }
            char nameSr[127];
            printf("Input username:");
            gets(nameSr);
            __fpurge(stdin);
            if (checkInput(nameSr))
            {
                puts("Input is not invalid!");
                break;
            }
            Account result;
            result = checkAcc(accList, nameSr);
            if (result == 0)
            {
                puts("Account is not exist!");
                break;
            }
            if (result->status == 0)
            {
                printf("Account: %s\nStatus : blocked\n", result->username);
            }
            if (result->status == 1)
            {
                printf("Account: %s\nStatus : active\n", result->username);
            }
            if (result->status == 2)
            {
                printf("Account: %s\nStatus : idle\n", result->username);
            }
            break;
        case 5:
            if (acc == 0)
            {
                printf("You is not sign in!\n");
                break;
            }
            char passCh[127];
            printf("Input your password:");
            gets(passCh);
            __fpurge(stdin);
            if (checkInput(passCh))
            {
                puts("Input is not invalid!");
                break;
            }
            if (strcmp(passCh, acc->password) != 0)
            {
                printf("Password is incorrect!\n");
                acc->loginErr++;
                if (acc->loginErr > 3)
                {
                    puts("Account is blocked!");
                    acc->status = 0;
                    updateData(accList, argv[1]);
                    acc = 0;
                }
                break;
            }
            char newpass[127];
            printf("Input your new password:");
            gets(newpass);
            __fpurge(stdin);
            if (checkInput(newpass))
            {
                puts("Input is not invalid!");
                break;
            }
            strcpy(acc->password, newpass);
            updateData(accList, argv[1]);
            puts("Change password successful!");
            break;
        case 6:
            if (acc == 0)
            {
                printf("You is not sign in!\n");
                break;
            }
            char nameLg[127];
            printf("Input your username:");
            gets(nameLg);
            __fpurge(stdin);
            if (checkInput(nameLg))
            {
                puts("Input is not invalid!");
                break;
            }
            Account temp;
            temp = checkAcc(accList, nameLg);
            if (temp == 0)
            {
                puts("Account is not exist!");
                break;
            }
            if (strcmp(nameLg, acc->username) != 0)
            {
                printf("Account is not sign in!");
                break;
            }
            printf("Goodbye %s!\n", acc->username);
            acc = 0;
            break;
        default:
            printf("Input error!!!\n");
        }
    } while (scan >= 1 && scan <= 6);
    freeList(accList);
    free_dllist(accList);
    return 0;
}
void menu()
{
    printf("\n\tUSER MANAGEMENT PROGRAM\n");
    printf("\t==================================\n");
    printf("\t%4s1.Register \n", " ");
    printf("\t%4s2.Activate \n", " ");
    printf("\t%4s3.Sign in \n", " ");
    printf("\t%4s4.Search \n", " ");
    printf("\t%4s5.Change password \n", " ");
    printf("\t%4s6.Sign out \n", " ");
    printf("\t==================================\n");
    printf("...........Your choice(1-6, other to quit): ");
}