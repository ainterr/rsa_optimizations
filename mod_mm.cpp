#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include<iostream>

using namespace std;

//Global Variables
mpz_class  r, r_p; // r = coprime to m, r_p is mod. mul. inv. of r & m

//Functions
void mul_inv(mpz_class &ret, const mpz_class &a, const mpz_class &b);
void mm(mpz_class &ret, const mpz_class &y, const mpz_class &n);

mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n) {
	//End goal is to return m^exp%n
//	cout << "Begin mod";
	mpz_class orig_m = m;
	mpz_class loc_m = m;
	cout << "m: " << m << " exp: " << exp << " n: " << n << endl;
	for(int i=0; i < exp-1; i++) //Repeat multiplaction "exp" number of times
	{		
		 mm(loc_m, orig_m, n); //montgomery multiplication algorithm returns m*orig_m%n
	}
//	cout << "End mod";
	return loc_m;
}

void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n) {
//	cout << "Begin Precompute";
	mpz_class loc_n = n;
	int mag = 0;
	while(loc_n>=1)
	{		
		mag++;
		loc_n/=10;
	}
	r = pow(10, mag);	 //Set r = 10^x s.t r is just greater than n	
//	cout << "r: " << r << endl;

	mul_inv(r_p, r, n); 	 //r_p is the mod. mult. inv. of r and the modulus "n"
//	cout << "r_p: " << r_p << endl;
//	cout << "End Precompute";
}

/**
 * This function takes in a number and and a modulus b and sets the 
 * return variable to be the mod. mul. inv. of the two input numbers.
*/
void mul_inv(mpz_class &ret, const mpz_class &a, const mpz_class &b)
{
//	cout << "Begin Inverse";
	mpz_class b0 = b, t, h;
	mpz_class x0 = 0, x1 = 1;
	mpz_class loc_a = a, loc_b = b;

	if (loc_b==1){
		ret = 1;
	}
	else
	{
		while (loc_a>1)
		{
			h = loc_a/loc_b;
			t = loc_b, loc_b = loc_a%loc_b, loc_a = t;
			t = x0, x0 = x1-h*x0, x1=t;
		}
		if(x1 < 0 ){
			x1 += b0;
		}
		ret = x1;
	}
//	cout << "End Inverse";
}

void mm(mpz_class &ret, const mpz_class &y, const mpz_class &n)
{
	mpz_class x_p = (ret*r)%n;
	mpz_class y_p = (y*r)%n;
	
	mpz_class a = x_p*y_p;
	
	while(a%r != 0)
	{
		a += n;
	}
	ret = a/r; //ret*y%n in montgomery form
	ret = (ret*r_p)%n; //ret*y%n in normal numbers
//	cout << ret << endl;
}
