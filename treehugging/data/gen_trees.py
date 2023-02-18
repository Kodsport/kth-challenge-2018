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

def gen_tree(n, mode):
    eds = []
    assert mode in ['random', 'star', 'line', 'shallow', 'deep', 'deeper']
    depth = [0]
    for i in range(1, n):
        if mode == 'random':
            pred = random.randrange(i)
        elif mode == 'star':
            pred = 0
        elif mode == 'line':
            pred = i-1
        elif mode == 'shallow':
            pred = int(random.uniform(0, i**0.2) ** 5)
        elif mode == 'deep':
            pred = i-1 - int(random.uniform(0, i**0.1) ** 10)
        elif mode == 'deeper':
            if i < 4:
                pred = random.randrange(i)
            else:
                hi = math.log2(math.log2(i))
                pred = i - int(2 ** 2 ** min(random.uniform(-3, hi), random.uniform(-3, hi), random.uniform(-3, hi)))
        else:
            assert False
        assert 0 <= pred < i
        eds.append((pred, i))
        depth.append(depth[pred] + 1)
    print('depth =', max(depth), file=sys.stderr)
    return eds

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
mode = cmdlinearg('mode')
modes = mode.split(',') if ',' in mode else [mode, mode]
error, *errorargs = cmdlinearg('error', '').split(',')

a = gen_tree(n, modes[0])
b = gen_tree(n, modes[1])
ed = a[:]
for x in b:
    ed.append((n-1 - x[1], n-1 - x[0]))
random.shuffle(ed)

def remap(lut):
    global ed
    ed2 = []
    for (a, b) in ed:
        aa = lut[a]
        bb = lut[b]
        assert aa != bb
        if aa < bb:
            ed2.append((aa, bb))
        else:
            ed2.append((bb, aa))
    ed = ed2

if error == 'swap':
    # repeatedly swap nodes, but maintain no node having degree 0
    swaps = 0
    gr = [[] for _ in range(n)]
    for (a, b) in ed:
        gr[a].append(b)
        gr[b].append(a)

    def deg0(a):
        # at position a is node ren[a], which borders node j, which is at position inv[j]
        haslt = False
        hasgt = False
        for j in gr[ren[a]]:
            assert inv[j] != a
            if inv[j] > a:
                hasgt = True
            else:
                haslt = True
        return not haslt or not hasgt

    ren = list(range(n))
    inv = list(range(n))
    for _ in range(int(errorargs[0])):
        a = random.randrange(n)
        b = random.randrange(n)
        if a == b:
            continue
        ren[a], ren[b] = ren[b], ren[a]
        inv[ren[a]] = a
        inv[ren[b]] = b
        if deg0(a) or deg0(b) or any(deg0(inv[j]) for j in gr[ren[a]]) or any(deg0(inv[j]) for j in gr[ren[a]]):
            ren[a], ren[b] = ren[b], ren[a]
            inv[ren[a]] = a
            inv[ren[b]] = b
        else:
            swaps += 1

    print(swaps, "swaps", file=sys.stderr)
    remap(inv)

elif error == 'deg0':
    a = random.randrange(n)
    b = random.randrange(n)
    inv = list(range(n))
    inv[b] = a
    remap(inv)

print(n)
for (i, j) in ed:
    print(i+1, j+1)
