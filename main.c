#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("invalid args\n");
		return 1;
	}
	FILE *file = NULL;
	if(!(file = fopen(argv[1], "r"))) {
		printf("invalid file\n");
		return 1;
	}
	char *new_name = malloc(strlen(argv[1]) + 5);
	new_name = strcpy(new_name, argv[1]);
	new_name = strcat(new_name, ".tmp");
	FILE *temp = fopen(new_name, "w");
	int scope = 0;
	while(1) {
		int val = fgetc(file);
		if(val == EOF) {
			break;
		}
		if(val == '{') {
			scope++;
		}
		else if(val == '}') {
			scope--;
			if(scope < 0) {
				printf("bro you have an extra '}'\n");
				break;
			}
		}
		fputc(val, temp);
		if(val != ';' || scope == 0) {
			continue;
		}
		if(fgetc(file) != '\n') {
			continue;
		}
		ungetc('\n', file);
		fprintf(temp, "          printf(\"%%d\", __LINE__);perror(NULL);");
	}
	remove(argv[1]);
	rename(new_name, argv[1]);
	return 0;
}
