#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>

#include <iostream>

using namespace std;

//Ya these are important
mpz_class g_p;
mpz_class g_q;

//Precompute global variables
mpz_class m;
mpz_class dp;
mpz_class dq;
mpz_class qinv;
//mpz_class m1;
//mpz_class m2;
//mpz_class h;

//Inverse Global Variables
mpz_class x = 0, y = 1, v = 0;
mpz_class e,a,f;
mpz_class c,d,iq,r;


mpz_class modInverse(const mpz_class &a,const mpz_class &m);
void  mpz_pow(mpz_class &ret, const mpz_class &base, const mpz_class &exp);

mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n) { //calculates the mod 
//	cout << "Entered mod" <<endl;
	mpz_class ret;
	mpz_class temp, h, m1, m2;
	       	mpz_pow(temp, c, dp);
		m1 = temp%g_p;
		mpz_pow(temp, c, dq);
		m2 = temp%g_q;
	h = qinv*(m1 - m2)%g_p;

	ret = (m2 + (h*g_q));
//	cout << "Exit mod" << endl;
	return ret;
}

void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) { //precomptes values needed for mod fx.
//	cout << "Entered pre-compute" << endl;	
	g_p = p;
	g_q = q;
	dp = modInverse(exp, p-1);
	dq = modInverse(exp, q-1);
	qinv = modInverse(q, p);
//	cout << "Exit pre-computer" << endl;
}

mpz_class modInverse(const mpz_class &a,const mpz_class &m){ //Taken from some forgotten website. tb disected
//	cout << "Entered inverse" << endl;
	if (a%m == 0 || m%a == 0){
		cout << "Error. Numbers not comprime" << endl;
		return 1;
	}
	mpz_class u = 1;
	 e = m, f = a;

	while(f != 1){ //when f == 1, we've reached GCD
		iq = e/f;
		r = e%f;
		c = x-iq*u;
		d = y-iq*v;
		x = u;
		y = v;
		u = c;
		v = d;
		e = f;
		f = r;
	}
		u = (u+m)%m;
//	cout << "Exit inverse" << endl;
		return u;
}

void mpz_pow(mpz_class &ret, const mpz_class &base, const mpz_class &exp){	
//	cout << "Entered Pow" << endl;
	ret = 1;
	
	for(mpz_class counter = 0; counter < exp; counter++){
		ret *= base;
	}
	
//	cout << "Exit pow" << endl;
}
