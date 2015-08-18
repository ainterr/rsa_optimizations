#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

int * bin_array(mpz_class num) {
	static int bin[sizeof(num)*8] = { 0 };
	int x = 0;
	mpz_class n;

	while(num > 0) {
		n = num & 1;
		if(n != 0) bin[x] = 1;
		else  bin[x] = 0;

		num >>= 1;
		x++;
	}

	return bin;
}

mpz_class mod(mpz_class m, mpz_class exp, mpz_class n) {
	int * bin = bin_array(exp);
	int x;
	mpz_class ret = 1;
	mpz_class val = m % n;

	for(x = 0; x < sizeof(exp)*8; x++) {
		if(x) val = (val * val) % n;
		if(bin[x]) ret *= val;
	}

	ret %= n;

	return ret;
}
