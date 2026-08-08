#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

char* pathorprompt(char* path, const char* prompt){
	char *result;
	size_t length;

	result = NULL;
	if(path != NULL){
		// portable strdup
		length = strlen(path) + 1;
		result = malloc(length);
		memcpy(result, path, length);
	} else {
		printf("%s", prompt);
		result = malloc(260);
		if(fgets(result, sizeof result, stdin) != NULL){
			if(result[strlen(result)-1] == '\n'){
				result[strlen(result)-1] = '\0';
			}
		}
	}

	return result;
}

char *basename(const char* path){
	char *basename, *extPos;

	basename = (char*)calloc(strlen(path)+1, sizeof(char));
	memcpy(basename, path, strlen(path)+1);
	extPos = strrchr(basename, '.');
	*extPos = '\0';

	return basename;
}
