#include <iostream>
#include <iomanip>
using namespace std;
#include <unistd.h>					// getpid
#include "PRNG.h"

PRNG prng1, prng2, prng3;				// global, normally one generator for entire program
extern PRNG prng1;					// declaration to use prng1 in another translation unit

int main() {
    uint32_t seed = getpid();				// start with a pseudo random-number
    prng1.seed( seed );					// synchronize all generators with same seed
    prng2.seed( seed );
    prng3.seed( seed );

    // check 3 forms of generation are identical for 3 generators
    for ( int i = 0; i < 10; i += 1 ) {			// generate 10 random numbers between 0-1
	cout << prng1() % 2 << prng2( 1 ) << prng3( 0, 1 ) << endl;
    }
    cout << endl;
    for ( int i = 0; i < 10; i += 1 ) {			// generate 10 random numbers between 5-21
	cout << setw( 2 ) << prng1() % 17 + 5 << "  ";	// 0-16 + 5 = 5-21
	cout << setw( 2 ) << prng2( 16 ) + 5 << "  ";
	cout << setw( 2 ) << prng3( 5, 21 ) << endl;
    }
}
