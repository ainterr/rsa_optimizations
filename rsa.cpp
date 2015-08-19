#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include <time.h>
#include <stdint.h>
#include <iostream>

using namespace std;

// If you'd like to define the keys up here, simple uncomment this code and substitute the values with your own
/*
#define HARDCODED_KEYS 1
#define EXP "158306798557072761079432079748149567825016765046913883964014613775776306037474501463369921628992533312298808609078756097042285249267890219078764623497470192144382514657581587703973692641931288995078102752352350184834385610173615683815147403068520116706643320240742275484768353777145356967526250960072595031109023860493087239629618880211298451357897808581975171080587694389253548071795540933573481163120602186428765592638764414969533247632383239347611397572387560951725016051582947213376518971466490963334721098767600820592472431715518848339987055020980311250201733120122669828244108187929299248552223223894566135545400347395519737305188238745862278377831456612518021279116789394170665428199664514569903444448841288369247960611262064577076902541441590646306319732815527028743410427325307867085533659713405324088567498669018644897978482350367315185541212736392389216659163570687063127142133114283227999573805923235609377191041858837705257557287987683494489939245908739573552554516582936801486538385236278031855734878145407050620095988949937666850728403590671448282858402427230605736136330498082797183589963287248500425533468417140659042008156430852402229291556649868936670281819509988720694760732191525783523778328847496836923703312737"
#define MOD "715958364297486546329634960351561536577746444750506881053731677801604566198189662715124874321943527409297289339120449819326495644280568717670622947357235800328921183018005970143904761208629555370259721211849836040541793508656976818038321396377172237154322219213134118311038824200729781214599952326980723245724387326280826611248798050680275109146542590645014615078909373210165604856894925551280466150537223482988200306726016386989048405912876982756497699448041100137547607271588683425785447783658782572911987899381150712798900404205366003978864924774686816534709197673968629669010704458789765016380308703635234340296713700225706992999441659061943544901181390056235663409008322181462166603323951083429017995004587660272585619764694220034272255338359971389550871726055789666787195714454790017955312813039690435170078343265427018842974067370648439758420373556942410294736075271841522709415144611715775347563980480170739794412780191470182979085746411978862782003998299068558934086783542205382407135682727579619750565064640699779975357623009397403595084526951044861438636676160329372203580148769149922658869071822944571338856466414213283516319832616987526768573589294348111370949186498201244479135082298818427968963158235718319254698242413"
#define FIRST_PRIME "1"
#define SECOND_PRIME "1"
#define KEY_BASE 10
/**/

int keygen();
int * bin_array(mpz_class num);
int prime(mpz_class num);
void print_bin(mpz_class num);
mpz_class mod(mpz_class &m, mpz_class &exp, mpz_class &n);
void precompute(mpz_class &p, mpz_class &q, mpz_class &exp, mpz_class &n);

int main(int argc, char *argv[]) {
	if(argc == 1) {	
		cout << "Usage: rsa_fme keygen\n";
		cout << "Usage: rsa_fme mod [message] [exponent] [modulus] [first_prime] [second_prime]\n";
		return 0;
	}
	if(!strcmp(argv[1], "keygen")) return keygen();	
	if(!strcmp(argv[1], "mod")) {
		mpz_class m(argv[2]);

		#ifndef HARDCODED_KEYS
		mpz_class e(argv[3]);
		mpz_class n(argv[4]);
		mpz_class p(argv[5]);
		mpz_class q(argv[6]);
		#endif
		#ifdef HARDCODED_KEYS
		mpz_class e(EXP, KEY_BASE);
		mpz_class n(MOD, KEY_BASE);
		mpz_class p(FIRST_PRIME, KEY_BASE);
		mpz_class q(SECOND_PRIME, KEY_BASE);
		#endif

		precompute(p, q, e, n);

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
