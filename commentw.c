#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "snd.h"
#include "sff.h"

// trimmed fgets
void fgets_t(char *szOutput, size_t cbData){
	char *szCurrent = szOutput;
	int c;
	for(;;){
		c = fgetc(stdin);
		if(c == EOF || c == 0x04){ break; } // EOF or EOT
		if(szCurrent >= szOutput+cbData){
			printf("Comment trimmed\n");
			break;
		}
		(*szCurrent) = (char)c;
		szCurrent++;
	}
	// trim the newline
	if((szCurrent < szOutput+cbData) && (*(szCurrent-1)) == 0xA){
		(*(szCurrent-1)) = 0;
	}
}

int main(int argc, char **argv){
	char error[BUFSIZ];
	char signature[12];
	char *path;
	FILE *file;
	char *comment;
	int offset;
	int size;

	path = NULL;
	file = NULL;

	if(argc > 1) path = argv[1];
	fopen_s(&file, path, "rb+");
	if(file == NULL){
		strerror_s(error, sizeof(error), errno);
		printf("%s\n", error);
		return errno;
	}
	fread(signature, sizeof(signature), 1, file);

	if(strcmp(signature, SFF_SIGNATURE) == 0){
		printf("SFF file\n");
		size = 436;
		offset = 0x4c;
	} else if (strcmp(signature, SND_SIGNATURE) == 0) {
		printf("SND file\n");
		size = 488;
		offset = 0x18;
	} else {
		printf("I don't what to do with this file\n");
		return -1;
	}

	comment = (char*)malloc(size);
	memset(comment, 0, size);
	fseek(file, offset, SEEK_SET);

	printf("Type in your comment. Hit Ctrl+D to end your comment.\n");
	fgets_t(comment, size);
	
	fwrite(comment, size, 1, file);
	free(comment);
	return 0;
}
