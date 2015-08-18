fme:
	g++ -c mod_fme.cpp -lm -lgmpxx -lgmp
	g++ -c rsa.cpp -lm -lgmpxx -lgmp
	g++ -o rsa mod_fme.o rsa.o -lm -lgmpxx -lgmp
crt:
	g++ -c mod_crt.cpp -lm -lgmpxx -lgmp
	g++ -c rsa.cpp -lm -lgmpxx -lgmp
	g++ -o rsa mod_crt.o rsa.o -lm -lgmpxx -lgmp
mm:
	g++ -c mod_mm.cpp -lm -lgmpxx -lgmp
	g++ -c rsa.cpp -lm -lgmpxx -lgmp
	g++ -o rsa mod_mm.o rsa.o -lm -lgmpxx -lgmp
clean:
	rm rsa *.o
