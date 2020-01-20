#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "contacts.h"
#include "contactHelpers.h"

void getName(struct Name *name) {
	int YorN = 0; 
	char midIni;

	printf("Please enter the contact's first name: ");
	scanf(" %30[^\n]", name->firstName);

	printf("Do you want to enter a middle initial(s)? (y or n): ");
	YorN = yes(); 
	if (YorN == 1) {
		printf("Please enter the contact's middle initial(s): ");
		scanf(" %6[^\n]%c", name->middleInitial, &midIni); 
		if (midIni != '\n') 
			clearKeyboard();		
	}
	else 
		*name->middleInitial = '\0'; 
	printf("Please enter the contact's last name: ");
	scanf(" %35[^\n]", name->lastName);
}

void getAddress(struct Address *address) {
	int YorN = 0;
	char pCode;

	printf("Please enter the contact's street number: ");
	address->streetNumber = getInt();

	while (address->streetNumber <= 0) {
		printf("*** INVALID STREET NUMBER *** <must be a positive number>: "); 	
		address->streetNumber = getInt(); 
	}

	printf("Please enter the contact's street name: ");
	scanf(" %40[^\n]", address->street);
	printf("Do you want to enter an apartment number? (y or n): ");
	YorN = yes();

	if (YorN == 1) {
		printf("Please enter the contact's apartment number: ");
		address->apartmentNumber = getInt();
		while (address->apartmentNumber <= 0) {
			printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");			
			address->apartmentNumber = getInt();
		}
	}
	else 
		address->apartmentNumber = '\0';	
	printf("Please enter the contact's postal code: ");
	scanf(" %7[^\n]%c", address->postalCode, &pCode);

	if (pCode != '\n') 
		clearKeyboard();
	printf("Please enter the contact's city: ");
	scanf(" %40[^\n]", address->city);
}

void getNumbers(struct Numbers *numbers) {
	int YorN = 0;
	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell); 

	printf("Do you want to enter a home phone number? (y or n): ");
	YorN = yes();

	if (YorN == 1) {
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}
	else 
		*numbers->home = '\0';
	printf("Do you want to enter a business phone number? (y or n): ");
	YorN = yes();
	if (YorN == 1) {
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}
	else 
		*numbers->business = '\0';
	
}

void getContact(struct Contact *contact) {
	getName(&(*contact).name);
	getAddress(&(*contact).address);
	getNumbers(&(*contact).numbers);
}