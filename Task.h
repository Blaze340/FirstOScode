#include<stdio.h>
#include<stdlib.h>

int32_t TaskAdd(void (*f)(void *data), void *data);
int32_t TaskKill(int32_t id);
int32_t TaskCurrent(void);
int32_t TaskSwitcher(void);
int32_t TaskNext(void);
int32_t TasksInit(void);