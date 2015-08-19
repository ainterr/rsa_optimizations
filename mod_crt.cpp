#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>

#include <iostream>

using namespace std;

mpz_class P, Q;
mpz_class dP, dQ, Qi;

// Mod Inverse function adapted from Rosetta Code
mpz_class mod_inv(mpz_class &a, mpz_class &b)
{
	mpz_class b0 = b, t, q;
	mpz_class x0 = 0, x1 = 1;
	mpz_class ret;

	if (b == 1) {
		ret = 1;
		return ret;
	}
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n) {
	mpz_class m1 = pow(m, dP) % P;
	mpz_class m2 = pow(m, dQ) % Q;

	mpz_class h = Qi * (m1 - m2) % P;
	mpz_class ret = m2 + h * Q;

	return ret;
}

void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) {
	P = p, Q = q;
	
	dP = mod_inv(exp, P - 1);
	dQ = mod_inv(exp, Q - 1);
	Qi = mod_inv(Q, P);
}
