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

#define RP_BC ((core->b << 8) | core->c)
#define RP_DE ((core->d << 8) | core->e)
#define RP_HL ((core->h << 8) | core->l)
#define RP_FA ((core->psw << 8) | core->a)

#define PC core->pc
#define SP core->sp

#define MEM core->mem

#define FLAG_C core->cc.c
#define FLAG_Z core->cc.z
#define FLAG_S core->cc.s
#define FLAG_A core->cc.a
#define FLAG_P core->cc.p

#define REG(x) ((uint8_t*)core + (x))
#define RP(x) ((uint16_t*)core + (x))

typedef struct condition {
	uint8_t z:1; /* zero flag */
	uint8_t s:1; /* sign bit */
	uint8_t p:1; /* parity */
	uint8_t c:1; /* carry */
	uint8_t a:1; /* auxilary carry */
} condition;

typedef struct i8080 {

	uint8_t b;
	uint8_t c;

	uint8_t d;
	uint8_t e;

	uint8_t h;
	uint8_t l;

	uint8_t psw;
	uint8_t a;

	condition cc;

	uint16_t pc;
	uint16_t sp;
	uint8_t *mem;

	uint8_t halt;
	uint8_t ie; /* interrupt enable */
} i8080;

void init_core(i8080* core, uint8_t* mem);
void dump_core(i8080* core);
int step_core(i8080* core);
int run_core(i8080* core, int cycles, int fend);
uint8_t parity(uint16_t x);

int INC(i8080*core, int blit);
int INX(i8080*core, int blit);
int MVI(i8080*core);
int ADD(i8080*core, uint8_t blit);
int SUB(i8080*core, uint8_t blit);
int ANA(i8080*core);
int XRA(i8080*core);
int ORA(i8080*core);
int CMP(i8080*core);
int MOV(i8080*core);
int PUSH(i8080*core);
int POP(i8080*core);
int DAD(i8080*core);
int LXI(i8080*core, uint8_t low, uint8_t hi);
int JMP(i8080*core, uint8_t cond);
int CALL(i8080*core, uint8_t cond);
int RET(i8080*core, uint8_t cond);

/*
/CASE$/ read !./opdecode.sh
*/

//CASE

#endif
