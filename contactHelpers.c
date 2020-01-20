#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "string.h"
#include "contactHelpers.h"

#define MAXCONTACTS 5

void clearKeyboard(void) {
	while (getchar() != '\n'); 
}

void pause(void) {
	printf("\n");
	printf("(Press Enter to Continue)"); 
	clearKeyboard();
}

int getInt(void) {
	int val = 0;
	char invInt;
	scanf("%d%c", &val, &invInt);
	while (invInt != '\n') {
		clearKeyboard();
		printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		scanf("%d%c", &val, &invInt);
	}
	return val;
}

int getIntInRange(int low, int high) {
	int val = 0;
	val = getInt();
	while (val < low || val > high) {
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", low, high);
		val = getInt();
	}
	return val;
}

int yes(void) {
	char YorN;
	char newl;
	scanf(" %c%c", &YorN, &newl);
	while (!(YorN == 'y' || YorN == 'Y' || YorN == 'N' || YorN == 'n') || newl != '\n')	{
		if (newl != '\n') 
			clearKeyboard();
		printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: "); // This part pops up whene there is a wrong inputted value instead of Y or n or New Line (newl).
		scanf(" %c%c", &YorN, &newl);
	}
	if (YorN == 'y' || YorN == 'Y') 
		return 1;
	return 0;
}

int menu(void) {
	int value = 0;

	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\nSelect an option:> ");
	value = getIntInRange(0, 6);
	printf("\n");

	return value;
}

void contactManagerSystem(void) {
	int pick = 1;
	int rreturn = 0;

	struct Contact contacts[MAXCONTACTS] = {
		{ { "Niaz", { '\0' }, "Haque" },
	{ 75, "Graydon Hall", 0, "M3A 3M5", "Toronto" },
	{ "4163911447", "2223334444", "3334445555" } },
	{
		{ "Marshal", { '\0' }, "Matthers" },
	{ 55, "Beverly Hills", 0, "A9A 3K3", "Los Angeles" },
	{ "9051112222", "9052223333", "9053334444" } },
	{
		{ "Brian", "A.", "Jones" },
	{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
	{ "7051112222", "7052223333", "7053334444" } },
	{
		{ "Sasha", { '\0' }, "Williams" },
	{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
	{ "9052223333", "9052223333", "9054445555" } },
	};

	while (rreturn != 1) {
		pick = menu(); 
		switch (pick) {
		case 0:
			printf("Exit the program? (Y)es/(N)o: ");
			rreturn = yes();
			printf("\n");
			break;
		case 1:
			displayContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 2:
			addContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 3:
			updateContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 4:
			deleteContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 5:
			searchContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 6:
			sortContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		}
	}
	printf("Contact Management System: terminated\n");
}

void getTenDigitPhone(char phoneNum[]) {
	int userInp = 1;
	while (userInp == 1) {
		scanf("%10s", phoneNum);
		clearKeyboard();
		if (strlen(phoneNum) == 10 && strspn(phoneNum, "0123456789") == strlen(phoneNum)) // If other then 0-9 is inputted, it will be wrong or more than the desired numbers of character is inputted. So need to input again.
			userInp = 0;
		else
			printf("Enter a 10-digit phone number: ");
	}
}

int findContactIndex(const struct Contact contact[], int size, const char cellNum[]) {
	int val = 0;
	int i = 0;
	for (i = 0; i < size; i++) {
		if (strcmp(cellNum, contact[i].numbers.cell) == 0) {
			val = i;
			return val;
		}
	}
	return -1;
}

void displayContactHeader() {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}

void displayContactFooter(int count) {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n", count);
}

void displayContact(const struct Contact* contact) {
	if (strlen(contact->name.middleInitial) > 0) {
		printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
		printf("    C: %10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);
		if (contact->address.apartmentNumber > 0) 
			printf("       %d %s, Apt# %d, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.apartmentNumber, contact->address.city, contact->address.postalCode);
		else 
			printf("       %d %s, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.city, contact->address.postalCode);
	}
	else {
		printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
		printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);
		if (contact->address.apartmentNumber > 0) 
			printf("       %d %s, Apt# %d, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.apartmentNumber, contact->address.city, contact->address.postalCode);
		else 
			printf("       %d %s, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.city, contact->address.postalCode);
	}
}

void displayContacts(const struct Contact contacts[], int size) {
	int i = 0;
	int count = 0; 
	displayContactHeader();

	for (i = 0; i < size; i++) {
		if (strlen(contacts[i].numbers.cell) > 0) {
			displayContact(&contacts[i]);
			count++;
		}
	}
	displayContactFooter(count);
}

void searchContacts(const struct Contact contacts[], int size) {
	int i = -1;
	char num[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(num);

	i = findContactIndex(contacts, MAXCONTACTS, num);
	if (i > 0) {
		printf("\n");
		displayContact(&contacts[i]);
	}
	else 
		printf("*** Contact NOT FOUND ***\n");
}

void addContact(struct Contact contacts[], int size) {
	int i = 0;
	int noNumb = -5;

	for (i = 0; i < size; i++) {
		if (strlen(contacts[i].numbers.cell) == 0)
			noNumb = i;
	}
	if (noNumb == -5) 
		printf("*** ERROR: The contact list is full! ***\n");
	else {
		getContact(&contacts[noNumb]);
		printf("--- New contact added! ---\n");
	}
}

void updateContact(struct Contact contacts[], int size) {
	int i = -1;
	char num[11];
	int YorN = 0; 
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(num);
	i = findContactIndex(contacts, size, num);

	if (i == -1) 
		printf("*** Contact NOT FOUND ***\n");
	else {
		printf("\nContact found:\n");
		displayContact(&contacts[i]);
		printf("\n");
		printf("Do you want to update the name? (y or n): ");
		YorN = yes();

		if (YorN == 1) 
			getName(&contacts[i].name);
		printf("Do you want to update the address? (y or n): ");
		YorN = yes();

		if (YorN == 1) 
			getAddress(&contacts[i].address);		
		printf("Do you want to update the numbers? (y or n): ");
		YorN = yes();

		if (YorN == 1) 
			getNumbers(&contacts[i].numbers);
		printf("--- Contact Updated! ---\n");
	}
}

void deleteContact(struct Contact contacts[], int size) {
	int i = -5; 
	char num[11];
	int YorN = 0;

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(num);
	i = findContactIndex(contacts, size, num);

	if (i == -5) 
		printf("*** Contact NOT FOUND ***\n");
	else {
		printf("\nContact found:\n");
		displayContact(&contacts[i]);
		printf("\n");
		printf("CONFIRM: Delete this contact? (y or n): ");
		YorN = yes();
		if (YorN == 1) {
			*contacts[i].numbers.cell = '\0';
			printf("--- Contact deleted! ---\n");
		}
	}
}

void sortContacts(struct Contact contacts[], int size) {
	int i = 0;
	int t = 0;
	struct Contact hold;
	for (t = 0; t < size; t++) {
		for (i = 0; i < size; i++) {
			if (strcmp(contacts[i].numbers.cell, contacts[t].numbers.cell) > 0) {
				if (strlen(contacts[i].numbers.cell) > 0 && strlen(contacts[t].numbers.cell) > 0) {
					hold = contacts[i];
					contacts[i] = contacts[t];
					contacts[t] = hold;
				}
			}
		}
	}
	printf("--- Contacts sorted! ---\n");
}