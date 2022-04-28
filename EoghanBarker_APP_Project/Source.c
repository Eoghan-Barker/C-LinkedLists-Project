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

nodeT* createNode(int reg);
void addClientStart(nodeT** head, int reg);
void addClientEnd(nodeT* head, int reg);
char* validEmail(char* email);
void displayList(nodeT* head);
int searchList(nodeT* head, int reg);
void displayNode(nodeT* head, int location);
void updateClient(nodeT* head, int location);
void deleteClient(nodeT** head, int location);
void statistics(nodeT* head);
void outputToFile(nodeT* head);
void clientsInOrder(nodeT* head);
int userLogin();
int loadDatabase(nodeT** head);
int openFile(int mode);
void closeFile();

FILE* fptr = NULL;

void main() {
	nodeT* head = NULL;
	int choice = 0;
	int regSearch;
	int location;
	int login = 0;
	int loadSuccess = 0;

	login = userLogin();

	while (login != 1) {
		printf("Incorrect username or password, try again\n");
		login = userLogin();
	}

	printf("Welcome to the XYX Medical Supplier client record\n");


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
		printf("Enter 9 to load an existing database in from a local file\n");
		printf("Enter -1 to exit\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Enter registration number(must be unique):\n");
			scanf("%d", &regSearch);

			location = searchList(head, regSearch);

			if (location > -1) {
				printf("Registration number already exists\n");
				break;
			}

			if (head == NULL) {
				addClientStart(&head, regSearch);
			}
			else {
				addClientEnd(head, regSearch);
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
		case 9:
			loadSuccess = loadDatabase(&head);

			if (loadSuccess != 1) {
				printf("Error loading file\n");
			}
			else
			{
				printf("Database loaded successfully\n");
			}
			break;
		case -1:
			break;
		default:
			printf("invlaid selection\n");
			break;
		}
	}
}

nodeT* createNode(int reg) {
	nodeT* newNode;
	char newEmail[30];

	newNode = (nodeT*)malloc(sizeof(nodeT));
	newNode->regNum = reg;
	printf("Enter company name, country, and year founded: \n");
	scanf("%s %s %d",  newNode->name, newNode->country, &newNode->founded);
	printf("Enter company email:\n");
	scanf("%s", newEmail);
	strcpy(newNode->email, validEmail(newEmail));
	printf("Enter company contact name:\n");
	scanf("%s", newNode->contact);
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

char* validEmail(char* email) {
	char* at;
	char* com;
	char newEmail[30];
	int isValid = 0;

	at = strstr(email, "@");
	com = strstr(email, ".com");

	if (at != NULL && com != NULL) {
		isValid = 1;
		strcpy(newEmail, email);
	}

	while (isValid == 0) {
		printf("Not a vaild email(must contain @ and .com)\n");
		printf("Enter new email\n");
		scanf("%s", newEmail);

		at = strstr(newEmail, "@");
		com = strstr(newEmail, ".com");

		if (at != NULL && com != NULL) isValid = 1;
	}

	return newEmail;
}

void addClientStart(nodeT** head, int reg) {
	nodeT* newNode = NULL;

	newNode = createNode(reg);
	newNode->NEXT = *head;
	*head = newNode;
}

void addClientEnd(nodeT* head, int reg){
	nodeT* temp = head;
	nodeT* newNode;

	newNode = createNode(reg);


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
	char turnoverLabel[3][30] = { "Less than e1 Million", "Less than e10 Million", "Over e10 Million" };
	char staffLabel[3][30] = { "Less than 10", "Less than 100", "Over 100" };
	char salesLabel[3][30] = { "ICT", "Medical Devices", "Other Area" };

	while (temp != NULL)
	{
		printf("\nClient %d\n", counter);
		printf("%d %s %s %d %s %s %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat);
		printf("%s \n%s \n%s \n", turnoverLabel[temp->avgTurnover - 1], staffLabel[temp->staffStat - 1], salesLabel[temp->areaOfSales - 1]);


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
	char turnoverLabel[3][30] = { "Less than e1 Million", "Less than e10 Million", "Over e10 Million" };
	char staffLabel[3][30] = { "Less than 10", "Less than 100", "Over 100" };
	char salesLabel[3][30] = { "ICT", "Medical Devices", "Other Area" };

	for (int i = 0; i < location; i++) {
		if (temp->NEXT == NULL) break;
		temp = temp->NEXT;
	}

	printf("%d %s %s %d %s %s %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat);
	printf("%s \n%s \n%s \n", turnoverLabel[temp->avgTurnover - 1], staffLabel[temp->staffStat - 1], salesLabel[temp->areaOfSales - 1]);
}

void updateClient(nodeT* head, int location){
	nodeT* temp = head;
	char newEmail[30];

	for (int i = 0; i < location; i++) {
		temp = temp->NEXT;
	}

	printf("Enter company name, country, and year founded: \n");
	scanf("%s %s %d", temp->name, temp->country, &temp->founded);
	printf("Enter company email:\n");
	scanf("%s", newEmail);
	strcpy(temp->email, validEmail(newEmail));
	printf("Enter company contact name:\n");
	scanf("%s", temp->contact);
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

int userLogin() {
	char newUsername[30];
	char newPassword[30];
	char validUsername[30];
	char validPassword[30];
	char ch;
	int success = 0;
	int i;

	printf("Enter username: \n");
	scanf("%s", newUsername);
	printf("Enter password: \n");
	for (i = 0; i < 100; i++)
	{
		ch = getch();
		// break on return character
		if (ch == 13)
			break;
		newPassword[i] = ch;
		ch = '*';
		printf("%c ", ch);
	}
	// end string
	newPassword[i] = '\0';

	if (openFile(1) == 1) {
		for (int i = 0; i < 3; i++) {
			fscanf(fptr, "%s %s\n", validUsername, validPassword);

			if (strcmp(newUsername, validUsername) == 0 && strcmp(newPassword, validPassword) == 0) {
				success = 1;
			}
		}
	}

	return success;
}

int loadDatabase(nodeT** head) {
	nodeT* newNode = NULL;
	nodeT* temp = NULL;

	if (openFile(2) != 1) return 0;

	while (!feof(fptr)) {
		newNode = (nodeT*)malloc(sizeof(nodeT));
		fscanf(fptr, "%d %s %s %d %s %s %d %d %d %d %d %d\n", &newNode->regNum, newNode->name, newNode->country, &newNode->founded, newNode->email, newNode->contact, &newNode->lastOrder, &newNode->numEmployees, &newNode->isVat, &newNode->avgTurnover, &newNode->staffStat, &newNode->areaOfSales);

		if (*head == NULL) {
			newNode->NEXT = *head;
			*head = newNode;
		}
		else
		{
			temp = *head;
			while (temp->NEXT != NULL) {
				temp = temp->NEXT;
			}

			newNode->NEXT = NULL;
			temp->NEXT = newNode;
		}
	}
	return 1;
}

//if mode is 0 = w mode
//mode 1 = r mode
int openFile(int mode) {
	int result;

	if (mode == 0) {
		fptr = fopen("clients.txt", "w");
	}
	else if(mode == 1) {
		fptr = fopen("login.txt", "r");
	}
	else {
		fptr = fopen("clients.txt", "r");
	}

	if (fptr == NULL)
	{
		printf("Error opening file");
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

void closeFile() {
	fclose(fptr);
}