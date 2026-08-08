#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "fnt.h"

int main(int argc, char* *argv){
	char *fntPath = NULL;
	char *prefix = NULL;
	char pcxPath[260];
	char txtPath[260];
	FILE *pcxHandle = NULL;
	FILE *txtHandle = NULL;
	FILE *fntHandle = NULL;
	char *pcxData = NULL;
	char *txtData = NULL;
	Header header;

	if(argc > 1)
		fntPath = argv[1];

	fntPath = pathorprompt(fntPath, "Enter path to FNT: ");

	// get filename without extension
	prefix = basename(fntPath);
	snprintf(pcxPath, sizeof(pcxPath), "%s.pcx", prefix);
	snprintf(txtPath, sizeof(txtPath), "%s.txt", prefix);

	// open files
	fntHandle = fopen(fntPath, "rb");
	pcxHandle = fopen(pcxPath, "wb");
	txtHandle = fopen(txtPath, "wb");

	// check file handles
	if(fntHandle == NULL) {
		printf("Couldn't open %s for reading\n", fntPath);
		return -1;
	}

	if(pcxHandle == NULL){
		printf("Couldn't open %s for writing\n", pcxPath);
		return -1;
	}

	if(txtHandle == NULL){
		printf("Couldn't open %s for writing\n", txtPath);
		return -1;
	}

	// validate signature
	fread(&header, sizeof(Header), 1, fntHandle);
	if(strcmp(header.signature, SIGNATURE) != 0){
		printf("Not an FNT file\n");
		return -1;
	}

	pcxData = (char*)calloc(header.cbPcx, sizeof(char));
	txtData = (char*)calloc(header.cbTxt, sizeof(char));

	fseek(fntHandle, header.oPcx, 0);
	fread(pcxData, header.cbPcx, 1, fntHandle);

	fseek(fntHandle, header.oTxt, 0);	
	fread(txtData, header.cbTxt, 1, fntHandle);

	fwrite(pcxData, header.cbPcx, 1, pcxHandle);
	printf("Wrote %s\n", pcxPath);

	fwrite(txtData, header.cbTxt, 1, txtHandle);
	printf("Wrote %s\n", txtPath);

	free(pcxData);
	free(txtData);
	free(prefix);
	free(fntPath);
	fclose(fntHandle);
	fclose(pcxHandle);
	fclose(txtHandle);
	return 0;
}
