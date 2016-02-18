#!/usr/bin/python

def keys(p, q):
	n = p * q
	t = n - (p + q - 1)
	e = 17
	d = 1
	while 1:
		print(d)
		d += t
		if d % e == 0:
			d /= e
			break

	print("Public: {},{}".format(e,n))
	print("Private: {}".format(d))

keys(67, 53)
