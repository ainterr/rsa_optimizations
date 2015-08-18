#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include <time.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int keygen();
int * bin_array(mpz_class num);
int prime(mpz_class num);
void print_bin(mpz_class num);
mpz_class mod(mpz_class m, mpz_class exp, mpz_class n);

int main(int argc, char *argv[]) {
	if(argc == 1) {	
		cout << "Usage: rsa_fme keygen\n";
		cout << "Usage: rsa_fme mod [message] [exponent] [modulus]\n";
		return 0;
	}
	if(!strcmp(argv[1], "keygen")) return keygen();	
	if(!strcmp(argv[1], "mod")) {
		mpz_class m, e, n;
		m = argv[2];
		e = argv[3];
		n = argv[4];

		uint64_t diff;
		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC, &start);
	
		cout << mod(m, e, n) << "\n";

		clock_gettime(CLOCK_MONOTONIC, &end);
		diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

		cout << "Computed in " << (double)diff / 1000000000. << " s\n";
	}
}

int keygen() {
	mpz_class p = 4, q = 4; // Arbitrary, non-prime numbers
	mpz_class n, t, e, d;

	cout << "RSA Key Generator\n\n";

	// Take in two prime numbers
	while(!prime(p)) {
		cout << "Enter a prime number(p): ";
		cin >> p;
	}
	while(!prime(q)) {
		cout << "Enter a prime number(q): ";
		cin >> q;
	}

	// Calculate n
	n = p * q;
	cout << "n: " << n << "\n";

	// Calculate the totient of n
	t = n - (p + q - 1);
	cout << "t(n): " << t << "\n";

	// Print possible values of e
	cout << "Some possible values for e:\n";
	mpz_class x;
	int y = 0;
	for(x = t-1; x > 0; x--) {
		// e must be coprime to t and should not be equal to p or q
		if (t % x == 0 || !prime(x) || x == p || x == q) continue;
		
		cout << x << " (";
		print_bin(x);
		cout << ")\n";

		y++;
		if (y > 25) break; // limit the number of options printed to the screen
	}
	printf("\n");
	
	// Allow the user to select one
	e = 4; // Arbitrary, non-prime number
	while(t % e == 0 || !prime(e) || e == p || e == q) {
		cout << "Please select a value for e: ";
		cin >> e;
	}

	// Calculate a value for d
	d = 1;
	while(1) { d += t; if (d % e == 0) { d /= e; break; } }
	cout << "d: " << d << "\n";

	cout << "\nPublic Key: e=" << e << ",n=" << n << "\n";
	cout << "\bPrivate Key: d=" << d << "\n";

	// MOD TESTING - decrypt the cyphertext "5"
	//mpz_class message = 5;
	//cout << mod(message, d, n) << "\n";

	return 0;
}

int prime(mpz_class num) {
	mpz_class x;
	for(x = 2; x < sqrt(num) + 1; x++) 
		if (num % x == 0) return 0;
	return 1;
}

void print_bin(mpz_class num) {
	mpz_class n;
	while(num != 0) {
		n = num & 1;
		n != 0 ? cout << 1: cout << 0;
		num >>= 1;
	}
}
