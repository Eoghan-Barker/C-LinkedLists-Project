#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {

	int regNum;
	char name[30];
	char country[20];
	int founded;
	char email[30];
	char contact[30];
	int lastOrder;
	int numEmployees;
	float avgOrder;
	int isVat;
	int avgTurnover;
	int staffStat;
	int areaOfSales;

	struct node* NEXT;
}nodeT;

nodeT* createNode();
void addClientStart(nodeT** head);
void addClientEnd(nodeT* head);
void displayList(nodeT* head);
int searchList(nodeT* head, int reg);
void updateClient(nodeT* head);
void deleteClient(nodeT* head);
void statistics(nodeT* head);
void outputToFile(nodeT* head);
void clientsInOrder(nodeT* head);

void main() {
	nodeT* head = NULL;
	int choice = 0;
	int regSearch;

	while (choice != -1)
	{
		printf("Enter 1 to add a client\n");
		printf("Enter 2 to display all client details\n");
		printf("Enter 3 to display a specified client's details\n");
		printf("Enter 4 to update a client's details\n");
		printf("Enter 5 to delete a client\n");
		printf("Enter 6 generate statistics\n");
		printf("Enter 7 to output all client details to a report file\n");
		printf("Enter 8 to list all clients in order of their last average turnover\n");
		printf("Enter -1 to exit\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			if (head == NULL) {
				addClientStart(&head);
			}
			else {
				addClientEnd(head);
			}
			break;
		case 2:
			displayList(head);
			break;
		case 3:
			searchList(head, regSearch);
			break;
		case 4:
			updateClient(head);
			break;
		case 5:
			deleteClient(head);
			break;
		case 6:
			statistics(head);
			break;
		case 7:
			outputToFile(head);
			break;
		case 8:
			clientsInOrder(head);
			break;
		case -1:
			break;
		default:
			printf("invlaid selection\n");
			break;
		}
	}
}

nodeT* createNode() {
	nodeT* newNode;


	newNode = (nodeT*)malloc(sizeof(nodeT));
	printf("Enter company registration number, name, country, and year founded: \n");
	scanf("%d %s %s %d", &newNode->regNum, newNode->name, newNode->country, &newNode->founded);
	printf("Enter company email and contact name:\n");
	scanf("%s %s", newNode->email, newNode->contact);
	printf("Enter the company's last order, number of employees, and average annual order\n");
	scanf("%d %d %f", &newNode->lastOrder, &newNode->numEmployees, &newNode->avgOrder);
	printf("Is the client VAT registered?(0= yes, 1 = no)\n");
	scanf("%d", &newNode->isVat);
	printf("What are the client's average turnover?(1 = < £1 million, 2 = < £10 million, 3 = > £10 million)\n");
	scanf("%d", &newNode->avgTurnover);
	printf("How many staff are employed by the company?(1 = < 10, 2 = < 100, 3 = > 100)\n");
	scanf("%d", &newNode->staffStat);
	printf("What area of sales is the company in?(1 = ICT, 2 = Medical Devices, 3 = other)\n");
	scanf("%d", &newNode->isVat);

	return newNode;
}

void addClientStart(nodeT** head) {
	nodeT* newNode = NULL;

	newNode = createNode();

	newNode->NEXT = *head;
	*head = newNode;
}

void addClientEnd(nodeT* head){
	nodeT* temp = head;
	nodeT* newNode;

	newNode = createNode();


	while (temp->NEXT != NULL)
	{
		temp = temp->NEXT;
	}

	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}

void displayList(nodeT* head){
	nodeT* temp = head;
	int counter = 0;

	while (temp != NULL)
	{
		printf("\nClient %d\n", counter);
		printf("%d %s %s %d %s %s %d %d %f %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat, temp->avgTurnover, temp->staffStat, temp->areaOfSales);


		temp = temp->NEXT;
		counter++;
	}
}

int searchList(nodeT* head, int reg){
	nodeT* temp = head;
	int found = -1;
	int count = 0;

	while (temp != NULL)
	{
		if (reg == temp->regNum)
		{
			found = count;
		}

		temp = temp->NEXT;
		count++;
	}

	return found;
}

void updateClient(nodeT* head){

}

void deleteClient(nodeT* head){

}

void statistics(nodeT* head) {

}

void outputToFile(nodeT* head){

}

void clientsInOrder(nodeT* head){

}