#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int disasm(const uint8_t *buffer, int pc);

int
main(int argc, char **argv)
{
	FILE *f = fopen(argv[1], "r");
	if( f == NULL )
		return 1;

	uint8_t *buffer = malloc(0x800);
	if( fread(buffer,1,0x800,f) != 0x800 )
		return 2;
	fclose(f);

	int pc = 0;
	while(pc < 0x800){
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
	case 55:
		printf("STC:");
		break;
	case 63:
		printf("CMC:");
		break;
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
	case 47:
		printf("CMA:");
		break;
	case 39:
		printf("DAA:");
		break;
	case 0:
		printf("NOP:");
		break;
	case 127:
	case 126:
	case 125:
	case 124:
	case 123:
	case 122:
	case 121:
	case 120:
	case 119:
	case 118:
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
	case 18:
	case 2:
		printf("STAX:");
		break;
	case 26:
	case 10:
		printf("LDAX:");
		break;
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
	case 7:
		printf("RLC:");
		break;
	case 15:
		printf("RRC:");
		break;
	case 23:
		printf("RAL:");
		break;
	case 31:
		printf("RAR:");
		break;
	case 245:
	case 229:
	case 213:
	case 197:
		printf("PUSH:");
		break;
	case 241:
	case 225:
	case 209:
	case 193:
		printf("POP:");
		break;
	case 57:
	case 41:
	case 25:
	case 9:
		printf("DAD:");
		break;
	case 51:
	case 35:
	case 19:
	case 3:
		printf("INX:");
		break;
	case 59:
	case 43:
	case 27:
	case 11:
		printf("DCX:");
		break;
	case 235:
		printf("XCHG:");
		break;
	case 227:
		printf("XTHL:");
		break;
	case 249:
		printf("SPHL:");
		break;
	case 49:
	case 33:
	case 17:
	case 1:
		printf("LXI:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 62:
	case 54:
	case 46:
	case 38:
	case 30:
	case 22:
	case 14:
	case 6:
		printf("MVI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 198:
		printf("ADI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 206:
		printf("ACI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 214:
		printf("SUI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 222:
		printf("SBI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 230:
		printf("ANI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 238:
		printf("XRI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 246:
		printf("ORI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 254:
		printf("CPI:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 50:
		printf("STA:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 58:
		printf("LDA:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 34:
		printf("SHLD:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 42:
		printf("LHLD:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 233:
		printf("PCHL:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 195:
		printf("JMP:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 194:
		printf("JNZ:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 202:
		printf("JZ:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 210:
		printf("JNC:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 218:
		printf("JC:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 226:
		printf("JPO:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 234:
		printf("JPE:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 242:
		printf("JP:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 250:
		printf("JM:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 196:
		printf("CNZ:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 204:
		printf("CZ:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 205:
		printf("CALL:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 212:
		printf("CNC:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 220:
		printf("CC:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 228:
		printf("CPO:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 236:
		printf("CPE:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 244:
		printf("CP:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 252:
		printf("CM:");
		printf("%02x:%02x", buffer[pc+2], buffer[pc+1]);
		opbytes = 3;
		break;
	case 192:
		printf("RNZ:");
		break;
	case 200:
		printf("RZ:");
		break;
	case 201:
		printf("RET:");
		break;
	case 208:
		printf("RNC:");
		break;
	case 216:
		printf("RC:");
		break;
	case 224:
		printf("RPO:");
		break;
	case 232:
		printf("RPE:");
		break;
	case 240:
		printf("RP:");
		break;
	case 248:
		printf("RM:");
		break;
	case 251:
		printf("EI:");
		break;
	case 243:
		printf("DI:");
		break;
	case 219:
		printf("IN:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 211:
		printf("OUT:");
		printf("%02x", buffer[pc+1]);
		opbytes = 2;
		break;
	case 118:
		printf("HLT:");
		break;
	default:
		printf("IDK"); exit(5);
	}
	printf("\n");
	return opbytes;
}
