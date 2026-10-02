#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

#define NAME_LEN 50

struct task {
	int number;
	char name[NAME_LEN + 1];
	struct task *next;
};

struct task *todo = NULL;
int num_tasks = 0;

void insert(void);
void delete(void);
void renumber(void);
void print(void);
void free_all(void);

int main(void)
{
	char code;

	printf("TODO LIST  [i]nsert [d]elete [p]rint [q]uit\n\n");

	for (;;) {
		printf("Enter code: ");
		scanf(" %c", &code);
		while (getchar() != '\n')
			;

		switch (code) {
			case 'i': insert();
			          break;
			case 'd': delete();
			          renumber();
			          break;
			case 'p': print();
			          break;
			case 'q': free_all();
			          return 0;
			default:  printf("-- Invalid code --\n");
			          break;
		}
	}

	return 0;
}

void insert(void)
{
	struct task *new_task, *p;

	new_task = malloc(sizeof *new_task);
	if (new_task == NULL) {
		printf("-- Database is full --\n");
		return;
	}

	new_task->number = ++num_tasks;

	printf("Enter task: ");
	read_line(new_task->name, NAME_LEN);

	new_task->next = NULL;

	if (todo == NULL)
		todo = new_task;
	else {
		for (p = todo; p->next != NULL; p = p->next)
			;
		p->next = new_task;
	}
}

void delete(void)
{
	struct task *prev, *p;
	int number;

	if (todo == NULL) {
		printf("-- No tasks to delete --\n");
		return;
	}

	printf("Delete no.: ");
	scanf("%d", &number);
	while (getchar() != '\n')
		;

	for (prev = NULL, p = todo;
			p != NULL && p->number < number;
			prev = p, p = p->next)
		;
	if (p == NULL || p->number != number) {
		printf("Task not found.\n");
		return;
	}
	if (prev == NULL)
		todo = p->next;
	else
		prev->next = p->next;

	free(p);
}

void renumber(void)
{
	struct task *p;
	int number = 0;
	
	for (p = todo; p != NULL; p = p->next)
		p->number = ++number;
	num_tasks = number;
}

void print(void)
{
	struct task *p;

	if (todo == NULL) {
		printf("-- No tasks to print --\n");
		return;
	}

	printf("+-----+----------------------------------------------------+\n");
	printf("| No. | Task                                               |\n");
	printf("+-----+----------------------------------------------------+\n");
	for (p = todo; p != NULL; p = p->next)
		printf("| %3d | %-50s |\n", p->number, p->name);
	printf("+-----+----------------------------------------------------+\n");
}

void free_all(void)
{
	struct task *p;

	while (todo != NULL) {
		p = todo;
		todo = todo->next;
		free(p);
	}
}
