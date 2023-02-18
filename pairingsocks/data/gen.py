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
mode = cmdlinearg('mode')
max_type = int(cmdlinearg('max_type', '1000000000'))
N = int(cmdlinearg('N'))
p = float(cmdlinearg('p', '0.5'))
changes = int(cmdlinearg('changes', '0'))
swaps = int(cmdlinearg('swaps', '0'))

a = []

for i in range(2*N):
    if mode == 'random':
        a.append(random.randint(1, max_type))
    elif mode == 'consecutive':
        a.append(1+(i//2))
    elif mode == 'same':
        a.append(max_type)
    elif mode == 'pairs':
        if i%2 == 0:
            a.append(random.randint(1, max_type))
        else:
            a.append(a[-1])

postprocess = cmdlinearg('postprocess', 'do_nothing')

if postprocess == 'shuffle':
    random.shuffle(a)
elif postprocess == 'large_stack' or postprocess == 'random_stack':
    s = []
    newA = []
    for i in range(0, 2*N, 2):
        s.append(a[i])
        newA.append(a[i])
        while len(s) > 0:
            if i == 2*N-2:
                newA.append(s.pop())
                continue
            if postprocess == 'random_stack' and random.random() < p:
                newA.append(s.pop())
                continue
            break
    a = newA

for i in range(changes):
    j = random.randint(1, 2*N)
    a[j] = random.randint(1, max_type)

for i in range(swaps):
    j = random.randint(1, 2*N)
    k = random.randint(1, 2*N)
    a[j], a[k] = a[k], a[j]

print(N)
print(' '.join(str(x) for x in a))
