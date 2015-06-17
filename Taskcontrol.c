#include <stdlib.h>
#include <stdint.h>
#include "Task.h"
#define MAX_TASKS 10

typedef struct Task_s {
void (*f)(void *data); /* Task function */
void *data; /* Private data pointer for this task */
} Task_t;

/* Process list */
Task_t tasks[MAX_TASKS];
int32_t currentTask;

int32_t TasksInit(void)
{
uint32_t i =0;
while(i !=MAX_TASKS)
{
	tasks[i].f = NULL;
	tasks[i].data = NULL;
	i++;
}
return 0;
}

int32_t TaskAdd(void (*f)(void *data), void *data)
{                           /* Try to find an empty slot */
	uint32_t i;
	for(i=0; i<MAX_TASKS; i++) {
		if(tasks[i].f == NULL) {
			tasks[i].f = f;
			tasks[i].data = data;
			return i;
		}
	}
/* No slots available, return -1 */
return -1;
}

int32_t TaskKill(int32_t id)
{
	tasks[id].f = NULL;
	tasks[id].data = NULL;
	return 0;
}


int32_t TaskCurrent(void)
{
	return currentTask;
}

                        /* Find the next task to run */
int32_t TaskNext(void)
{
	int32_t i;
	int32_t count=0;
	i = currentTask;
	do {
		i = (i + 1) % MAX_TASKS;
		count++;
	} while((tasks[i].f == NULL)
		&& (count <= MAX_TASKS));
	return (count <= MAX_TASKS) ? i : -1;
}

int32_t TaskSwitcher(void)
{
	
	if(currentTask<0)
	{
		return -1;
	}
	tasks[currentTask].f(tasks[currentTask].data);
	currentTask = TaskNext();
	return 0;	
}