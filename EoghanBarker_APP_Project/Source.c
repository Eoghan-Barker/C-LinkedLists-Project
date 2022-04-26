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
void displayNode(nodeT* head, int location);
void updateClient(nodeT* head, int location);
void deleteClient(nodeT** head, int location);
void statistics(nodeT* head);
void outputToFile(nodeT* head);
void clientsInOrder(nodeT* head);

void main() {
	nodeT* head = NULL;
	int choice = 0;
	int regSearch;
	int location;

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
			printf("Enter registration number of client you wish to display details: \n");
			scanf("%d", &regSearch);

			location = searchList(head, regSearch);

			if (location > -1) {
				displayNode(head, location);
			}
			else {
				printf("Registration number does not exist\n");
			}
			
			break;
		case 4:
			printf("Enter registration number of client you wish to update: \n");
			scanf("%d", &regSearch);

			location = searchList(head, regSearch);

			if (location > -1) {
				updateClient(head, location);
			}
			else {
				printf("Registration number does not exist\n");
			}
			break;
		case 5:
			printf("Enter registration number of client you wish to delete: \n");
			scanf("%d", &regSearch);

			location = searchList(head, regSearch);

			if (location > -1) {
				deleteClient(&head, location);
			}
			else {
				printf("Registration number does not exist\n");
			}
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
	scanf("%d", &newNode->areaOfSales);

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
	int counter = 1;

	while (temp != NULL)
	{
		printf("\nClient %d\n", counter);
		printf("%d %s %s %d %s %s %d %d %d %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat, temp->avgTurnover, temp->staffStat, temp->areaOfSales);


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

void displayNode(nodeT* head, int location) {
	nodeT* temp = head;

	for (int i = 0; i < location; i++) {
		if (temp->NEXT == NULL) break;
		temp = temp->NEXT;
	}

	printf("%d %s %s %d %s %s %d %d %d %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat, temp->avgTurnover, temp->staffStat, temp->areaOfSales);
}

void updateClient(nodeT* head, int location){
	nodeT* temp = head;

	for (int i = 0; i < location; i++) {
		temp = temp->NEXT;
	}

	printf("Enter company registration number, name, country, and year founded: \n");
	scanf("%d %s %s %d", &temp->regNum, temp->name, temp->country, &temp->founded);
	printf("Enter company email and contact name:\n");
	scanf("%s %s", temp->email, temp->contact);
	printf("Enter the company's last order, number of employees, and average annual order\n");
	scanf("%d %d %f", &temp->lastOrder, &temp->numEmployees, &temp->avgOrder);
	printf("Is the client VAT registered?(0= yes, 1 = no)\n");
	scanf("%d", &temp->isVat);
	printf("What are the client's average turnover?(1 = < £1 million, 2 = < £10 million, 3 = > £10 million)\n");
	scanf("%d", &temp->avgTurnover);
	printf("How many staff are employed by the company?(1 = < 10, 2 = < 100, 3 = > 100)\n");
	scanf("%d", &temp->staffStat);
	printf("What area of sales is the company in?(1 = ICT, 2 = Medical Devices, 3 = other)\n");
	scanf("%d", &temp->areaOfSales);

}

void deleteClient(nodeT** head, int location){
	nodeT* temp = *head;
	nodeT* prev = NULL;
	int i;

	for (i = 0; i < location; i++)
	{
		prev = temp;
		temp = temp->NEXT;
	}

	//check if start, middle or end of list
	if (temp->NEXT == NULL) {
		prev->NEXT = NULL;
	}
	else if (location == 0) {
		*head = (*head)->NEXT;
	}
	else {
		prev->NEXT = temp->NEXT;
	}

	free(temp);
}

void statistics(nodeT* head) {
	nodeT* temp = head;
	int type = 0;
	int selection;
	int count = 0;
	int stats[3] = { 0,0,0 };

	do {
		printf("Do you want statistics to be generated by 1. Area of company sales or 2. Number of Employees\n");
		scanf("%d", &type);

		switch (type) {
		case 1:
			printf("Select Area of Sales 1. ICT, 2. Medical Devices, 3. Other: \n");
			scanf("%d", &selection);

			while (temp != NULL) {

				if (temp->areaOfSales == selection) {
					if (temp->avgTurnover == 1) stats[0]++;
					if (temp->avgTurnover == 2) stats[1]++;
					if (temp->avgTurnover == 3) stats[2]++;
					
					count++;
				}

				temp = temp->NEXT;
			}

			break;
		case 2:
			printf("Select Number of Employees 1. Less than 10, 2. Less than 100, 3. Greater than 100: \n");
			scanf("%d", &selection);

			while (temp != NULL) {

				if (temp->staffStat == selection) {
					if (temp->avgTurnover == 1) stats[0]++;
					if (temp->avgTurnover == 2) stats[1]++;
					if (temp->avgTurnover == 3) stats[2]++;
					count++;
				}

				temp = temp->NEXT;
			}

			break;
		default:
			printf("Invalid input(must be 1 or 2)");
			break;
		}
	} while (type != 1 && type != 2);

	printf("Less than 1 Millon: %.2f%%\n", ((stats[0]/(float)count)*100.0));
	printf("Less than 10 Millon: %.2f%%\n", ((stats[1]/ (float)count)*100.0));
	printf("Greater than 10 Millon: %.2f%%\n\n", ((stats[2]/ (float)count)*100.0));
}

void outputToFile(nodeT* head){
	nodeT* temp = head;
	FILE* fp;

	fp = fopen("clients.txt", "w");

	while (temp != NULL)
	{
		if (fp != NULL)
		{
			fprintf(fp, "%d %s %s %d %s %s %d %d %d %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat, temp->avgTurnover, temp->staffStat, temp->areaOfSales);
		}
		temp = temp->NEXT;
	}

	if (fp != NULL)
	{
		fclose(fp);
	}
}

void clientsInOrder(nodeT* head){
	nodeT* temp = head;
	int location = 0;

	for (int i = 3; i > 0; i--) {
		temp = head;
		while (temp != NULL) {
			location = 0;
			if (temp->avgTurnover == i) displayNode(temp, location);

			location++;
			temp = temp->NEXT;
		}
	}
}