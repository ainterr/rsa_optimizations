#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>

#include <iostream>

using namespace std;

size_t exp_bitsize;
int * bin;

int * bin_array(mpz_class num) {
	size_t size = exp_bitsize;
	int * bin = (int *)malloc(size * sizeof(int));
	int x = 0;
	mpz_class n = 1;
	mpz_class res;
	
	while(x < size) {
		res = n & num;
		res /= n;
		bin[x] = res.get_ui();

		x++;
		n *= 2;
	}

	return bin;
}

mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n) {
	int x;
	mpz_class ret = 1;
	mpz_class val = m % n;

	for(x = 0; x < exp_bitsize; x++) {
		if(x) val = (val * val) % n;
		if(bin[x]) ret *= val;
	}

	ret %= n;

	return ret;
}

void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) {
	exp_bitsize = mpz_sizeinbase(exp.get_mpz_t(), 2);
	bin = bin_array(exp);
}
