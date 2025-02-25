#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
	char name[10];
	struct Node * link;
}Node;
int add(Node ** head, char * str)
{
	Node * node = (Node*)malloc(sizeof(Node));
	strcpy(node->name, str);

	if(*head==NULL)
	{
		*head = node;
		node->link=NULL;
	}
	else
	{
		Node * current = *head;
		while(current->link!=NULL)
		{
			current=current->link;
		}
		current->link=node;
		node->link=NULL;
	}

	return 0;
}

void print(Node * head)
{
	Node * current = head;
	while(current!=NULL)
	{
		printf("%s, ", current->name);
		current=current->link;
	}
	printf("\n");
	return;
}
void clear(Node ** head)
{
	Node * current = *head;
	while(current!=NULL)
	{
		Node * link = current->link;
		free(current);
		current = link;
	}
	*head = NULL;
}
int insert(Node ** head, int index, char * str)
{
	return 0;
}

int main()
{
	Node * head = NULL;

	add(&head, "Mon");
	add(&head, "Fri");
	add(&head, "Sun");
	print(head);

	insert(&head,1,"Thu");
	print(head);

	clear(&head);
	print(head);
	return 0;
}

