#ifndef INTERNAL_FUN_H
#define INTERNAL_FUN_H

#include <string>
#include <bitset>

#define stateSize 1600
using std::string ;
using std::bitset ;

typedef bitset<stateSize> Binary ;

Binary internalFun(Binary stateVar) ;
Binary roundFun(int i, Binary stateVar, bitset<64> singleRC) ;



#endif 
