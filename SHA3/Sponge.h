#ifndef SPONGE_H
#define SPONGE_H

#include <string>
#include <vector>
#include <bitset>

#define stateSize 1600

using std::string ;
using std::vector ;
using std::bitset ;

typedef bitset<stateSize> Binary ;

bool SpongeConstruction( string inputString, int outputLen ) ;
void BinaryTransfer(string& inputString) ;
vector<Binary> Padding(string inputString) ;
void PrintHex(string hashVal) ;


#endif  //* SPONGE_H *// 

