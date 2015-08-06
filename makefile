all:
	gcc rsa_fme.c -o rsa_fme -lm
fme:
	gcc rsa_fme.c -o rsa -lm
clean:
	rm rsa
	rm rsa_fme
