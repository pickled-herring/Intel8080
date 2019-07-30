#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "core.h"
/* define CPUDIAG for any programs running on CP/M */
#define CPUDIAG

void set_conditions(i8080*core, uint16_t res);
void logic_set_conditions(i8080*core, uint16_t res);

void
init_core (i8080* core, uint8_t *mem)
{
	memset(core, 0 , sizeof(i8080));
	SP = 0xF000; PC = 0x0000; MEM = mem;
}

void
dump_core (i8080*core)
{

#define DUMP(l,x) printf("%c:%02x  ",(l),(x));
	DUMP('A',REG_A);
	DUMP('F',PSW);
	printf("\n");
	DUMP('B',REG_B);
	DUMP('C',REG_C);
	printf("\n");
	DUMP('D',REG_D);
	DUMP('E',REG_E);
	printf("\n");
	DUMP('H',REG_H);
	DUMP('L',REG_L);

	printf("\n");
	printf("FLAGS: s%d z%d 0 a%d 0 p%d 1 c%d\n",
			FLAG_S, FLAG_Z, FLAG_A, FLAG_P, FLAG_C);

	printf("SP: %04x\n", SP);
	printf("PC: %04x\n\n", PC);

	printf("MEM:\n");
	for(int i = -10; i < 5; i++)
	printf("%04x: %02x\n", (SP + i), MEM[SP+i]);
}

int
run_core (i8080* core, int cycles, int fend)
{
	int done = 0, step = 0;
	while(step < cycles && !core->halt){
		//printf("\n%04d:", step);
		done += step_core(core);
		if( PC > fend ){
			printf("\n Bad memory location %04x\n", PC);
			exit(13);
		}
		step++;
	}
	printf("\n\ncycles:%d\n\n", done);
	return done;
}

uint8_t
parity(uint16_t x)
{
	uint8_t res = 1;
	for(int i=0; i<8; i++){
		if(x>>i & 1)
			res = !res;
	}
	return res;
}


int
step_core (i8080* core){
/*
/MAIN$/+,/END$/- >
/MAIN$/+,/END$/- s/print/\/\/print/g
/MAIN$/+,/END$/- s/\/\/print/print/g

*/

	int done = 1;
	//MAIN
	//printf("%04x:%02x:", PC, MEM[PC]);
	switch(MEM[PC]){
	/* STC */
	case 55:
		//printf("STC:");
		FLAG_C = 1;
		done = 4;
		break;
	/* CMC */
	case 63:
		//printf("CMC:");
		FLAG_C = !FLAG_C;
		done = 4;
		break;
	/* INC */
	case 60:
	case 52:
	case 44:
	case 36:
	case 28:
	case 20:
	case 12:
	case 4:
		//printf("INC:");
		done = INC(core, 1);
		break;
	/* DCR */
	case 61:
	case 53:
	case 45:
	case 37:
	case 29:
	case 21:
	case 13:
	case 5:
		//printf("DCR:");
		done = INC(core, -1);
		break;
	/* CMA */
	case 47:
		//printf("CMA:");
		REG_A = ~REG_A;
		done = 4;
		break;
	/* DAA */
	case 39:
		//printf("DAA: not implemented");
		done = 4;
		break;
	/* NOP */
	case 0:
		//printf("NOP:");
		done = 4;
		break;
	/* MOV */
	case 127:
	case 126:
	case 125:
	case 124:
	case 123:
	case 122:
	case 121:
	case 120:
	case 119:
	case 117:
	case 116:
	case 115:
	case 114:
	case 113:
	case 112:
	case 111:
	case 110:
	case 109:
	case 108:
	case 107:
	case 106:
	case 105:
	case 104:
	case 103:
	case 102:
	case 101:
	case 100:
	case 99:
	case 98:
	case 97:
	case 96:
	case 95:
	case 94:
	case 93:
	case 92:
	case 91:
	case 90:
	case 89:
	case 88:
	case 87:
	case 86:
	case 85:
	case 84:
	case 83:
	case 82:
	case 81:
	case 80:
	case 79:
	case 78:
	case 77:
	case 76:
	case 75:
	case 74:
	case 73:
	case 72:
	case 71:
	case 70:
	case 69:
	case 68:
	case 67:
	case 66:
	case 65:
	case 64:
		//printf("MOV:");
		done = MOV(core);
		break;
	/* STAX */
	case 18:
	case 2:
		//printf("STAX:");
		{
		uint8_t *dest;
		if((MEM[PC] >> 4) & 1)
			dest = MEM + RP_DE;
		else
			dest = MEM + RP_BC;
		*dest = REG_A;
		}
		done = 7;
		break;
	/* LDAX */
	case 26:
	case 10:
		//printf("LDAX:");
		{
		uint8_t *src;
		if((MEM[PC] >> 4) & 1)
			src = MEM + RP_DE;
		else
			src = MEM + RP_BC;
		REG_A = *src;
		}
		done = 7;
		break;
	/* ADD */
	case 135:
	case 134:
	case 133:
	case 132:
	case 131:
	case 130:
	case 129:
	case 128:
		//printf("ADD:");
		done = ADD(core, 0);
		break;
	/* ADC */
	case 143:
	case 142:
	case 141:
	case 140:
	case 139:
	case 138:
	case 137:
	case 136:
		//printf("ADC:");
		done = ADD(core, FLAG_C);
		break;
	/* SUB */
	case 151:
	case 150:
	case 149:
	case 148:
	case 147:
	case 146:
	case 145:
	case 144:
		//printf("SUB:");
		done = SUB(core, 0);
		break;
	/* SBB */
	case 159:
	case 158:
	case 157:
	case 156:
	case 155:
	case 154:
	case 153:
	case 152:
		//printf("SBB:");
		done = SUB(core, FLAG_C);
		break;
	/* ANA */
	case 167:
	case 166:
	case 165:
	case 164:
	case 163:
	case 162:
	case 161:
	case 160:
		//printf("ANA:");
		done = ANA(core);
		break;
	/* XRA */
	case 175:
	case 174:
	case 173:
	case 172:
	case 171:
	case 170:
	case 169:
	case 168:
		//printf("XRA:");
		done = XRA(core);
		break;
	/* ORA */
	case 183:
	case 182:
	case 181:
	case 180:
	case 179:
	case 178:
	case 177:
	case 176:
		//printf("ORA:");
		done = ORA(core);
		break;
	/* CMP */
	case 191:
	case 190:
	case 189:
	case 188:
	case 187:
	case 186:
	case 185:
	case 184:
		//printf("CMP:");
		done = CMP(core);
		break;
	/* RLC */
	case 7:
		//printf("RLC:");
		FLAG_C = REG_A >> 7;
		REG_A = (REG_A << 1) | FLAG_C;
		done =4;
		break;
	/* RRC */
	case 15:
		//printf("RRC:");
		FLAG_C = REG_A & 1;
		REG_A = (REG_A >> 1) | (FLAG_C << 7);
		done =4;
		break;
	/* RAL */
	case 23:
		//printf("RAL:");
		{
		uint8_t temp = FLAG_C;
		FLAG_C = REG_A >> 7;
		REG_A = (REG_A << 1) | temp;
		done =4;
		}
		break;
	/* RAR */
	case 31:
		//printf("RAR:");
		{
		uint8_t temp = FLAG_C;
		FLAG_C = REG_A & 1;
		REG_A = (REG_A >> 1) | (temp << 7);
		done =4;
		}
		break;
	/* PUSH */
	case 245:
	case 229:
	case 213:
	case 197:
		//printf("PUSH:");
		done = PUSH(core);
		break;
	/* POP */
	case 241:
	case 225:
	case 209:
	case 193:
		//printf("POP:");
		done = POP(core);
		break;
	/* DAD */
	case 57:
	case 41:
	case 25:
	case 9:
		//printf("DAD:");
		done = DAD(core);
		break;
	/* INX */
	case 51:
	case 35:
	case 19:
	case 3:
		//printf("INX:");
		done = INX(core, 1);
		break;
	/* DCX */
	case 59:
	case 43:
	case 27:
	case 11:
		//printf("DCX:");
		done = INX(core, -1);
		break;
	/* XCHG */
	case 235:
		//printf("XCHG:");
		{
		uint8_t temp = REG_D;
		REG_D = REG_H;
		REG_H = temp;
		temp = REG_E;
		REG_E = REG_L;
		REG_L = temp;
		}
		done = 4;
		break;
	/* XTHL */
	case 227:
		//printf("XTHL:");
		{
		uint8_t temp = MEM[SP];
		MEM[SP] = REG_L;
		REG_L = temp;
		temp = MEM[SP+1];
		MEM[SP+1] = REG_H;
		REG_H = temp;
		}
		done = 16;
		break;
	/* SPHL */
	case 249:
		//printf("SPHL:");
		SP = RP_HL;
		done = 16;
		break;
	/* LXI */
	case 49:
	case 33:
	case 17:
	case 1:
		//printf("LXI:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		done = LXI(core, MEM[PC+1], MEM[PC+2]);
		PC+=2;
		break;
	/* MVI */
	case 62:
	case 54:
	case 46:
	case 38:
	case 30:
	case 22:
	case 14:
	case 6:
		//printf("MVI:");
		//printf("%02x", MEM[PC+1]);
		done = MVI(core);
		PC++;
		break;
	/* ADI */
	case 198:
		//printf("ADI:");
		//printf("%02x", MEM[PC+1]);
		set_conditions(core,(uint16_t)(REG_A + MEM[PC+1]));
		REG_A += MEM[PC+1];
		PC++;
		done = 7;
		break;
	/* ACI */
	case 206:
		//printf("ACI:");
		//printf("%02x", MEM[PC+1]);
		{
		uint8_t temp = FLAG_C;
		set_conditions(core,(uint16_t)(REG_A + MEM[PC+1] + FLAG_C));
		REG_A += (MEM[PC+1] + temp);
		}
		PC++;
		done = 7;
		break;
	/* SUI */
	case 214:
		//printf("SUI:");
		//printf("%02x", MEM[PC+1]);
		set_conditions(core,(uint16_t)(REG_A - MEM[PC+1]));
		if(REG_A < MEM[PC+1])
			FLAG_C = 1;
		else
			FLAG_C = 0;
		REG_A -= MEM[PC+1];
		PC++;
		done = 7;
		break;
	/* SBI */
	case 222:
		//printf("SBI:");
		//printf("%02x", MEM[PC+1]);
		{
		uint8_t temp = FLAG_C;
		set_conditions(core,(uint16_t)(REG_A - MEM[PC+1] - FLAG_C));
		if(MEM[PC+1] > REG_A)
			FLAG_C = 1;
		else
			FLAG_C = 0;
		REG_A -= (MEM[PC+1]+temp);
		}
		PC++;
		done = 7;
		break;
	/* ANI */
	case 230:
		//printf("ANI:");
		//printf("%02x", MEM[PC+1]);
		logic_set_conditions(core,(uint16_t)(REG_A & MEM[PC+1]));
		REG_A &= MEM[PC+1];
		PC++;
		done = 7;
		break;
	/* XRI */
	case 238:
		//printf("XRI:");
		//printf("%02x", MEM[PC+1]);
		logic_set_conditions(core,(uint16_t)(REG_A ^ MEM[PC+1]));
		REG_A ^= MEM[PC+1];
		PC++;
		done = 7;
		break;
	/* ORI */
	case 246:
		//printf("ORI:");
		//printf("%02x", MEM[PC+1]);
		logic_set_conditions(core,(uint16_t)(REG_A | MEM[PC+1]));
		REG_A |= MEM[PC+1];
		PC++;
		done = 7;
		break;
	/* CPI */
	case 254:
		//printf("CPI:");
		//printf("%02x", MEM[PC+1]);
		set_conditions(core,(uint16_t)(REG_A - MEM[PC+1]));
		if(REG_A < MEM[PC+1])
			FLAG_C = 1;
		else
			FLAG_C = 0;
		PC++;
		done=7;
		break;
	/* STA */
	case 50:
		//printf("STA:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		MEM[(MEM[PC+2] << 8) | MEM[PC+1]] = REG_A;
		PC+=2;
		done = 13;
		break;
	/* LDA */
	case 58:
		//printf("LDA:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		REG_A = MEM[(MEM[PC+2] << 8) | MEM[PC+1]];
		PC+=2;
		done = 13;
		break;
	/* SHLD */
	case 34:
		//printf("SHLD:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		MEM[(MEM[PC+2] << 8) | MEM[PC+1]] = REG_L;
		MEM[((MEM[PC+2] << 8) | MEM[PC+1]) + 1] = REG_H;
		PC+=2;
		done = 16;
		break;
	/* LHLD */
	case 42:
		//printf("LHLD:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		REG_L = MEM[(MEM[PC+2] << 8) | MEM[PC+1]];
		REG_H = MEM[((MEM[PC+2] << 8) | MEM[PC+1]) + 1];
		PC+=2;
		break;
	/* PCHL */
	case 233:
		//printf("PCHL:");
		PC = RP_HL;
		return 5;
		break;
	/* JMP */
	case 195:
		//printf("JMP:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
#ifdef CPUDIAG
	if(!MEM[PC+2] && !MEM[PC+1]){
		core->halt = 1;
		return 10;
	}
#endif
		PC=((MEM[PC+2] << 8) | MEM[PC+1]);
		return 10;
	/* JNZ */
	case 194:
		//printf("JNZ:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, !FLAG_Z);
	/* JZ */
	case 202:
		//printf("JZ:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, FLAG_Z);
	/* JNC */
	case 210:
		//printf("JNC:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, !FLAG_C);
	/* JC */
	case 218:
		//printf("JC:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, FLAG_C);
	/* JPO */
	case 226:
		//printf("JPO:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, !FLAG_P);
	/* JPE */
	case 234:
		//printf("JPE:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, FLAG_P);
	/* JP */
	case 242:
		//printf("JP:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, !FLAG_S);
	/* JM */
	case 250:
		//printf("JM:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return JMP(core, FLAG_S);
	/* CNZ */
	case 196:
		//printf("CNZ:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, !FLAG_Z);
	/* CZ */
	case 204:
		//printf("CZ:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, FLAG_Z);
	/* CALL */
	case 205:
		//printf("CALL:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		/* Here's CALL MSG for cpudiag.bin*/
#ifdef CPUDIAG
	if(((MEM[PC+2] << 8 ) | MEM[PC+1]) == 5){
		if(REG_C == 9){
			char*str = (char*)(MEM+RP_DE+3);
			while(*str != '$')
				printf("%c",*str++);
			printf("\n");
			PC+=3;
			return 17;
		} else if (REG_C == 2) {
			printf("%c", *(char*)(MEM+RP_DE+3));
			PC+=3;
			return 17;
		}
	} else if(((MEM[PC+2] << 8 ) | MEM[PC+1]) == 0){
		exit(12);
	} else
#endif
	{
		SP--;
		MEM[SP--] = (uint8_t)((PC+3) >> 8);
		MEM[SP] = (uint8_t)((PC+3) & 0xff);
		PC=((MEM[PC+2] << 8) | MEM[PC+1]);
		return 17;;
	}
	/* CNC */
	case 212:
		//printf("CNC:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, !FLAG_C);
	/* CC */
	case 220:
		//printf("CC:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, FLAG_C);
	/* CPO */
	case 228:
		//printf("CPO:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, !FLAG_P);
	/* CPE */
	case 236:
		//printf("CPE:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, FLAG_P);
	/* CP */
	case 244:
		//printf("CP:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, !FLAG_S);
	/* CM */
	case 252:
		//printf("CM:");
		//printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		return CALL(core, FLAG_S);
	/* RNZ */
	case 192:
		//printf("RNZ:");
		return RET(core, !FLAG_Z);
	/* RZ */
	case 200:
		//printf("RZ:");
		return RET(core, FLAG_Z);
	/* RET */
	case 201:
		//printf("RET:");
		PC = MEM[SP];
		SP++;
		PC |= (MEM[SP] << 8);
		SP++;
		return 10;
	/* RNC */
	case 208:
		//printf("RNC:");
		return RET(core, !FLAG_C);
	/* RC */
	case 216:
		//printf("RC:");
		return RET(core, FLAG_C);
	/* RPO */
	case 224:
		//printf("RPO:");
		return RET(core, !FLAG_P);
	/* RPE */
	case 232:
		//printf("RPE:");
		return RET(core, FLAG_P);
	/* RP */
	case 240:
		//printf("RP:");
		return RET(core, !FLAG_S);
	/* RM */
	case 248:
		//printf("RM:");
		return RET(core, FLAG_S);
	/* EI */
	case 251:
		//printf("EI:");
		core->ie = 1;
		break;
	/* DI */
	case 243:
		//printf("DI:");
		core->ie = 0;
		break;
	/* IN */
	case 219:
		//printf("IN:");
		//printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* OUT */
	case 211:
		//printf("OUT:");
		//printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* HLT */
	case 118:
		//printf("HLT:");
		core->halt = 1;
		break;
	//END
	default:
		printf("crashed %04x: %02x",PC,MEM[PC]);
		dump_core(core);
	}
	PC++;
	return done;
}

void
update_conditions(i8080*core)
{
	FLAG_C = core->psw & 1;
	FLAG_P = (core->psw>>2) & 1;
	FLAG_A = (core->psw>>4) & 1;
	FLAG_Z = (core->psw>>6) & 1;
	FLAG_S = (core->psw>>7) & 1;
}

void
set_conditions(i8080*core, uint16_t res)
{
	FLAG_C = ((int16_t)res > 0xff);
	FLAG_S = (0x80 == (res & 0x80));
	FLAG_Z = ((res&0xff) == 0);
	FLAG_P = parity((uint8_t)res);
	return;
}

void
logic_set_conditions(i8080*core, uint16_t res)
{
	FLAG_C = ((int16_t)res > 0xff);
	FLAG_S = (0x80 == (res & 0x80));
	FLAG_Z = ((res&0xff) == 0);
	FLAG_P = parity((uint8_t)res);
	return;
}

int
INC (i8080*core, int blit)
{
	uint8_t reg = ((MEM[PC] >> 3) & 7);
	uint8_t *addr;
	int done=5;

	if(reg == 0b110){
		addr = MEM + RP_HL;
		done = 10;
	} else {
		addr = REG(reg);
	}

	uint16_t res = *addr + blit;
	*addr = res;
	set_conditions(core, res);
	return done;
}

int
MVI (i8080*core)
{
	uint8_t reg = ((MEM[PC] >> 3) & 7);
	uint8_t *addr;
	int done=7;

	if(reg == 0b110){
		addr = MEM + RP_HL;
		done = 10;
	} else {
		addr = REG(reg);
	}

	*addr = MEM[PC+1];
	return done;
}

int
MOV (i8080*core)
{
	uint8_t*src, *dest;
	int done=4;

	if ((MEM[PC] & 7)== 0b110){
		src = MEM+RP_HL;
		done += 3;
	} else
		src = REG(MEM[PC] & 7);

	if (((MEM[PC] >> 3) & 7) == 0b110){
		dest = MEM+RP_HL;
		done += 3;
	} else
		dest = REG((MEM[PC] >> 3) & 7);

	*dest = *src;
	return done;
}

int
ADD (i8080*core, uint8_t blit)
{
	uint8_t *src;
	int done = 4;
	if ((MEM[PC] & 7) == 0b110){
		src = MEM+RP_HL;
		done = 7;
	} else
		src = REG(MEM[PC] & 7);
	uint16_t res= REG_A + *src + blit;
	REG_A = res;
	set_conditions(core,res);
	return done;
}

int
SUB (i8080*core, uint8_t blit)
{
	uint8_t *src;
	int done = 4;
	if ((MEM[PC] & 7) == 0b110){
		src = MEM+RP_HL;
		done = 7;
	} else
		src = REG(MEM[PC] & 7);
	uint16_t res= REG_A - (*src + blit);
	REG_A = res;
	set_conditions(core,res);
	return done;
}

int
ANA (i8080*core)
{
	uint8_t *src;
	int done = 4;
	if ((MEM[PC] & 7) == 0b110){
		src = MEM+RP_HL;
		done = 7;
	} else
		src = REG(MEM[PC] & 7);
	uint16_t res= REG_A & *src;
	REG_A = res;
	logic_set_conditions(core,res);
	return done;
}

int
XRA (i8080*core)
{
	uint8_t *src;
	int done = 4;
	if ((MEM[PC] & 7) == 0b110){
		src = MEM+RP_HL;
		done = 7;
	} else
		src = REG(MEM[PC] & 7);
	uint16_t res= REG_A ^ *src;
	REG_A = res;
	logic_set_conditions(core,res);
	return done;
}

int
ORA (i8080*core)
{
	uint8_t *src;
	int done = 4;
	if ((MEM[PC] & 7) == 0b110){
		src = MEM+RP_HL;
		done = 7;
	} else
		src = REG(MEM[PC] & 7);
	uint16_t res= REG_A | *src;
	REG_A = res;
	logic_set_conditions(core,res);
	FLAG_A = 0;
	return done;
}

int
CMP (i8080*core)
{
	uint8_t *src;
	int done = 4;
	if ((MEM[PC] & 7) == 0b110){
		src = MEM+RP_HL;
		done = 7;
	} else
		src = REG(MEM[PC] & 7);
	uint16_t res= REG_A - *src;
	set_conditions(core,res);
	return done;
}

int
PUSH (i8080*core)
{
	switch((MEM[PC] >> 4) & 3){
	case 0b00:
		SP--;
		MEM[SP--] = REG_B;
		MEM[SP] = REG_C;
		break;
	case 0b10:
		SP--;
		MEM[SP--] = REG_H;
		MEM[SP] = REG_L;
		break;
	case 0b01:
		SP--;
		MEM[SP--] = REG_D;
		MEM[SP] = REG_E;
		break;
	case 0b11:
		SP--;
		MEM[SP--] = REG_A;
		MEM[SP] = PSW;
		break;
	};
	return 11;
}

int
POP (i8080*core)
{
	switch((MEM[PC] >> 4) & 3){
	case 0b00:
		REG_C = MEM[SP];
		SP++;
		REG_B = MEM[SP];
		SP++;
		break;
	case 0b10:
		REG_L = MEM[SP];
		SP++;
		REG_H = MEM[SP];
		SP++;
		break;
	case 0b01:
		REG_E = MEM[SP];
		SP++;
		REG_D = MEM[SP];
		SP++;
		break;
	case 0b11:
		core->psw = MEM[SP];
		SP++;
		REG_A = MEM[SP];
		SP++;
		update_conditions(core);
		break;
	};
	return 10;
}

int
DAD (i8080*core)
{
	uint32_t res;
	switch((MEM[PC] >> 4) & 3){
	case 0b00:
		res = RP_BC + RP_HL;
		break;
	case 0b01:
		res = RP_DE + RP_HL;
		break;
	case 0b10:
		res = RP_HL*2;
		break;
	case 0b11:
		res = SP + RP_HL;
		break;
	}
	if(res > 0xff);
		FLAG_C = 1;
	REG_L = res & 0xff;
	REG_H = (res >> 8) & 0xff;
	return 10;
}

int
INX (i8080*core, int blit)
{
	uint16_t res;
	switch((MEM[PC] >> 4) & 3){
	case 0b00:
		res = RP_BC + blit;
		REG_C = res & 0xff;
		REG_B = (res >> 8) & 0xff;
		break;
	case 0b01:
		res = RP_DE + blit;
		REG_E = res & 0xff;
		REG_D = (res >> 8) & 0xff;
		break;
	case 0b10:
		res = RP_HL + blit;
		REG_L = res & 0xff;
		REG_H = (res >> 8) & 0xff;
		break;
	case 0b11:
		SP += blit;
		break;
	}
	return 10;
}

int
LXI (i8080*core, uint8_t low, uint8_t hi)
{
	switch((MEM[PC] >> 4)& 3){
	case 0b00:
		REG_B = hi;
		REG_C = low;
		break;
	case 0b01:
		REG_D = hi;
		REG_E = low;
		break;
	case 0b10:
		REG_H = hi;
		REG_L = low;
		break;
	case 0b11:
		SP = (hi << 8) | low;
		break;
	}
	return 10;
}

int
JMP (i8080*core, uint8_t cond)
{
	if(cond){
		PC = (MEM[PC+2] << 8) | MEM[PC+1];
	} else {
		PC += 3;
	}
	return 10;
}

int
CALL (i8080*core, uint8_t cond)
{
	if(cond){
		SP--;
		MEM[SP--] = (uint8_t)((PC+3) >> 8);
		MEM[SP] = (uint8_t)((PC+3) & 0xff);
		PC=((MEM[PC+2] << 8) | MEM[PC+1]);
		return 17;
	}
	PC += 3;
	return 11;
}

int
RET (i8080*core, uint8_t cond)
{
	if(cond){
		PC = MEM[SP];
		SP++;
		PC |= (MEM[SP] << 8);
		SP++;
		return 11;
	}
	PC++;
	return 5;
}
