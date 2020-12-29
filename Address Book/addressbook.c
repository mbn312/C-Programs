#include "addressbook.h"

Contact * getContact(int index, pContact *pTop) { /*gets contact at a given index*/
	int count = 0;

	Contact * pCursor = (*pTop); /*cursor starts at the top*/

	while (count != index) { /*while the cursor is not at the given index*/
		pCursor = pCursor->pNext; /*moves the cursor to the next node*/
		count++;
	}
	return pCursor;

}

char * getContactAsString(int index, pContact *pTop) { /*returns the contact in the form of a string*/
	Contact *contact = getContact(index, pTop); /*calls on the getContact method to get the contact at given index*/
	char *contactString = (char *) malloc(sizeof(Contact));
	/*creates a string and concatenates the field of the contact into the contact string separated by commas*/
	strcpy(contactString, contact->lastName);
	strcat(contactString, ",");
	strcat(contactString, contact->firstName);
	strcat(contactString, ",");
	strcat(contactString, contact->email);
	strcat(contactString, ",");
	strcat(contactString, contact->phoneNumber);

	return contactString; /*returns the contact string*/
}

int getCount(pContact *pTop) { /*gets the number of contacts*/
	int count = 0;
	Contact * cursor = (*pTop); /*cursor starts at the first contact*/
	while (cursor != NULL) { /*while the cursor has not reached the end of the list*/
		count++; /*increases count*/
		cursor = cursor->pNext; /*moves cursor to next contact*/
	}
	return count; /*returns count*/
}

Contact * createContact(char *contactInfo) { /*creates a contact with the specified values*/

	char *fields[4] = { strtok(contactInfo, ","), strtok(NULL, ","), strtok(
	NULL, ","), strtok(NULL, ",") };
	Contact * pContactNewContact = (Contact *) malloc(sizeof(Contact)); /*allocates the required amount of memory for the contact*/
	if (pContactNewContact && fields[3] != NULL) {
		/*copies the information into the corrects fields*/
		strcpy(pContactNewContact->lastName, fields[0]);
		strcpy(pContactNewContact->firstName, fields[1]);
		strcpy(pContactNewContact->email, fields[2]);
		strcpy(pContactNewContact->phoneNumber, fields[3]);
		/*creates the connections to both sides of contacts*/
		pContactNewContact->pPrev = NULL;
		pContactNewContact->pNext = NULL;
	}
	return pContactNewContact;

}

void addContact(char *contactInfo, int index, pContact * pTop) { /*adds contact to list*/
	Contact * pContactNew = createContact(contactInfo); /*creates a contact by calling on the create Contact method*/
	Contact * pCPrev;
	int size = getCount(pTop);
	if (strcmp(pContactNew->firstName, "") != 0) {
		if (index <= size) {
			if (index == 0) { /*if placing at the top of the list*/
				pCPrev = NULL; /*previous contact would be NULL*/
				pContactNew->pPrev = pCPrev;
				pContactNew->pNext = (*pTop); /*next contact would be the previous contact at top of list*/
				if ((*pTop)) { /*if the list isn't empty*/
					(*pTop)->pPrev = pContactNew;
				}
				(*pTop) = pContactNew; /*sets new contact as the top of the list*/
			} else { /*if not placing at top of the list*/
				pCPrev = getContact(index - 1, pTop); /*gets the previous contact by  using calling on pPrev of the contact at the given index*/
				/*inserts contact into the list at index*/
				pContactNew->pPrev = pCPrev;
				pContactNew->pNext = pCPrev->pNext;
				pCPrev->pNext = pContactNew;
				if (pContactNew->pNext) { /*if contact is not being placed at the end of the list*/
					pContactNew->pNext->pPrev = pContactNew;
				}
			}
		}
	}
}

void deleteContact(int index, pContact *pTop) { /*deleting contact at given index*/
	Contact * tempContact;
	if (index <= getCount(pTop) - 1) { /*makes sure the index contains a contact*/
		Contact * contactToRemove = getContact(index, pTop); /*gets the contact to remove*/
		if (contactToRemove == (*pTop)) { /*if the contact is at the top of the list*/
			if (contactToRemove->pNext) { /*if the contact is not the only one in the list*/
				tempContact = contactToRemove->pNext;
				(*pTop) = tempContact;
				tempContact->pPrev = NULL;
			} else {
				tempContact = NULL;
				(*pTop) = NULL;
			}
		} else {
			if (contactToRemove->pNext) { /*if the contact is not at the end of the list*/
				tempContact = contactToRemove->pNext;
				tempContact->pPrev = contactToRemove->pPrev;
				contactToRemove->pPrev->pNext = tempContact;
			} else {
				tempContact = contactToRemove->pPrev;
				tempContact->pNext = NULL;
			}
		}
		free(contactToRemove); /*frees contact from memory*/
	}
}

void getField(int index, char *field, pContact *pTop) { /*gets given field of contact*/

	Contact * pContact = getContact(index, pTop); /*gets the contact*/
	char value[255];
	/*returns the field that was requested*/
	if (strcmp(field, "firstName") == 0) {
		strcpy(value, pContact->firstName);
	} else if (strcmp(field, "lastName") == 0) {
		strcpy(value, pContact->lastName);
	} else if (strcmp(field, "email") == 0) {
		strcpy(value, pContact->email);
	} else if (strcmp(field, "phoneNumber") == 0) {
		strcpy(value, pContact->phoneNumber);
	} else
		strcpy(value, "Field not valid.");

	printf("%s\n", value);

}

void loadFile(char *file, pContact *pTop) /*loads file into list*/
{
	FILE *pInFile;
	int index = getCount(pTop);
	char buffer[BUFSIZ];
	pInFile = fopen(file, "r"); /*opens file to read*/
	while (!feof(pInFile)) { /*while not at the end of the file*/
		fgets(buffer, BUFSIZ, pInFile); /*gets the contact info at each line*/
		buffer[strlen(buffer) - 1] = 0;
		if (strcmp(buffer, "lastName,firstName,email,phoneNumber") != 0) {
			addContact(buffer, index, pTop); /*creates and adds the contact to the list*/
			index++;
		}
	}
	fclose(pInFile); /*closes the file*/
}

void saveFile(char *file, pContact *pTop) {
	int size = getCount(pTop);
	FILE *pOutFile;
	pOutFile = fopen(file, "w"); /*opens the file to write*/
	fprintf(pOutFile, "lastName,firstName,email,phoneNumber\n");
	for (int i = 0; i < size; i++) {
		char *contactString = getContactAsString(i, pTop);/*gets the contact as a string at every index of list*/
		fprintf(pOutFile, "%s\n", contactString); /*prints the contact info into the file*/
	}
	fclose(pOutFile); /*closes file*/

}

void quitProgram() {
	printf("Complete\n"); /*prints out complete to end the program*/
}

void editContact(int index, char *field, char* value, pContact * pTop) {
	Contact * pContact = getContact(index, pTop); /*gets the contact at the given index*/
	if (strcmp(field, "firstName") == 0) { /*if the field to change is the first name*/
		strcpy(pContact->firstName, value); /*sets field to the new given value*/
	} else if (strcmp(field, "lastName") == 0) { /*if the field to change is the last name*/
		strcpy(pContact->lastName, value);
	} else if (strcmp(field, "email") == 0) { /*if the field to change is the email*/
		strcpy(pContact->email, value);
	} else if (strcmp(field, "phoneNumber") == 0) {/*if the field to change is the phone number*/
		strcpy(pContact->phoneNumber, value);
	}
}

void sortContacts(pContact *pTop) /*sorts the contacts in ascending order*/{
	Contact *cursor;
	int size = getCount(pTop);
	char *cursorString;
	char *comp;
	int count;
	int compare;

	for (int i = 1; i < size; i++) /*goes through all of the contacts in the list*/
	{
		count = 0;
		cursor = getContact(i, pTop); /*gets contact at given  index*/
		cursorString = getContactAsString(i, pTop);
		comp = getContactAsString(count, pTop);
		compare = strcmp(cursorString, comp);
		while (count < i) {
			/*goes through the sorted portion of the list until it reaches a contact that is greater than it*/
			if (compare < 0) {
				move(cursor, count, pTop);
				//test(cursor, i, count, pTop);
				count = i;
			} else {
				count++;
				comp = getContactAsString(count, pTop);
				compare = strcmp(cursorString, comp);
			}
		}
	}
}

void move(Contact * contact, int newIndex, pContact *pTop) /*moves the contact to the new index*/{

	Contact * oNext;
	Contact * oPrev = contact->pPrev;
	if (contact->pNext)
		oNext = contact->pNext;
	else
		oNext = NULL;

	if (newIndex == 0) /*if moving to the beginning of the list*/
	{
		contact->pPrev = NULL;
		contact->pNext = (*pTop);
		(*pTop)->pPrev = contact;
		(*pTop) = contact;
	} else {
		Contact * nPrev = getContact(newIndex - 1, pTop); /*gets the new previous contact and sets the contact after it*/
		contact->pPrev = nPrev;
		contact->pNext = nPrev->pNext;
		nPrev->pNext = contact;
		if (contact->pNext) /*if not at the end of the list*/
		{
			contact->pNext->pPrev = contact; /*connects contact to the next in the list*/
		}
	}
	if (oNext) {
		oPrev->pNext = oNext;
		oNext->pPrev = oPrev;
	} else {
		oPrev->pNext = NULL;
	}
}

void printAllContacts(pContact * pTop) {
	int size = getCount(pTop); /*gets the number of contacts*/
	printf("\n----------------------------------------------------------------\n");
	printf("   Contacts:\n");
	printf("----------------------------------------------------------------\n");
	for (int i = 0; i < size; i++) { /*loops through all of the contacts and prints them out*/
		printf("\t%d. %s\n", i+1, getContactAsString(i, pTop)); 
	}
	printf("----------------------------------------------------------------\n");
}

void printCommands() { /*returns out the available commands for the address book*/
	printf("\n----------------------------------------------------------------\n");
	printf("   Commands:\n");
	printf("----------------------------------------------------------------\n");
	printf("\tc - Get Commands\n");
	printf("\ta - Add Contact\n");
	printf("\td - Delete Contact\n");
	printf("\tg - Get Contact\n");
	printf("\t* - Get All Contacts\n");
	printf("\tf - Get Contact Field\n");
	printf("\tn - Get Number of Contacts\n");
	printf("\tl - Load File of Contacts\n");
	printf("\ts - Save Contacts to File\n");
	printf("\te - Edit Contact\n");
	printf("\to - Sort Contacts\n");
	printf("\tq - Quit Program\n");
	printf("----------------------------------------------------------------\n");
}

void printTitle() {
	printf("\n================================================================\n");
	printf("\n\t Address Book\n\n");
	printf("================================================================\n\n");
}
