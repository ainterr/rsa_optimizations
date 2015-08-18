fme:
	g++ -c mod_fme.c -lm -lgmpxx -lgmp
	g++ -c rsa.c -lm -lgmpxx -lgmp
	g++ -o rsa mod_fme.o rsa.o -lm -lgmpxx -lgmp
clean:
	rm rsa *.o
