#ifndef __SND_H__
#define __SND_H__
#include <stdint.h>
const char SND_SIGNATURE[12] = "ElecbyteSnd";

struct Header {
	char signature[12];
	uint16_t nHiVer;
	uint16_t nLoVer;
	uint32_t cSounds;
	uint32_t oFirst;
	char comment[488];
};

struct SubfileHeader {
	uint32_t oNext;
	uint32_t cbSubfile;
	uint32_t nGroup;
	uint32_t nIndex;
};

typedef struct Header Header;
typedef struct SubfileHeader SubfileHeader;
#endif
