#include <stdio.h>

int global_init = 10;          // .data

int global_uninit;             // .bss

const int max_speed = 120;     // .rodata

const int table[100] = {0};

static int counter = 5;        // .data

static int flag;               // .bss

void printMessage(void)
{
    printf("Project Phoenix\n");
}

int main(void)
{
    int local = 50;

    printMessage();

    printf("global_init    = %d\n", global_init);
    printf("global_uninit  = %d\n", global_uninit);
    printf("max_speed      = %d\n", max_speed);
    printf("counter        = %d\n", counter);
    printf("flag           = %d\n", flag);
    printf("local          = %d\n", local);

    return 0;
}