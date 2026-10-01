#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

#define NAME_LEN 50

struct task {
	char name[NAME_LEN + 1];
	struct task *next;
};

struct task *head = NULL;

void insert(void);
void delete(void);
void print(void);

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
			case 'i':
				insert();
				break;
			case 'd':
				delete();
				break;
			case 'p':
				print();
				break;
			case 'q':
				return 0;
			default:
				printf("-- Invalid code --\n");
				break;
		}
	}

	return 0;
}

void insert(void)
{
	struct task *new_task;
	struct task *p;

	new_task = malloc(sizeof(struct task));
	if (new_task == NULL) {
		printf("-- Database is full --\n");
		return;
	}

	printf("Enter task: ");
	readline(new_task->name, NAME_LEN);

	new_task->next = NULL;

	if (head == NULL) {
		head = new_task;
	} else {
		for (p = head; p->next != NULL; p = p->next)
			;

		p->next = new_task;
	}
}

void delete(void)
{
	struct task *prev;
	struct task *current;
	int number;
	int current_number;

	if (head == NULL) {
		printf("-- No tasks to delete --\n");
		return;
	}

	printf("Delete no.: ");
	scanf("%d", &number);
	while (getchar() != '\n')
		;

	prev = NULL;
	current = head;
	current_number = 1;

	while (current != NULL && current_number < number) {
		prev = current;
		current = current->next;
		current_number++;
	}

	if (current == NULL || current_number != number) {
		printf("Task not found.\n");
		return;
	}

	if (prev == NULL)
		head = current->next;
	else
		prev->next = current->next;

	free(current);
}

void print(void)
{
	struct task *p;
	int number = 1;

	if (head == NULL) {
		printf("-- No tasks to print --\n");
		return;
	}

	printf("+-----+----------------------------------------------------+\n");
	printf("| No. | Task                                               |\n");
	printf("+-----+----------------------------------------------------+\n");

	for (p = head; p != NULL; p = p->next)
		printf("| %3d | %-50s |\n", number++, p->name);

	printf("+-----+----------------------------------------------------+\n");
}
