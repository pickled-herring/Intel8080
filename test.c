#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "core.h"


int
main (int argc, char** argv)
{
	i8080* core = (i8080* )malloc(sizeof(i8080));

	/* 16 kb of RAM */
	uint8_t *mem = malloc(0xFFFF);
	int rom_p = 0x100, fsize=0;
	int steps = atoi(argv[1]);

	init_core(core,mem);

	for(int i=2; i<argc; i++){

		FILE *f = fopen(argv[i], "rb");

		if(f==NULL){
			printf("unable to read %s\n", argv[i]);
			return 145;
		}

		fseek(f, 0L, SEEK_END);
		fsize += ftell(f);
		fseek(f, 0L, SEEK_SET);

		if(fread(mem+rom_p,1,fsize,f) != fsize)
			return 2;
		rom_p += fsize;

		fclose(f);

	}

	// jump to 0x100
	PC= 0x100;
	//sp = 0x7ad
	MEM[368] = 0x7;
	//skip DAA test
	MEM[0x59c] = 0xc3;
	MEM[0x59d] = 0xc2;
	MEM[0x59e] = 0x05;
	run_core(core, steps, rom_p + fsize);
	dump_core(core);
	free(mem); 
	return 0;
}
