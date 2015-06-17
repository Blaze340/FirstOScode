#include <stdint.h>
#include <stdio.h>
#include "Task.h"
#include "common.h"
int32_t count= 50;
int32_t idd=0;

void Task1(void* data)                                //this task will kill itself
{
	printf("hello from task1!!! it will kill itself so no more task1\n");
	idd= TaskCurrent();
	TaskKill(idd);
}

void Task2(void* data)                                 //this task kills other tasks 
{
	printf("hello from task2!!! it will kill task3 and task 4 and kills itself\n");
	idd= TaskCurrent();
	TaskKill(idd+1);
	TaskKill(idd+2);
	TaskKill(idd);

}

void Task3(void* data)                                 // this task kills itself
{
	printf("hello from task3!!! i will kill myself\n");
	idd= TaskCurrent();
	TaskKill(idd);
}

void Task4(void* data)                                  // this task creates task3 
{
	printf("hello from task4!!! i will create task3\n");
	TaskAdd(Task3, 0);
}

void Task5(void* data)                                  // this task will creates task4 and then kills itself
{
	printf("hello from task5!!! i will kill myself \n");
	TaskAdd(Task4, 0);
	idd= TaskCurrent();
	TaskKill(idd);
}





void TaskTests(int mode)
{
	printf("running TaskTests\n");
	TasksInit();
	TaskAdd(Task1, 0);
	TaskAdd(Task2, 0);
	TaskAdd(Task3, 0);
	TaskAdd(Task4, 0);
	TaskAdd(Task5, 0);
	while(count)
	{
	TaskSwitcher();                                 // it will switch task so task2 will run first
	count--;
}
}
ADD_CMD("tasktests", TaskTests,"                Runs Test Tasks for LAB #5");
