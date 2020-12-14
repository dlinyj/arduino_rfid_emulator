/*
Rfid Emulator 
by Alexander Guthmann 
2009

Code for calculating a valid ID

How to compile the Computer program:
$ cd /your/folder/
$ cc -o IDcalculator IDcalculator.c
$ sudo ./IDcalculator

Tested with Ubuntu 9.04
*/




#include <stdio.h>
#include <stdlib.h>

int main() {
	int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;
	int i, j;
	int b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;
	int pc;
	int a, b;
	unsigned int id1, id2;
	int k, l, co, co2, m, n;



	int key[64];

	key[0] = 1;
	key[1] = 1;
	key[2] = 1;
	key[3] = 1;
	key[4] = 1;
	key[5] = 1;
	key[6] = 1;
	key[7] = 1;
	key[8] = 1;
	key[9] = 0;
	key[10] = 0;
	key[11] = 0;
	key[12] = 0;
	key[13] = 1;   //<-Parity
	key[14] = 0;
	key[15] = 0;
	key[16] = 0;
	key[17] = 0;
	key[18] = 1;   //<-Parity
	key[19] = 0;
	key[20] = 0;
	key[21] = 0;
	key[22] = 0;
	key[23] = 1;   //<-Parity
	key[24] = 0;
	key[25] = 0;
	key[26] = 0;
	key[27] = 0;
	key[28] = 1;   //<-Parity
	key[29] = 0;
	key[30] = 0;
	key[31] = 0;
	key[32] = 0;
	key[33] = 1;   //<-Parity
	key[34] = 0;
	key[35] = 0;
	key[36] = 0;
	key[37] = 0;   //<-so far id1
	key[38] = 1;   //<-Parity
	key[39] = 0;
	key[40] = 0;
	key[41] = 0;
	key[42] = 0;
	key[43] = 1;   //<-Parity
	key[44] = 0;
	key[45] = 0;
	key[46] = 0;
	key[47] = 0;
	key[48] = 1;   //<-Parity
	key[49] = 0;
	key[50] = 0;
	key[51] = 0;
	key[52] = 0;
	key[53] = 1;   //<-Parity  
	key[54] = 0;
	key[55] = 0;
	key[56] = 0;
	key[57] = 0;   //<-so far id2 
	key[58] = 1;   //<-Parity
	key[59] = 1;   //<-column parity
	key[60] = 1;   //<-column parity
	key[61] = 1;   //<-column parity
	key[62] = 1;   //<-column parity
	key[63] = 0;   //<-stop bit


	printf("\nRFID emulator by Alex G. 2009");
	printf("\nv1.0");
	printf("\nID calculator");
	printf("\n");

	//getting the ID
	id1 = 0xBCDAFC;
	id2 = 0x932A;

	printf("\nEnter the first 24Bits of Data(Hex):");
	scanf("%x",&id1);
	printf("\nEnter the secound 16Bits of Data(Hex):");
	scanf("%x",&id2);



	j = 37;

	while(id1 > 0){

		if(j == 13 || j == 18 || j == 23 || j == 28 || j == 33 || j == 38) { // skip the parity
			j--;
		}
		key[j] = id1%2; 
		id1 = id1/2;
		j--;
	}
	j = 57;

	while(id2 > 0){
		if(j == 43 || j == 48 || j == 53 || j == 58) { // skip the parity
			j--;
		}
			key[j] = id2%2; 
			id2 = id2/2;
		j--;
	}

	b1 = 9;
	b2 = 10;
	b3 = 11;
	b4 = 12;

	pc = 13;

	for(i=0;i < 10;i++) { //row parity bits
		a1 = key[b1];
		a2 = key[b2];
		a3 = key[b3];
		a4 = key[b4];

		a = a1 + a2 + a3 + a4;

		if(a == 2 || a == 4){
			key[pc] = 0;
		} 

		b1 = b1 + 5;
		b2 = b2 + 5;
		b3 = b3 + 5;
		b4 = b4 + 5;

		pc = pc + 5;

	}

	b1 = 9;
	b2 = 14;
	b3 = 19;
	b4 = 24;
	b5 = 29;
	b6 = 34;
	b7 = 39;
	b8 = 44;
	b9 = 49;
	b10 = 54;

	a = 0;
	pc = 59;

	for(i=0;i < 4;i++){ //column parity bits

		a1 = key[b1];
		a2 = key[b2];
		a3 = key[b3];
		a4 = key[b4];
		a5 = key[b5];
		a6 = key[b6];
		a7 = key[b7];
		a8 = key[b8];
		a9 = key[b9];
		a10 = key[b10];

		a = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10;

		if(a == 2 || a == 4) {
			key[pc] = 0;
		} 


		b1++;
		b2++;
		b3++;
		b4++;
		b5++;
		b6++;
		b7++;
		b8++;
		b9++;
		b10++;

		pc++;

	}   


	printf("\nGenerated ID:\n");

	for(b = 0;b < 64;b++)
	{
		printf("%i",key[b]);
	}

	printf("\n");

	printf("\ntfh.alex94@googlemail.com");

	printf("\n");
} 
