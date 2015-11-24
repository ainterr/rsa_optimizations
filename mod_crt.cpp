#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>

#include <iostream>

using namespace std;

//Ya these are important
mpz_class g_p; //Prime 1
mpz_class g_q; //Prime 2

//Precompute global variables
mpz_class m;
mpz_class dp;
mpz_class dq;
mpz_class qinv;

//Functions
void mul_inv(mpz_class &ret, const mpz_class &a, const mpz_class &b);
void mpz_pow(mpz_class &ret, const mpz_class &base, const mpz_class &exp);

mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n) { //calculates the mod 
	cout << "Entered mod" <<endl;
	mpz_class ret;			//Declare some local varialbes
	mpz_class temp, h, m1, m2;

	mpz_pow(temp, m, dp);		//Calc m1, m2, qinv.
		m1 = temp%g_p;
	mpz_pow(temp, m, dq);
		m2 = temp%g_q;
	h = qinv*(m1 - m2)%g_p;

	ret = (m2 + (h*g_q));
	cout << "Exit mod" << endl;
	return ret;
}

void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) { //precomptes values needed for mod fx.
	cout << "Entered pre-compute" << endl;	
	mpz_class temp;

	g_p = p; 			//Store the original values of P & Q globally
	g_q = q;
	mul_inv(temp, exp, p-1);	//Calculate and store dp, dq, qinv globally
		dp = temp;
	mul_inv(temp, exp, q-1);
		dq = temp;
	mul_inv(temp, q, p);
		qinv = temp;
	cout << "dp: " << dp << " dq: " << dq << " qinv: " << qinv << endl;
	cout << "Exit pre-computer" << endl;
}

void mul_inv(mpz_class &ret, const mpz_class &a, const mpz_class &b)
{
	cout << "Entered Inverse" << endl;
	mpz_class b0 = b, t, h;
	mpz_class x0 = 0, x1 = 1;
	mpz_class loc_a = a, loc_b = b;
	if (loc_b == 1) {
		ret = 1;
	}
	
	else {
		while (loc_a > 1) {
			cout << "Begin while - loc_b = " << loc_b << " loc_a: " << loc_a <<  endl;
			h = loc_a / loc_b;
			cout << "l2" << endl;
			t = loc_b, loc_b = loc_a % loc_b, loc_a = t;
			cout << "l3" << endl;
			t = x0, x0 = x1 - h * x0, x1 = t;
			cout << "Begin end" << endl;
		}

		if (x1 < 0){ 
			x1 += b0;
		}
		
		ret = x1;
	}

	cout << "Exit Inverse" << endl;
}

void mpz_pow(mpz_class &ret, const mpz_class &base, const mpz_class &exp){	
	cout << "Entered Pow" << endl;
	ret = 1;
	
	for(mpz_class counter = 0; counter < exp; counter++){
		ret *= base;
	}
	
	cout << "Exit pow" << endl;
}
