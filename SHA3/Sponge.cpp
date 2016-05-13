#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
#include "Sponge.h"
#include "InternalFun.h"

using namespace std;

#define bitRate   576 
#define capacity  1024



bool SpongeConstruction(string inputString, int outputLen) 
{
	// Transform the input string into binary bits
	BinaryTransfer( inputString ) ;
						
	// Padding using Multirate
	vector< Binary > Message = Padding( inputString ) ; 	
	
	//Initialize the state variable
	Binary stateVar ;
	
	// Absorbing phase
	/*** TODO: Implement your SHA3's absorbing phase here ***/
	for (int i = 0; i<Message.size(); i++) {
		stateVar = internalFun((Message[i] ^ stateVar));
	}

	// Squeezing phase
	string hashVal = ""; // The final output value 
	/*** TODO: Implement your SHA3's squeezing phase here ***/
	for (int i = 0; i<bitRate; i++)
		hashVal += stateVar[i] ? "1": "0";
	while (hashVal.length()<outputLen) {
		stateVar = internalFun(stateVar);
		for (int i = 0; i<bitRate; i++)
			hashVal += stateVar[i] ? "1": "0";
	}
	
	// Print the hash value to the stdout
	PrintHex( hashVal.substr(0, outputLen) ) ;
	cout << endl;

	bool ret_val = true;
	for (int i = 0; i<24; i++)
		ret_val = (hashVal[i]==0)&&ret_val;

	return ret_val;
}


void BinaryTransfer(string& inputString)
{
	string binary = "" ;
	
	for(int i=0; i<inputString.length(); i++)
	{
		for(int k=7; k>=0; k--)
			if( ((inputString[i] >> k) & 0x01) )
				binary += "1" ;
			else
				binary += "0" ;
	}	
	
	inputString = binary ;
}



vector< Binary > Padding(string inputString) 
{
	/*** TODO: Implement with Multirate padding ***/

	int length = inputString.length();
	int append_length = bitRate-length%bitRate;
	string append = "";
	string temp = "";
	vector< Binary > ret_val;

	if (append_length < 2)
		append_length += bitRate;

	for (int i = 0; i<append_length; i++)
		append += "0";
	append.front() = '1';
	append.back() = '1';
	inputString += append;

	length = inputString.length();
	for (int i = bitRate; i<=length; i += bitRate) {
		temp = inputString.substr(i-bitRate, bitRate);
		reverse(begin(temp), end(temp));
		ret_val.push_back((Binary)(temp));
	}

	return ret_val;
}

/*** Print the hash value in hex ***/
void PrintHex(string hashVal) 
{
	
	for(int i=0; i<hashVal.length(); i+=4)
	{
		string Ahex = hashVal.substr(i, 4) ; 
		int Val = 0 ;
		
		for(int k=0; k<4; k++)
			if( Ahex[k]-'0' )	
				Val += (1 << (3-k)) ;
		
		if( Val < 10 )	cout << Val ;
		else	cout << (char)(Val+55) ;			
	}		
}
