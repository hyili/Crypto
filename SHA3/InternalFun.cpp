#include <iostream>
#include <string>
#include <vector>
#include "InternalFun.h"




bitset<64> RC[24] = 
{ 
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808A,
	0x8000000080008000,
	0x000000000000808B,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008A,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000A,
	0x000000008000808B,
	0x800000000000008B,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800A,
	0x800000008000000A,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008
};

bitset<64> Rotate(bitset<64> L, bitset<64> temp, int offset) {
	temp.reset();
	bitset<64> overflow;
	
	temp = temp^L;
	overflow = (temp >> (64-offset));
	temp <<= offset;
	temp = temp^overflow;


	return temp;
}

bitset<64> Theta_transform(bitset<64> L[5][5], bitset<64> temp, int x) {
	temp.reset();

	x = x>=5 ? x%5 : (x<0 ? x%5+5 : x);
	for (int y = 0; y<5; y++) {
		temp ^= L[x][y];
	}

	return temp;
}

int Rho_transform(bitset<64> L[5][5], int x, int y) {
	int temp;
	int t = 24;
	static int tr[24][2] = {
		1, 0,
		0, 2,
		2, 1,
		1, 2,
		2, 3,
		3, 3,
		3, 0,
		0, 1,
		1, 3,
		3, 1,
		1, 4,
		4, 4,
		4, 0,
		0, 3,
		3, 4,
		4, 3,
		3, 2,
		2, 2,
		2, 0,
		0, 4,
		4, 2,
		2, 4,
		4, 1,
		1, 1
	};

	if (x==0 && y==0)
		return 0;

	for (int i = 0; i<24; i++) {
		if (tr[i][0]==x && tr[i][1]==y) {
			t = i;
			break;
		}
	}

	if (t==24)
		exit(-1);

	temp = ((t+1)*(t+2))/2;
	temp = temp>=64 ? temp%64 : (temp<0 ? temp%64+64 : temp);

	return temp;
}


Binary internalFun(Binary stateVar) 
{
	for(int i=0; i<24; i++) {
		string temps = RC[i].to_string();
		reverse(begin(temps), end(temps));
		bitset<64> tempb = (bitset<64>) temps;
		stateVar = roundFun( i, stateVar, tempb ) ;
	}
		
	return stateVar ;
}

/*** Round function in SHA-3 ***/
Binary roundFun(int RC, Binary stateVar, bitset<64> singleRC)
{
	
	/*** TODO: Implement your SHA3's 5 functions as follows ***/
	bitset<64> L[5][5], tL[5][5];
	bitset<64> temp1, temp2, temp3;

	/*** Lane ***/
	for (int y = 0; y<5; y++) {
		for (int x = 0; x<5; x++) {
			int index = 64*(5*y+x);
			for (int z = 0; z<64; z++) {
				L[x][y][z] = 0^stateVar[index+z];
				tL[x][y][z] = 0^stateVar[index+z];
			}
		}
	}
	
	/*** Theta ***/
	for (int y = 0; y<5; y++) {
		for (int x = 0; x<5; x++) {
			tL[x][y] = L[x][y]^Theta_transform(L, temp1, x-1)^Rotate(Theta_transform(L, temp2, x+1), temp3, 1);
		}
	}

	/*** Rho ***/
	/*** Pi ***/	
	for (int y = 0; y<5; y++) {
		for (int x = 0; x<5; x++) {
			L[y][(2*x+3*y)%5] = Rotate(tL[x][y], temp1, Rho_transform(tL, x, y));
		}
	}

	/*** Xi ***/
	for (int y = 0; y<5; y++) {
		for (int x = 0; x<5; x++) {
			tL[x][y] = L[x][y]^(~(L[(x+1)%5][y])&L[(x+2)%5][y]);
		}
	}

	/*** Iota ***/
	tL[0][0] = tL[0][0]^singleRC;

	/*** Lane ***/
	for (int y = 0; y<5; y++) {
		for (int x = 0; x<5; x++) {
			int index = 64*(5*y+x);
			for (int z = 0; z<64; z++) {
				stateVar[index+z] = 0^tL[x][y][z];
			}
		}
	}

	return stateVar;
}
