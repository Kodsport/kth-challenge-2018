#!/usr/bin/python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
zeroes = cmdlinearg('zeroes')
n = int(cmdlinearg('n'))

assert zeroes in ['yes', 'no']

gr = []
has_left = [False] * n
if zeroes == 'no':
    for i in range(n-2, -1, -1):
        j = random.randrange(i+1, n)
        gr.append((i, j))
        has_left[j] = True
    for i in range(1, n):
        if not has_left[i]:
            j = random.randrange(i)
            gr.append((j, i))

while len(gr) < 2*(n-1):
    i = random.randrange(0, n)
    j = random.randrange(0, n)
    if i >= j:
        continue
    gr.append((i, j))

random.shuffle(gr)

print(n)
for (i, j) in gr:
    print(i+1, j+1)
