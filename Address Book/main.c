#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "addressbook.h"
#include "addressbook.c"

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	Contact *pTop = NULL;
	char command[BUFSIZ];
	char buffer[256 * 4];
	char field[255];
	int index;
	printTitle();

	do {
		printf("\n\nEnter Command (c - list of commands):\n"); /*prints Enter Command to stdout*/
		fgets(command, BUFSIZ, stdin); /*gets the command from stdin*/
		rewind(stdin);

		switch (command[0]) /*carries out the given command*/{
		case 'a':
		case 'A':
			printf("\n-= Add Contact =-\n\n");
			printf("Enter index to place new contact:\n");
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			rewind(stdin);
			printf("Enter in contact with format 'lastName,firstName,email,phoneNumber':\n");
			scanf("%s", buffer);
			rewind(stdin);
			addContact(buffer, index, &pTop);
			printf("\nContact Added.\n");
			break;
		case 'd':
		case 'D':
			printf("\n-= Delete Contact =-\n\n");
			printf("Enter contact index:\n");
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			rewind(stdin);
			deleteContact(index, &pTop);
			printf("\nContact Deleted.\n\n");
			break;
		case 'g':
		case 'G':
			printf("\n-= Get Contact =-\n\n");
			printf("Enter contact index:\n");
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			rewind(stdin);
			if (index >= getCount(&pTop))
				printf("No contact at given index\n");
			else
				printf("%s\n", getContactAsString(index, &pTop));
			break;
		case 'f':
		case 'F':
			printf("\n-= Get Contact Field =-\n\n");
			printf("Enter contact index:\n");
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			rewind(stdin);
			printf("Enter contact field (firstName,lastName,email,phoneNumber):\n");
			scanf("%s", buffer);
			rewind(stdin);
			if (index >= getCount(&pTop))
				printf("\nNo contact at given index\n");
			else
				getField(index, buffer, &pTop);
			break;
		case 'n':
		case 'N':
			printf("\n-= Number of Contacts =-\n\n");
			printf("%d Contacts\n", getCount(&pTop));
			break;
		case 'l':
		case 'L':
			printf("\n-= Load File =-\n\n");
			printf("Enter File Name:\n");
			scanf("%s", buffer);
			rewind(stdin);
			loadFile(buffer, &pTop);
			printf("\nContacts Loaded.\n");
			break;
		case 's':
		case 'S':
			printf("\n-= Save Contacts =-\n\n");
			printf("Enter File Name:\n");
			scanf("%s", buffer);
			saveFile(buffer, &pTop);
			printf("\nContacts saved to file.\n");
			break;
		case 'q':
		case 'Q':
			printf("-= Quitting Program =-\n");
			quitProgram();
			break;
		case 'e':
		case 'E':
			printf("\n-= Edit Contact =-\n\n");
			printf("Enter contact index:\n");
			index = atoi(fgets(buffer, BUFSIZ, stdin));
			rewind(stdin);
			printf("Enter contact field (firstName,lastName,email,phoneNumber):\n");
			scanf("%s", field);
			rewind(stdin);
			printf("Enter new information:\n");
			scanf("%s", buffer);
			rewind(stdin);
			editContact(index, field, buffer, &pTop);
			printf("\nContact Editted.\n");
			break;
		case 'o':
		case 'O':
			sortContacts(&pTop);
			printf("-= Contacts Sorted =-\n");
			break;
		case '*':
			printAllContacts(&pTop);
			break;
		case 'c':
		case 'C':
			printCommands();
			break;
		default:
		    break;
		}

	} while (command[0] != 'q' && command[0] != 'Q'); /*keeps going until the quit command has been received*/
	return EXIT_SUCCESS;
}
