#include <stdio.h>
#include <stdlib.h>

/*Create structure and declare tag members*/
typedef struct
{
    int data;
    char name;
}SingleTons;
static SingleTons *instance = NULL;

SingleTons *getInstance()
{
    instance = (SingleTons*)malloc(sizeof(SingleTons));
    return instance;
}

void freeSingleTons()
{
    free(instance);
}
int main()
{
    SingleTons *createInstance=getInstance();
    createInstance->data=30;
    printf("1 : %d\n",createInstance->data);

    SingleTons*createInstance1=getInstance();
    printf("2 : %d\n",createInstance->data);

    freeSingleTons();
}