#include "stdio.h"
#include <stdlib.h>
#include <string.h>

char parity (unsigned long val)
{ // calc XOR parity bit of all '1's in 24 bit value
	unsigned long i,p;
	p=0;
	for(i=0;i!=24;i++) {
		p^=val;val>>=1;
	}
return(p&1);
}

unsigned long add_ecc(unsigned long cmd)
{// add ecc byte to b29-24 of 24 bit command packet (lsbyte first)
	cmd&=0x00ffffff; 
	if(parity(cmd & 0b111100010010110010110111)) cmd|=0x01000000;           
	if(parity(cmd & 0b111100100101010101011011)) cmd|=0x02000000;
	if(parity(cmd & 0b011101001001101001101101)) cmd|=0x04000000;
	if(parity(cmd & 0b101110001110001110001110)) cmd|=0x08000000;
	if(parity(cmd & 0b110111110000001111110000)) cmd|=0x10000000;
	if(parity(cmd & 0b111011111111110000000000)) cmd|=0x20000000;
	return(cmd);
}

int main(int argc,char *argv[])
{
	unsigned long data, ecc; //use  unsigned long int type to suit 32bit system
	char *endptr;

	if (argc != 2) {
        printf("Usage: mipi_ecc_cal 0x00xxxxDT\n24bit hex data prefix with 0x, and lsb first! eg. 0x00009c21 or 0x9c21\n");
       	return 1;
    }

	data = strtoul(argv[1], &endptr, 0);

	if (*endptr != '\0') {
        printf("input data error: input data must be hex data:[%s]\n ", endptr);
		return 2;
    } else {

		if(data > 0xFFFFFF || !data) {
			printf("input data error: please input 24bit hex data! eg. 0x00009c21 or 0x9c21\n");
			return 3;
		}
		ecc = add_ecc(data);
		printf("0x%08lx ecc result = 0x%08lx\n", data, ecc);
		return 0;
	}
}
