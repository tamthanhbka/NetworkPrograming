#include "acc.h"

Account newAccount(char username[], char password[], int status)
{
    Account acc = (Account)malloc(sizeof(struct _acc));

    strcpy(acc->username, username);
    strcpy(acc->password, password);
    acc->status = status;
    acc->loginErr = 0;
    acc->activeErr = 0;
}
Dllist makeAccList(char *filename)
{
    Dllist list = new_dllist();
    IS is = new_inputstruct(filename);
    if (is == NULL)
    {
        printf("khong mo duoc file \n");
        exit(0);
    }
    while (get_line(is) >= 0)
    {
        dll_append(list, new_jval_v(newAccount(is->fields[0], is->fields[1], atoi(is->fields[2]))));
    }
    jettison_inputstruct(is);
    return list;
}
Account checkAcc(Dllist list, char *username)
{
    Dllist root;
    Account acc;
    dll_traverse(root, list)
    {
        acc = (Account)jval_v(dll_val(root));
        if (strcmp(acc->username, username) == 0)
        {
            return acc;
        }
    }
    return (void *)0;
}
void addAcc(Dllist list, Account acc)
{
    dll_append(list, new_jval_v(acc));
}
void updateData(Dllist list, char *filename)
{
    Dllist node;
    FILE *fout = fopen(filename, "w+");
    dll_traverse(node, list)
    {
        Account acc = (Account)jval_v(dll_val(node));
        fprintf(fout, "%s %s %d", acc->username, acc->password, acc->status);
        if (node != dll_last(list))
        {
            fprintf(fout, "\n");
        }
    }
    fclose(fout);
}
void freeList(Dllist list){
    Dllist node;
    dll_traverse(node, list){
        free(jval_v(dll_val(node)));
    }
}
int checkInput(char name[]){ // neu input co khoang trang -> return # 0, nguoc lai return 0
    return strstr(name," ") != NULL;
}
