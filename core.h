#ifndef CORE
#define CORE

#include <stdint.h>

#define REG_A core->a
#define REG_B core->b
#define REG_C core->c
#define REG_D core->d
#define REG_E core->e
#define REG_H core->h
#define REG_L core->l
#define PSW (0x02 | (core->cc.s << 7) \
		| (core->cc.z << 6 ) \
		| (core->cc.a << 4 ) \
		| (core->cc.p << 2 ) \
		| (core->cc.c))
#define PC core->pc
#define SP core->sp
#define MEM core->mem

#define FLAG_C core->cc.c
#define FLAG_Z core->cc.z
#define FLAG_S core->cc.s
#define FLAG_A core->cc.a
#define FLAG_P core->cc.p

 typedef struct condition {
	uint8_t z:1; /* zero flag */
	uint8_t s:1; /* sign bit */
	uint8_t p:1; /* parity */
	uint8_t c:1; /* carry */
	uint8_t a:1; /* auxilary carry */
} condition;

typedef struct i8080 {
	uint8_t halt;

	uint8_t b;
	uint8_t c;

	uint8_t d;
	uint8_t e;

	uint8_t h;
	uint8_t l;

	uint8_t a;
	condition cc;

	uint16_t pc;
	uint16_t sp;
	uint8_t *mem;

	uint8_t ie; /* interrupt enable */
} i8080;

void init_core(i8080* core, uint8_t* mem);
void dump_core(i8080* core);
int step_core(i8080* core);
int run_core(i8080* core, int cycles);
/*
/CASE$/ read !./opdecode.sh
*/

//CASE

#endif
