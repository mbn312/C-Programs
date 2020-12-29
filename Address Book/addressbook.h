#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct contact Contact;
typedef struct contact* pContact;
struct contact {
	char firstName[255];
	char lastName[255];
	char email[255];
	char phoneNumber[255];
	Contact *pPrev;
	Contact *pNext;
};

void move(Contact * contact, int newIndex, pContact *pTop);

Contact *getContact(int index, pContact *pTop);

char *getContactAsString(int index, pContact *pTop);

Contact *createContact(char *contactInfo);

void addContact(char * contactInfo, int index, pContact * pTop);

void deleteContact(int index, pContact * pTop);

void getField(int index, char *field, pContact * pTop);

int getCount(pContact * pTop);

void loadFile(char *file, pContact *pTop);

void saveFile(char *file, pContact *pTop);

void quitProgram();

void editContact(int index, char *field, char *newValue, pContact * pTop);

void sortContacts(pContact *pTop);

void printCommands();

void printAllContacts(pContact * pTop);

void printTitle();

#endif /* ADDRESSBOOK_H_ */
