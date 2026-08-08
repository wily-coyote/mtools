#ifndef __FNT_H__
#define __FNT_H__
#include <stdint.h>
const char SIGNATURE[12] = "ElecbyteFnt";

struct Header {
	char signature[12];
	uint16_t nHiVer;
	uint16_t nLoVer;
	uint32_t oPcx;
	uint32_t cbPcx;
	uint32_t oTxt;
	uint32_t cbTxt;
	char comment[32];
};

typedef struct Header Header;
#endif
