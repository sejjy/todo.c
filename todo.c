#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

struct task {
	struct task *next;
	size_t number;
	char name[];
};

struct task *todo = NULL;
size_t num_tasks = 0;

void insert(void);
void delete(void);
void renumber(void);
void h_border(size_t width);
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
	char *name;
	size_t len;

	printf("Enter task: ");
	name = readline();
	if (name == NULL) {
		printf("-- Memory allocation failed --\n");
		return;
	}

	len = strlen(name);
	new_task = malloc(sizeof *new_task + len + 1);
	if (new_task == NULL) {
		printf("-- Memory allocation failed --\n");
		free(name);
		return;
	}

	new_task->next = NULL;
	new_task->number = ++num_tasks;
	strcpy(new_task->name, name);
	free(name);

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
	size_t number;

	if (todo == NULL) {
		printf("-- No tasks to delete --\n");
		return;
	}

	printf("Delete no.: ");
	scanf("%zu", &number);
	while (getchar() != '\n')
		;

	for (prev = NULL, p = todo;
			p != NULL && p->number < number;
			prev = p, p = p->next)
		;
	if (p == NULL || p->number != number) {
		printf("-- Task not found --\n");
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
	size_t number = 0;
	
	for (p = todo; p != NULL; p = p->next)
		p->number = ++number;
	num_tasks = number;
}

void h_border(size_t width)
{
	size_t i;

	printf("+-----+");
	for (i = 0; i < width + 2; i++)
		printf("-");
	printf("+\n");
}

void print(void)
{
	struct task *p;
	size_t width = 4, len;

	if (todo == NULL) {
		printf("-- No tasks to print --\n");
		return;
	}

	for (p = todo; p != NULL; p = p->next) {
		len = strlen(p->name);
		if (len > width)
			width = len;
	}

	h_border(width);
	printf("| No. | %-*s |\n", (int)width, "Task");
	h_border(width);
	for (p = todo; p != NULL; p = p->next)
		printf("| %3zu | %-*s |\n", p->number, (int)width, p->name);
	h_border(width);
}

void free_all(void)
{
	struct task *temp;

	while (todo != NULL) {
		temp = todo;
		todo = todo->next;
		free(temp);
	}
}
