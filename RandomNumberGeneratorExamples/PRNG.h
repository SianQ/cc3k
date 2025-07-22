// Pseudo Random Number Generator : generate repeatable sequence of values that
//   appear random by scrambling the bits of a 32-bit integer value.
//
// Interface :
//   PRNG(s) - set starting seed 
//   seed() - read seed
//   seed(s) - reset seed
//   prng() - generate random value in range [0,UINT_MAX]
//   prng(u) - generate random value in range [0,u]
//   prng(l,u) - generate random value in range [l,u]
//
// Examples : generate random number between 5-21
//   prng() % 17 + 5	values 0-16 + 5 = 5-21
//   prng( 16 ) + 5
//   prng( 5, 21 )

#ifndef __PRNG_H__
#define __PRNG_H__

#include <cstdint>					// uint32_t
#include <cassert>					// assert

class PRNG {
    uint32_t  seed_;	// same results on 32/64-bit architectures
  public:
    PRNG( uint32_t  s = 362436069 ) {			// default seed
	seed_ = s;					// set seed
	assert( ((void)"invalid seed", seed_ != 0) );
    }
    uint32_t seed() {					// read seed
	return seed_;
    }
    void seed( uint32_t  s ) {				// reset seed
	seed_ = s;					// set seed
	assert( ((void)"invalid seed", seed_ != 0) );
    }
    uint32_t operator()() {				// [0,UINT_MAX]
	seed_ = 36969 * (seed_ & 65535) + (seed_ >> 16); // scramble bits
	return seed_;
    }
    uint32_t operator()( uint32_t u ) {			// [0,u]
	assert( ((void)"invalid random range", u < (uint32_t)-1) );
	return operator()() % (u + 1);			// call operator()()
    }
    uint32_t operator()( uint32_t l, uint32_t u ) {	// [l,u]
	assert( ((void)"invalid random range", l <= u) );
	return operator()( u - l ) + l;			// call operator()( uint32_t )
    }
};

#endif
