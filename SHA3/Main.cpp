#include <iostream>
#include "Sponge.h"
#include <string>
using namespace std ;

int main(int argc, char* argv[])
{
	if ( argc == 1 ) {
		unsigned long long init_value = 1227500180116042;
		string init_string = to_string(init_value);
		for (unsigned long long i = 0; true; i++) {
			cout << init_string << endl;
			if (SpongeConstruction( init_string, 512 )) {
				cout << "success after " << i << " iterations" << endl;
				break;
			}
			init_string = to_string(++init_value);
		}
	}

	else if( argc == 2 ) //default output block size = 512-bit = 64-byte
		SpongeConstruction( argv[1], 512 ) ;
	
	else if( argc == 3 )
		SpongeConstruction( argv[1], atoi(argv[2]) ) ;
	
	else
		cerr << "Invalid usage!\nUsage: ./MSHA3 [Input string] [output length]\n" ;		
}
