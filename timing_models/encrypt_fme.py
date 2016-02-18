#!/usr/bin/python

# This is a dummy encryption script that just returns the sum of hardcoded
# values. It's meant to simulate the responses of an encryption server for the
# purpose of the Brumley et all attack.

# usage: ./encrypt.py [message] [exp] [mod] <p> <q>
# Note: p and q are optional and the exp is expected in integer form

import sys

# Some arbitrary timing values
low = 200
high = 300

length = 16 # Assume 16 bit key

key = bin(int(sys.argv[2]))[2:]
key = "0"*(length - len(key)) + key

time = sum([low if x == "0" else high for x in key])

print(time)
