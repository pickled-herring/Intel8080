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
	int rom_p = 0;
	int steps = atoi(argv[1]);

	init_core(core,mem);

	for(int i=2; i<argc; i++){

		FILE *f = fopen(argv[i], "rb");

		if(f==NULL){
			printf("unable to read %s\n", argv[i]);
			return 1;
		}

		fseek(f, 0L, SEEK_END);
		int fsize = ftell(f);
		fseek(f, 0L, SEEK_SET);

		if(fread(mem+rom_p,1,fsize,f) != fsize)
			return 2;
		rom_p += fsize;

		fclose(f);

	}

	run_core(core, steps);
	dump_core(core);
	free(mem);

	return 0;
}
