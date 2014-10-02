/*=============================================================================
|		 Title:  Linked List C Implementation
|       Author:  Anýl Altunkan
|		E-Mail:	 altunkan@gmail.com
|		   Web:  http://anilaltunkan.com
|  Description:  Simple Linked List Console Application
*=============================================================================*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkList.h"

//add
static const char successMessage1[] = "%d is added to list!\n";
static const char errorMessage1[] = "Out Of Memory While Adding %d!\n";

//delete
static const char successMessage2[] = "%d is deleted from the list!\n";
static const char errorMessage2[] = "%d is not found in the list!\n";

//reverse
static const char successMessage3[] = "List is reversed!\n";
static const char errorMessage3[] = "Out Of Memory While Reversing The List!\n";
static const char errorMessage4[] = "List is Empty!";


int main() {
	char *rMsg = NULL;
	int addResultCode = -1;
	int deleteResultCode = -1;
	int reverseResultCode = -1;
	int menuChoice = 0;
	int item;
	int sReturn;
	while (menuChoice != 5) {
		menuChoice = displayMenu();
		switch (menuChoice)
		{
		case 1:	
			printf("Enter an integer into the list: ");
			if ((sReturn = scanf("%d", &item)) == 0) {
				menuChoice = -1;
				printf("Not an integer!\n");
			}
			else {
				addResultCode = addNewItem(item, &rMsg);
				printf("%s\n", rMsg);
			}
			break;
		case 2:
			printf("Enter an integer for deleting from the list: ");
			if ((sReturn = scanf("%d", &item)) == 0) {
				menuChoice = -1;
				printf("Not an integer!\n");
			}
			else {
				addResultCode = deleteItem(item, &rMsg);
				printf("%s\n", rMsg);
			}
			break;
		case 3: 
			reverseResultCode = reverseList(&rMsg);
			printf("%s\n", rMsg);
			break;
		case 4:
			printList();
			break;
		default:
			break;
		}
	}
	return 0;
}

int addNewItem(int addData, char **resultMsg) {
	printf("Trying to add a new item into the list!\n");
	int resultCode = 1;
	struct node *newNode;
	char *returnMessage = NULL;
	newNode = malloc(sizeof(struct node));
	if (newNode == NULL) {
		resultCode = 0;
		returnMessage = malloc(sizeof(errorMessage1)+1);
		sprintf(returnMessage, errorMessage1, addData);
	}

	if (resultCode == 1) {
		newNode->data = addData;
		newNode->next = NULL;

		if (head != NULL) {
			current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = newNode;
		}
		else {
			head = newNode;
		}
		returnMessage = malloc(sizeof(successMessage1) + 1);
		sprintf(returnMessage, successMessage1, addData);
	}

	*resultMsg = malloc(strlen(returnMessage));
	strcpy(*resultMsg, returnMessage);
	return resultCode;
}

int deleteItem(int deleteData, char **resultMsg) {
	printf("Trying to delete an item from the list!\n");
	int resultCode = 1;
	struct node *nodeToDelete = malloc(sizeof(struct node));
	char *returnMessage = NULL;
	current = head;
	temp = head;
	while (current != NULL && current->data != deleteData) {
		temp = current;
		current = current->next;
	}

	if (current == NULL) {
		resultCode = 0;
		returnMessage = malloc(sizeof(errorMessage2)+1);
		sprintf(returnMessage, errorMessage2, deleteData);
	}
	else {
		nodeToDelete = current;
		current = current->next;
		temp->next = current;
		if (nodeToDelete == head) {
			head = head->next;
			temp = NULL;
		}
		free(nodeToDelete);
		returnMessage = malloc(sizeof(successMessage2)+1);
		sprintf(returnMessage, successMessage2, deleteData);
	}

	*resultMsg = malloc(strlen(returnMessage));
	strcpy(*resultMsg, returnMessage);
	return resultCode;
}

void printList() {
	printf("\nPrinting List..\n");
	printf("--------------\n");
	current = head;
	while (current != NULL) {
		printf("%d\n", current->data);
		current = current->next;
	}
	printf("\n");
}

int reverseList(char **resultMsg) {
	printf("Reversing the list!\n");
	int resultCode = 1;
	char *returnMessage = NULL;
	if (head == NULL) {
		returnMessage = errorMessage4;
		*resultMsg = malloc(strlen(returnMessage));
		strcpy(*resultMsg, returnMessage);
		return 1;
	}
	struct node *prevNode = NULL;

	current = head;
	while (current != NULL) {
		temp = current->next;
		current->next = prevNode;
		prevNode = current;
		current = temp;
	}
	head = prevNode;
	returnMessage = successMessage3;

	*resultMsg = malloc(strlen(returnMessage));
	strcpy(*resultMsg, returnMessage);
	return resultCode;
}

int displayMenu() {
	int choice;
	int sReturn;
	printf("Menu\n");
	printf("------------\n");
	printf("\t1.Add\n");
	printf("\t2.Delete\n");
	printf("\t3.Reverse\n");
	printf("\t4.Print\n");
	printf("\t5.Exit\n");
	while (1) {
		printf("Enter Your Choice: ");
		if ((sReturn = scanf("%d", &choice)) == 0  ||
			(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)) {
			printf("Please Just Enter 1,2,3,4,5 as Your Choice!\n");
		}
		else {
			break;
		}
	}
	return choice;
}