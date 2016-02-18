#!/usr/bin/python

# This script implements an attack on RSA described by Brumley at all
# Note: this does not actually work for now... This provies it's ineffective
# against FME, however.
# key value - 0b1010101010101010

import os

def calc_time(guess):
	return int(os.popen("python ../timing_models/encrypt_fme.py 0 {} 0".format(guess)).read().strip())

# Read in and parse data
f = open("idealized_data.csv")
data = f.read()
f.close()
data = [ x.split(",") for x in data.split("\n") ][1:-1]

# Calculating the high and low values
low = [ int(x[2]) for x in data if x[1] == "0" ]
high = [ int(x[2]) for x in data if x[1] == "1" ]
low = sum(low)/len(low)
high = sum(high)/len(high)
print("Low value: {}\nHigh value: {}\n".format(low, high))

# Start the attack
key = "1010101010101010"
total_time = calc_time(int(key, 2))
print("Actual Time: {}\n".format(total_time))

guess = "101" # 3 bits for free
for x in range(16-3):
	g_low = guess + "0" + "0"*(16-len(guess)-1)
	g_high = guess + "1" + "0"*(16-len(guess)-1)

	g_low_time = calc_time(int(g_low, 2))
	g_high_time = calc_time(int(g_high, 2))

	g_low_diff = abs(total_time - g_low_time)
	g_high_diff = abs(total_time - g_high_time)

	print("Low: {} {} {}".format(g_low, g_low_time, g_low_diff))
	print("High: {} {} {}".format(g_high, g_high_time, g_high_diff))
	print

	if g_low_diff < g_high_diff: guess += "0"
	else: guess += "1"

print(guess)
