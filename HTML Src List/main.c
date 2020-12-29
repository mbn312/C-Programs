#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defines the functions that are going to be used
void count(char *file);
void urls(char *file);
void tags(char *file);
void frequencies(char *file);
void printCommands();
void printTitle();

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp;
	char buffer[BUFSIZ];
	char url[BUFSIZ] = "curl -s ";
	char file[2 * BUFSIZ];
	char command[BUFSIZ];
	printTitle();
	printf("\nEnter URL:");
	fgets(buffer, BUFSIZ, stdin);
	rewind(stdin);
	strcat(url, buffer);
	fp = popen(url, "r");
	//while it isnt the end of the file, it will get the next input from fp and concat it to file
	while (!feof(fp)) {
		fgets(buffer, BUFSIZ, fp);
		strcat(file, buffer);
	}
	pclose(fp);
	//will loop until the user inputs 'q' into the standard input
	do {
		char *ptr = file;
		printf("Enter Command ( * - print command list):\n");
		fgets(command, BUFSIZ, stdin);
		rewind(stdin);
		//the user input will trigger a corresponding function
		switch (command[0]) {
		case 'c':
		case 'C':
			count(ptr);
			break;
		case 't':
		case 'T':
			tags(ptr);
			break;
		case 'u':
		case 'U':
			urls(ptr);
			break;
		case 'f':
		case 'F':
			frequencies(ptr);
			break;
		case 'q':
		case 'Q':
			printf("Complete\n");
			break;
		case '*':
			printCommands();
			break;
		default:
			break;
		}
	} while (command[0] != 'q');
	return EXIT_SUCCESS;
}

void printTitle() {
	printf("\n================================================================\n");
	printf("\n\t HTML Src List\n\n");
	printf("================================================================\n\n");
}

void printCommands() {
	printf("\n----------------------------------------------------------------\n");
	printf("   Commands:\n");
	printf("----------------------------------------------------------------\n");
	printf("\t* - Get Commands\n");
	printf("\tc - Get Count\n");
	printf("\tt - Get Tags\n");
	printf("\tu - Get URLs\n");
	printf("\t* - Get All Contacts\n");
	printf("\tf - Get Frequencies\n");
	printf("\tq - Quit\n");
	printf("----------------------------------------------------------------\n");
}

//count function goes through and looks for src=" and if it is valid, it will increase count by one.
void count(char *file) {
	int count = 0;
	char search[BUFSIZ] = "src=\"";
	size_t nlen = strlen(search);

	while (file != NULL) {
		file = strstr(file, search);
		if (file != NULL) {
			file -= 1;
			//isspace() checks to see if it is white space
			if (isspace(file[0]))
				count++;
			//gets rid of the src=\ at the beginning to find the next instance
			file += nlen + 1;
		}
	}
	printf("%d\n", count);
}

//goes through and finds all the valid src attributes and gets the url directly afterwards by iterating forward in the character array
void urls(char *file) {
	char search[BUFSIZ] = "src=\"";
	size_t nlen = strlen(search);

	while (file != NULL) {
		file = strstr(file, search);
		if (file != NULL) {
			file -= 1;
			if (isspace(file[0])) {
				int i = 6;
				do {
					printf("%c", file[i]);
					i++;
				} while (file[i] != '\"');
				printf("\n");
			}
			file += nlen + 1;
		}
	}
}
//finds a valid src attribute and when it finds it, it goes backwards until it finds < and prints out the word directly after it
void tags(char *file) {
	char search[BUFSIZ] = "src=\"";
	size_t nlen = strlen(search);

	while (file != NULL) {
		file = strstr(file, search);
		if (file != NULL) {
			int count = 1;
			file -= 1;
			if (isspace(file[0])) {
				do {
					file -= 1;
					count++;
				} while (file[0] != '<');
				int i = 1;
				do {
					printf("%c", file[i]);
					i++;
				} while (!isspace(file[i]));
				printf("\n");
			}
			file += nlen + count;
		}
	}
}

//goes through the tags and groups them together
void frequencies(char *file) {
	char search[BUFSIZ] = "src=\"";
	int cImg = 0;
	int cScript = 0;
	int cIframe = 0;
	size_t nlen = strlen(search);

	while (file != NULL) {
		file = strstr(file, search);
		if (file != NULL) {
			int count = 1;
			file -= 1;
			if (isspace(file[0])) {
				do {
					file -= 1;
					count++;
				} while (file[0] != '<');
				if (file[1] == 'i') {
					if (file[2] == 'm') {
						cImg++;
					} else {
						cIframe++;
					}
				} else {
					cScript++;
				}
			}
			file += nlen + count;
		}
	}

	printf("script\t%d\n", cScript);
	printf("iframe\t%d\n", cIframe);
	printf("img\t%d\n", cImg);
}

