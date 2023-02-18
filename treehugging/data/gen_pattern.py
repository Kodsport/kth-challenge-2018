#!/usr/bin/python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
mode = cmdlinearg('mode')

ed = []
if mode == 'multiedge1':
    ed = [(0, n-1) for _ in range(2*(n-1))]
elif mode == 'multiedge2':
    ed = [(i, i+1) for i in range(n-1)] + [(0, n-1) for _ in range(n-1)]
elif mode == 'cycle1':
    assert n % 2 == 0
    for i in range(n//2):
        ed.append((i, i + n//2))
    for i in range(n//2-1):
        ed.append((i+1, i + n//2))
    ed.append((0, n-1))
    for i in range(n//2-1):
        ed.append((i, i+1))
        ed.append((i + n//2, i+1 + n//2))
elif mode == 'cycle2':
    assert n % 2 == 0
    for i in range(n//2):
        ed.append((i, n-1 - i))
        ed.append(((i+1) % (n//2), n-1 - i))
    for i in range(n//2-1):
        ed.append((i, i+1))
        ed.append((i + n//2, i+1 + n//2))
elif mode == 'cycle3':
    for i in range(n-2):
        ed.append((i, i+1))
        ed.append((i, i+2))
    ed.append((n-2, n-1))
    ed.append((0, n-1))
else:
    assert False, "unknown mode"

random.shuffle(ed)

print(n)
for (i, j) in ed:
    print(i+1, j+1)
