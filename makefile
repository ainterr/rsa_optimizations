ALL = rsa_fme rsa_crt rsa_unopt

CC = g++
DEBUG =
CFLAGS = -c -lm -lgmpxx -lgmp $(DEBUG)
LFLAGS = -lm -lgmpxx -lgmp $(DEBUG)

all: $(ALL)

rsa_unopt: rsa.o mod_unopt.o
	$(CC) rsa.o mod_unopt.o -o rsa_unopt $(LFLAGS)

mod_unopt.o: mod_unopt.cpp
	$(CC) $(CFLAGS) mod_unopt.cpp

rsa_fme: rsa.o mod_fme.o
	$(CC) rsa.o mod_fme.o -o rsa_fme $(LFLAGS)

mod_fme.o: mod_fme.cpp
	$(CC) $(CFLAGS) mod_fme.cpp

rsa_crt: rsa.o mod_crt.o
	$(CC) rsa.o mod_crt.o -o rsa_crt $(LFLAGS)

mod_crt.o: mod_crt.cpp
	$(CC) $(CFLAGS) mod_crt.cpp

rsa.o: rsa.cpp
	$(CC) $(CFLAGS) rsa.cpp

clean:
	rm *.o rsa_unopt rsa_fme rsa_crt
