#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int disasm(const uint8_t *buffer, int pc);

#define MEM buffer
#define PC pc

int
main(int argc, char **argv)
{
	FILE *f = fopen(argv[1], "r");
	if( f == NULL )
		return 1;

	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, 0L, SEEK_SET);

	uint8_t *buffer = malloc(size);
	if( fread(buffer,1,size,f) != size )
		return 2;
	fclose(f);

	int pc = 0x100;
	while(pc < size){
		pc += disasm(buffer, pc);
	}

	free(buffer);
	return 0;
}

int
disasm(const uint8_t *buffer, int pc)
{
	int opbytes = 1;
	printf("%04x:", pc);
	switch(buffer[pc]){
	/*
clear:
/CASES$/+,/default:$/- d
/CASES$/ r !./opdecode.sh
/CASES$/+,/default:$/- >
	*/
	//CASES
	/* STC */
	case 55:
		printf("STC:");
		break;
	/* CMC */
	case 63:
		printf("CMC:");
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
		printf("INC:");
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
		printf("DCR:");
		break;
	/* CMA */
	case 47:
		printf("CMA:");
		break;
	/* DAA */
	case 39:
		printf("DAA:");
		break;
	/* NOP */
	case 0:
		printf("NOP:");
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
		printf("MOV:");
		break;
	/* STAX */
	case 18:
	case 2:
		printf("STAX:");
		break;
	/* LDAX */
	case 26:
	case 10:
		printf("LDAX:");
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
		printf("ADD:");
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
		printf("ADC:");
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
		printf("SUB:");
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
		printf("SBB:");
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
		printf("ANA:");
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
		printf("XRA:");
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
		printf("ORA:");
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
		printf("CMP:");
		break;
	/* RLC */
	case 7:
		printf("RLC:");
		break;
	/* RRC */
	case 15:
		printf("RRC:");
		break;
	/* RAL */
	case 23:
		printf("RAL:");
		break;
	/* RAR */
	case 31:
		printf("RAR:");
		break;
	/* PUSH */
	case 245:
	case 229:
	case 213:
	case 197:
		printf("PUSH:");
		break;
	/* POP */
	case 241:
	case 225:
	case 209:
	case 193:
		printf("POP:");
		break;
	/* DAD */
	case 57:
	case 41:
	case 25:
	case 9:
		printf("DAD:");
		break;
	/* INX */
	case 51:
	case 35:
	case 19:
	case 3:
		printf("INX:");
		break;
	/* DCX */
	case 59:
	case 43:
	case 27:
	case 11:
		printf("DCX:");
		break;
	/* XCHG */
	case 235:
		printf("XCHG:");
		break;
	/* XTHL */
	case 227:
		printf("XTHL:");
		break;
	/* SPHL */
	case 249:
		printf("SPHL:");
		break;
	/* LXI */
	case 49:
	case 33:
	case 17:
	case 1:
		printf("LXI:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
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
		printf("MVI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* ADI */
	case 198:
		printf("ADI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* ACI */
	case 206:
		printf("ACI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* SUI */
	case 214:
		printf("SUI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* SBI */
	case 222:
		printf("SBI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* ANI */
	case 230:
		printf("ANI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* XRI */
	case 238:
		printf("XRI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* ORI */
	case 246:
		printf("ORI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* CPI */
	case 254:
		printf("CPI:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* STA */
	case 50:
		printf("STA:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* LDA */
	case 58:
		printf("LDA:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* SHLD */
	case 34:
		printf("SHLD:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* LHLD */
	case 42:
		printf("LHLD:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* PCHL */
	case 233:
		printf("PCHL:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JMP */
	case 195:
		printf("JMP:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JNZ */
	case 194:
		printf("JNZ:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JZ */
	case 202:
		printf("JZ:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JNC */
	case 210:
		printf("JNC:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JC */
	case 218:
		printf("JC:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JPO */
	case 226:
		printf("JPO:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JPE */
	case 234:
		printf("JPE:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JP */
	case 242:
		printf("JP:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* JM */
	case 250:
		printf("JM:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CNZ */
	case 196:
		printf("CNZ:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CZ */
	case 204:
		printf("CZ:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CALL */
	case 205:
		printf("CALL:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CNC */
	case 212:
		printf("CNC:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CC */
	case 220:
		printf("CC:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CPO */
	case 228:
		printf("CPO:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CPE */
	case 236:
		printf("CPE:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CP */
	case 244:
		printf("CP:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* CM */
	case 252:
		printf("CM:");
		printf("%02x:%02x", MEM[PC+2], MEM[PC+1]);
		PC+=2;
		break;
	/* RNZ */
	case 192:
		printf("RNZ:");
		break;
	/* RZ */
	case 200:
		printf("RZ:");
		break;
	/* RET */
	case 201:
		printf("RET:");
		break;
	/* RNC */
	case 208:
		printf("RNC:");
		break;
	/* RC */
	case 216:
		printf("RC:");
		break;
	/* RPO */
	case 224:
		printf("RPO:");
		break;
	/* RPE */
	case 232:
		printf("RPE:");
		break;
	/* RP */
	case 240:
		printf("RP:");
		break;
	/* RM */
	case 248:
		printf("RM:");
		break;
	/* EI */
	case 251:
		printf("EI:");
		break;
	/* DI */
	case 243:
		printf("DI:");
		break;
	/* IN */
	case 219:
		printf("IN:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* OUT */
	case 211:
		printf("OUT:");
		printf("%02x", MEM[PC+1]);
		PC++;
		break;
	/* HLT */
	case 118:
		printf("HLT:");
		break;
	default:
		printf("IDK");
	}
	printf("\n");
	return opbytes;
}
