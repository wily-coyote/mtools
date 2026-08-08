#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "fnt.h"

int main(int argc, char **argv){
	char *pcxPath = NULL;
	char *txtPath = NULL;
	char *fntPath = NULL;
	FILE *pcxHandle = NULL;
	FILE *txtHandle = NULL;
	FILE *fntHandle = NULL;
	char *pcxData = NULL;
	char *txtData = NULL;
	Header header;

	if(argc > 3){
		pcxPath = argv[1];
		txtPath = argv[2];
		fntPath = argv[3];
	}

	pcxPath = pathorprompt(pcxPath, "Enter path to PCX: ");
	txtPath = pathorprompt(txtPath, "Enter path to TXT: ");
	fntPath = pathorprompt(fntPath, "Enter path to FNT: ");

	// open files
	pcxHandle = fopen(pcxPath, "rb");
	txtHandle = fopen(txtPath, "rb");
	fntHandle = fopen(fntPath, "wb");

	// check files
	if(pcxHandle == NULL) {
		printf("Couldn't open PCX %s for reading\n", pcxPath);
		return -1;
	}

	if(txtHandle == NULL) {
		printf("Couldn't open TXT %s for reading\n", txtPath);
		return -1;
	}

	if(fntHandle == NULL) {
		printf("Couldn't open FNT %s for writing\n", fntPath);
		return -1;
	}

	memcpy(header.signature, SIGNATURE, 12);

	fseek(pcxHandle, 0, SEEK_END);
	fseek(txtHandle, 0, SEEK_END);

	header.nHiVer = 0x0100;
	header.nLoVer = 0x0000;

	header.cbPcx = ftell(pcxHandle);
	header.cbTxt = ftell(txtHandle);

	header.oPcx = sizeof(Header);
	header.oTxt = sizeof(Header)+header.cbPcx;

	memset(header.comment, 0, 32);
	//strcpy(header.comment, "pcx2fnt");

	rewind(pcxHandle);
	rewind(txtHandle);

	fwrite(&header, sizeof(Header), 1, fntHandle);
	
	pcxData = (char*)malloc(header.cbPcx);
	txtData = (char*)malloc(header.cbTxt);

	fread(pcxData, header.cbPcx, 1, pcxHandle);
	fread(txtData, header.cbTxt, 1, txtHandle);

	fwrite(pcxData, header.cbPcx, 1, fntHandle);
	fwrite(txtData, header.cbTxt, 1, fntHandle);

	printf("Wrote %s\n", fntPath);

	fclose(fntHandle);
	fclose(pcxHandle);
	fclose(txtHandle);
	free(pcxPath);
	free(txtPath);
	free(fntPath);
	return 0;
}
