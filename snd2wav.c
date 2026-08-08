#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "snd.h"

int main(int argc, char** argv){
	char filename[260];
	char *sndPath = NULL;
	FILE *sndHandle = NULL;
	Header header;
	SubfileHeader curSubfile;
	uint8_t* wavData;
	FILE *wavFile = NULL;
	uint32_t i = 0;

	if(argc > 1)
		sndPath = argv[1];
	sndPath = pathorprompt(sndPath, "Enter path to SND: ");

	sndHandle = fopen(sndPath, "rb");
	if(sndHandle == NULL) {
		printf("Couldn't read %s\n", sndPath);
		return -1;
	}

	fread(&header, sizeof(Header), 1, sndHandle);
	if(strcmp(header.signature, SND_SIGNATURE) != 0){
		printf("Not an SND file\n");
		return -1;
	}

	fseek(sndHandle, header.oFirst, 0);
	for(i = 0; i < header.cSounds; i++){
		fread(&curSubfile, sizeof(SubfileHeader), 1, sndHandle);

		memset(filename, 0, sizeof(filename));
		snprintf(filename, sizeof(filename), "%u-%u.wav", curSubfile.nGroup, curSubfile.nIndex);

		wavFile = fopen(filename, "wb");
		if(wavFile == NULL){
			printf("Couldn't write to %s\n", filename);
			goto next;
		}

		wavData = (uint8_t*)calloc(curSubfile.cbSubfile, sizeof(uint8_t));
		fread(wavData, curSubfile.cbSubfile, 1, sndHandle);
		fwrite(wavData, curSubfile.cbSubfile, 1, wavFile);
		fclose(wavFile);
		free(wavData);

		printf("Wrote %s\n", filename);

next:
		fseek(sndHandle, curSubfile.oNext, 0);
	}

	fclose(sndHandle);
	return 0;
}
