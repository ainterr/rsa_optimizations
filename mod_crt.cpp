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
int prime2(mpz_class num);

mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n) { //calculates the mod 
//	cout << "Entered mod" <<endl;
	mpz_class ret;			//Declare some local varialbes
	mpz_class temp, h, m1, m2;
	mpz_class difM;

	mpz_pow(temp, m, dp);		//Calc m1, m2, qinv.
		//cout << temp << endl;
		m1 = temp%g_p;
	mpz_pow(temp, m, dq);
		//cout << temp << endl;
		m2 = temp%g_q;
	difM = m1 - m2;
	while (difM < 0){
		difM += g_p;
	}
	h = qinv*(difM)%g_p;
	
	cout << "m1: " << m1 << " m2: " << m2 << " h: " << h << endl;
	ret = (m2 + (h*g_q));
//	cout << "Exit mod" << endl;
	return ret;
}

void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) { //precomptes values needed for mod fx.
//	cout << "Entered pre-compute" << endl;	
//	cout << "M: " << m << " P: " << p << " Q: " << q << " E: " << exp << endl;
	mpz_class temp;

	g_p = p; 			//Store the original values of P & Q globally
	g_q = q;
	//mul_inv(temp, exp, p-1);	//Calculate and store dp, dq, qinv globally
	//	dp = temp;
	dp = exp%(p-1);
	//mul_inv(temp, exp, q-1);
	//	dq = temp;
	dq = exp%(q-1);
	mul_inv(temp, q, p);
		qinv = temp;
	cout << "dp: " << dp << " dq: " << dq << " qinv: " << qinv << endl;
//	cout << "Exit pre-computer" << endl;
}

void mul_inv(mpz_class &ret, const mpz_class &a, const mpz_class &b)
{
//	cout << "Entered Inverse" << endl;
	mpz_class b0 = b, t, h;
	mpz_class x0 = 0, x1 = 1;
	mpz_class loc_a = a, loc_b = b;
	if (loc_b == 1) {
		ret = 1;
	}
/*	else if (!prime2(b) || !prime2(a)){
		cout << "Error! NUMBER NOT PRIME" << endl;
	}	
*/	else {
		while (loc_a > 1) {
//			cout << "Begin while - loc_b = " << loc_b << " loc_a: " << loc_a <<  endl;
			h = loc_a / loc_b;
		//	cout << "l2" << endl;
			t = loc_b, loc_b = loc_a % loc_b, loc_a = t;
	//		cout << "l3" << endl;
			t = x0, x0 = x1 - h * x0, x1 = t;
//			cout << "Begin end" << endl;
		}

		if (x1 < 0){ 
			x1 += b0;
		}
		
		ret = x1;
	}

//	cout << "Exit Inverse" << endl;
}

void mpz_pow(mpz_class &ret, const mpz_class &base, const mpz_class &exp){	
//	cout << "Entered Pow" << endl;
	ret = 1;
	
	for(mpz_class counter = 0; counter < exp; counter++){
		ret *= base;
	}
	
//	cout << "Exit pow" << endl;
}

int prime2(mpz_class num) {
	mpz_class x;
	for(x = 2; x < sqrt(num) + 1; x++){
		if (num % x == 0) return 0;
	}
	return 1;
}
