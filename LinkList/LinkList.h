#ifndef _LINKLIST_H_
#define _LINKLIST_H_

struct node {
	int data;
	struct node *next;
};

struct node *current;
struct node *temp;
struct node *head;

int addNewItem(int addData, char **resultMsg);
int deleteItem(int deleteData, char **resultMsg);
void printList();
int reverseList(char **resultMsg);
int displayMenu();

#endif


