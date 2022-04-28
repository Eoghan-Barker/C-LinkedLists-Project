//G00397072 - Eoghan Barker
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// client nodes for database linked list
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

FILE* fptr = NULL;

// Calls user login and has a menu for user to work with the database
void main() {
	nodeT* head = NULL;
	int choice = 0;
	int regSearch;
	int location;
	int login = 0;
	int loadSuccess = 0;

	// if login successful login = 1
	login = userLogin();

	// continue to ask user for login details until they enter valid username and password
	while (login != 1) {
		printf("Incorrect username or password, try again\n");
		login = userLogin();
	}

	printf("Welcome to the XYX Medical Supplier client record\n");

	// print menu until user enters -1
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
		// add client
		case 1:
			// reg number must be unique
			// ask for regnumber here and search for it in the list 
			// to verify uniqueness before creating a new node
			printf("Enter registration number(must be unique):\n");
			scanf("%d", &regSearch);

			// returns -1 if ID not in list else returns position it appears in list
			location = searchList(head, regSearch);

			if (location > -1) {
				printf("Registration number already exists\n");
				break;
			}

			// check if list is empty to see if node should be added to start or end of list
			if (head == NULL) {
				addClientStart(&head, regSearch);
			}
			else {
				addClientEnd(head, regSearch);
			}
			break;
		// print entire list if list is not empty
		case 2:
			if (head == NULL) {
				printf("List is empty\n");
			}
			else {
				displayList(head);
			}
			break;
		// print specified node
		case 3:

			// Check if list is empty
			if (head == NULL) {
				printf("List is empty\n");
				break;
			}

			printf("Enter registration number of client you wish to display details: \n");
			scanf("%d", &regSearch);

			// Search if reg number exists, returns -1 if not
			location = searchList(head, regSearch);

			// Ensure node exists
			if (location > -1) {
				displayNode(head, location);
			}
			else {
				printf("Registration number does not exist\n");
			}
			
			break;
		// update node
		case 4:
			// Check if list is empty
			if (head == NULL) {
				printf("List is empty\n");
				break;
			}

			printf("Enter registration number of client you wish to update: \n");
			scanf("%d", &regSearch);

			// Search if list
			location = searchList(head, regSearch);

			if (location > -1) {
				updateClient(head, location);
			}
			else {
				printf("Registration number does not exist\n");
			}
			break;
		// delete node
		case 5:
			// Check if list is empty
			if (head == NULL) {
				printf("List is empty\n");
				break;
			}

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
		// print stats
		case 6:
			// Check if list is empty
			if (head == NULL) {
				printf("List is empty\n");
				break;
			}

			statistics(head);
			break;
		// output list data to file
		case 7:
			// Check if list is empty
			if (head == NULL) {
				printf("List is empty\n");
				break;
			}

			outputToFile(head);
			break;
		// print list in order of average turnover
		case 8:
			// Check if list is empty
			if (head == NULL) {
				printf("List is empty\n");
				break;
			}

			clientsInOrder(head);
			break;
		// read data from file into list
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

// Creates a new node and asks user for all the node's data
// args - registration number as int
// returns - node pointer
nodeT* createNode(int reg) {
	nodeT* newNode;
	char newEmail[30];

	// allocate correct memory to node
	newNode = (nodeT*)malloc(sizeof(nodeT));
	// copy user entered reg to node data(uniqness checked in main)
	newNode->regNum = reg;
	printf("Enter company name, country, and year founded: \n");
	scanf("%s %s %d",  newNode->name, newNode->country, &newNode->founded);
	printf("Enter company email:\n");
	// call validEmail which returns a string and copy it into node data
	scanf("%s", newEmail);
	strcpy(newNode->email, validEmail(newEmail));

	printf("Enter company contact name:\n");
	scanf("%s", newNode->contact);
	printf("Enter the company's last order, number of employees, and average annual order\n");
	scanf("%d %d %f", &newNode->lastOrder, &newNode->numEmployees, &newNode->avgOrder);

	// These inputs need Validation
	printf("Is the client VAT registered?(0= yes, 1 = no)\n");
	scanf("%d", &newNode->isVat);
	
	while (newNode->isVat < 0 || newNode->isVat > 1) {
		printf("Invalid input\n");
		printf("Is the client VAT registered?(0= yes, 1 = no)\n");
		scanf("%d", &newNode->isVat);
	}

	printf("What are the client's average turnover?(1 = < £1 million, 2 = < £10 million, 3 = > £10 million)\n");
	scanf("%d", &newNode->avgTurnover);

	while (newNode->avgTurnover < 1 || newNode->avgTurnover > 3) {
		printf("Invalid input\n");
		printf("What are the client's average turnover?(1 = < £1 million, 2 = < £10 million, 3 = > £10 million)\n");
		scanf("%d", &newNode->avgTurnover);
	}

	printf("How many staff are employed by the company?(1 = < 10, 2 = < 100, 3 = > 100)\n");
	scanf("%d", &newNode->staffStat);

	while (newNode->staffStat < 1 || newNode->staffStat > 3) {
		printf("Invalid input\n");
		printf("How many staff are employed by the company?(1 = < 10, 2 = < 100, 3 = > 100)\n");
		scanf("%d", &newNode->staffStat);
	}
	printf("What area of sales is the company in?(1 = ICT, 2 = Medical Devices, 3 = other)\n");
	scanf("%d", &newNode->areaOfSales);

	while (newNode->areaOfSales < 1 || newNode->areaOfSales > 3) {
		printf("Invalid input\n");
		printf("What area of sales is the company in?(1 = ICT, 2 = Medical Devices, 3 = other)\n");
		scanf("%d", &newNode->areaOfSales);
	}

	return newNode;
}

// Ensures user enters email containing "@" and ".com"
// args - email as string
// returns - email as string
char* validEmail(char* email) {
	char* at;
	char* com;
	char newEmail[30];
	int isValid = 0;

	// find position of '@' and '.com' sunstrings in email(NULL if don't exist)
	at = strstr(email, "@");
	com = strstr(email, ".com");

	// is valid if both substrings exist
	// copy email into newEmail for return
	if (at != NULL && com != NULL) {
		isValid = 1;
		strcpy(newEmail, email);
	}

	// ask user to enter new email until valid
	while (isValid == 0) {
		printf("Not a vaild email(must contain @ and .com)\n");
		printf("Enter new email\n");
		scanf("%s", newEmail);

		// check new input for substrings
		at = strstr(newEmail, "@");
		com = strstr(newEmail, ".com");

		if (at != NULL && com != NULL) isValid = 1;
	}

	return newEmail;
}

// call createNode(), link head pointer to new node, and point newNode.next to null
// args - head of linked list as node double pointer, registration number as int
void addClientStart(nodeT** head, int reg) {
	nodeT* newNode = NULL;

	newNode = createNode(reg);
	newNode->NEXT = *head;
	*head = newNode;
}

// call createNode(), traverse to end of list, 
// make last node point to new node and newnode point to null
// args - head of linked list as node pointer
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

// Print all data for each node in list
// args - head of linked list as node pointer
void displayList(nodeT* head){
	nodeT* temp = head;
	int counter = 1;
	// Labels for converting user inputs as int into relevent string data
	char turnoverLabel[3][30] = { "Less than e1 Million", "Less than e10 Million", "Over e10 Million" };
	char staffLabel[3][30] = { "Less than 10", "Less than 100", "Over 100" };
	char salesLabel[3][30] = { "ICT", "Medical Devices", "Other Area" };

	// print all nodes until end of list is reached
	while (temp != NULL)
	{
		printf("\nClient %d\n", counter);
		printf("%d %s %s %d %s %s %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat);
		printf("%s \n%s \n%s \n", turnoverLabel[temp->avgTurnover - 1], staffLabel[temp->staffStat - 1], salesLabel[temp->areaOfSales - 1]);


		temp = temp->NEXT;
		counter++;
	}
}

// Search for an node's reg num in the list
// Args - head of list as node pointer, reg number as int
// Returns - Position of node in list if found, else -1
int searchList(nodeT* head, int reg){
	nodeT* temp = head;
	int found = -1;
	int count = 0;

	// Traverse list and do checks until end of list
	while (temp != NULL)
	{
		// If reg num is found, save the position for returning
		if (reg == temp->regNum)
		{
			found = count;
		}

		temp = temp->NEXT;
		count++;
	}

	return found;
}

// Displays data of one node at user specified position in list
// Args - head pointer, Postion of node as int
void displayNode(nodeT* head, int location) {
	nodeT* temp = head;
	// Labels for printing relevant string data from int stored in the struct
	char turnoverLabel[3][30] = { "Less than e1 Million", "Less than e10 Million", "Over e10 Million" };
	char staffLabel[3][30] = { "Less than 10", "Less than 100", "Over 100" };
	char salesLabel[3][30] = { "ICT", "Medical Devices", "Other Area" };

	// Traverse list until specified locaton is reached, break if NULL(other input validation done in main)
	for (int i = 0; i < location; i++) {
		if (temp->NEXT == NULL) break;
		temp = temp->NEXT;
	}

	printf("%d %s %s %d %s %s %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat);
	// Print labels instead of integers
	printf("%s \n%s \n%s \n", turnoverLabel[temp->avgTurnover - 1], staffLabel[temp->staffStat - 1], salesLabel[temp->areaOfSales - 1]);
}

// Allow user to update data for specified node(except for reg num)
// Args - head pointer, location of node to update as int
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

	// These inputs need Validation
	printf("Is the client VAT registered?(0= yes, 1 = no)\n");
	scanf("%d", &temp->isVat);

	while (temp->isVat < 0 || temp->isVat > 1) {
		printf("Invalid input\n");
		printf("Is the client VAT registered?(0= yes, 1 = no)\n");
		scanf("%d", &temp->isVat);
	}

	printf("What are the client's average turnover?(1 = < £1 million, 2 = < £10 million, 3 = > £10 million)\n");
	scanf("%d", &temp->avgTurnover);

	while (temp->avgTurnover < 1 || temp->avgTurnover > 3) {
		printf("Invalid input\n");
		printf("What are the client's average turnover?(1 = < £1 million, 2 = < £10 million, 3 = > £10 million)\n");
		scanf("%d", &temp->avgTurnover);
	}

	printf("How many staff are employed by the company?(1 = < 10, 2 = < 100, 3 = > 100)\n");
	scanf("%d", &temp->staffStat);

	while (temp->staffStat < 1 || temp->staffStat > 3) {
		printf("Invalid input\n");
		printf("How many staff are employed by the company?(1 = < 10, 2 = < 100, 3 = > 100)\n");
		scanf("%d", &temp->staffStat);
	}
	printf("What area of sales is the company in?(1 = ICT, 2 = Medical Devices, 3 = other)\n");
	scanf("%d", &temp->areaOfSales);

	while (temp->areaOfSales < 1 || temp->areaOfSales > 3) {
		printf("Invalid input\n");
		printf("What area of sales is the company in?(1 = ICT, 2 = Medical Devices, 3 = other)\n");
		scanf("%d", &temp->areaOfSales);
	}

}

// Delete a node from the list
// Args - head double pointer, location of node to delete as int
void deleteClient(nodeT** head, int location){
	nodeT* temp = *head;
	nodeT* prev = NULL;
	int i;

	// Traverse to specified location(validation done in main), store last and 2nd last nodes in list
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

	// free memory of deleted node
	free(temp);
}

// Prints statistics generated based on user inputs
// Stats are percentage of clients, in specified field/with number of employees, in the 3 different average turnover groups
// Args - head pointer
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

			// Traverse list
			while (temp != NULL) {

				// check if node is in relevent field
				if (temp->areaOfSales == selection) {
					// Count nodes based on avgTurnover
					if (temp->avgTurnover == 1) stats[0]++;
					if (temp->avgTurnover == 2) stats[1]++;
					if (temp->avgTurnover == 3) stats[2]++;
					
					//Only counts nodes that are relevent to the statistics
					count++;
				}

				temp = temp->NEXT;
			}

			break;
		case 2:
			printf("Select Number of Employees 1. Less than 10, 2. Less than 100, 3. Greater than 100: \n");
			scanf("%d", &selection);

			while (temp != NULL) {

				// check if node is in relevent field
				if (temp->staffStat == selection) {
					// Count nodes based on avgTurnover
					if (temp->avgTurnover == 1) stats[0]++;
					if (temp->avgTurnover == 2) stats[1]++;
					if (temp->avgTurnover == 3) stats[2]++;

					//Only counts nodes that are relevent to the statistics
					count++;
				}

				temp = temp->NEXT;
			}

			break;
		default:
			printf("Invalid input(must be 1 or 2)");
			break;
		}
	} while (type != 1 && type != 2); // loop back if invalid input

	// Print percentages
	printf("Less than 1 Millon: %.2f%%\n", ((stats[0]/(float)count)*100.0));
	printf("Less than 10 Millon: %.2f%%\n", ((stats[1]/ (float)count)*100.0));
	printf("Greater than 10 Millon: %.2f%%\n\n", ((stats[2]/ (float)count)*100.0));
}

// Open file and write data for each node to it
// Args - head pointer
void outputToFile(nodeT* head){
	nodeT* temp = head;
	FILE* fp;

	fp = fopen("clients.txt", "w");

	//Traverse list
	while (temp != NULL)
	{
		// check if file opened correctly
		if (fp != NULL)
		{
			fprintf(fp, "%d %s %s %d %s %s %d %d %d %d %d %d\n", temp->regNum, temp->name, temp->country, temp->founded, temp->email, temp->contact, temp->lastOrder, temp->numEmployees, temp->isVat, temp->avgTurnover, temp->staffStat, temp->areaOfSales);
		}
		temp = temp->NEXT;
	}

	// check if file opened correctly before trying to close
	if (fp != NULL)
	{
		fclose(fp);
	}
}

// Prints list in order of average turnover
void clientsInOrder(nodeT* head){
	nodeT* temp = head;
	int location = 0;

	// Start by printing nodes highest turnover bracket(3) then middle(2) then lowest(1)
	for (int i = 3; i > 0; i--) {
		// reset temp for list traversel 
		temp = head;
		// Traveres list
		while (temp != NULL) {
			// reset location
			location = 0;
			// if node is in correct bracket then print
			if (temp->avgTurnover == i) displayNode(temp, location);

			location++;
			temp = temp->NEXT;
		}
	}
}

// Ask user for login credentials and validate it from login.txt
// Masks password entry with '*' for each character
// Returns - 1 if credentials are vaild, else 0
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
	// Mask user password entry with '*'
	printf("Enter password: \n");
	// Use loop so that masking can stop when user hits enter
	for (i = 0; i < 30; i++)
	{
		// Holds user entered character so it can be replaced with * on screen
		ch = getch();
		// break on return character
		if (ch == 13)
			break;
		// save user entered char
		newPassword[i] = ch;
		ch = '*';
		// print *
		printf("%c ", ch);
	}
	// end string
	newPassword[i] = '\0';

	// Open login.txt, check if successful
	// 1 arg opens login.txt in 'r' mode
	if (openFile(1) == 1) {
		// login.txt contains 3 username/password pairs, loop 3 times to compare each one with user input
		for (int i = 0; i < 3; i++) {
			fscanf(fptr, "%s %s\n", validUsername, validPassword);

			if (strcmp(newUsername, validUsername) == 0 && strcmp(newPassword, validPassword) == 0) {
				success = 1;
			}
		}
	}

	// check if file opened correctly before trying to close
	if (fptr != NULL)
	{
		fclose(fptr);
	}

	return success;
}

// Load data from output.txt, store in linked list
// Args - head double pointer
// Returns - 0 if failed, else 1
int loadDatabase(nodeT** head) {
	nodeT* newNode = NULL;
	nodeT* temp = NULL;

	if (openFile(2) != 1) return 0;

	// Traverse file until end
	while (!feof(fptr)) {
		//Create new node and copy data into it
		newNode = (nodeT*)malloc(sizeof(nodeT));
		fscanf(fptr, "%d %s %s %d %s %s %d %d %d %d %d %d\n", &newNode->regNum, newNode->name, newNode->country, &newNode->founded, newNode->email, newNode->contact, &newNode->lastOrder, &newNode->numEmployees, &newNode->isVat, &newNode->avgTurnover, &newNode->staffStat, &newNode->areaOfSales);

		// check if file opened correctly before trying to close
		if (fptr != NULL)
		{
			fclose(fptr);
		}
		// check if adding too start or end of list
		if (*head == NULL) {
			// Head point to new node, newnode point to null
			newNode->NEXT = *head;
			*head = newNode;
		}
		else
		{
			// traverse to end of list
			temp = *head;
			while (temp->NEXT != NULL) {
				temp = temp->NEXT;
			}

			// last node points to newnode, new node points to null
			newNode->NEXT = NULL;
			temp->NEXT = newNode;
		}
	}
	return 1;
}

// if mode 0 = w mode, clients.txt
// if mode 1 = r mode, login.txt
// if mode 0 = r mode, clients.txt
// returns 1 if file opened successfully
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