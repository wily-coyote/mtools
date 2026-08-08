CFLAGS := -Wall -Wextra -Wpedantic -std=c99
all: pcx2fnt fnt2pcx snd2wav commentr commentw
pcx2fnt: pcx2fnt.o common.o
fnt2pcx: fnt2pcx.o common.o
snd2wav: snd2wav.o common.o
commentr: commentr.o
commentw: commentw.o
