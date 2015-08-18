all:
	g++ rsa_fme.c -o rsa -lm -lgmpxx -lgmp
fme:
	g++ rsa_fme.c -o rsa -lm -lgmpxx -lgmp
clean:
	rm rsa *.o
