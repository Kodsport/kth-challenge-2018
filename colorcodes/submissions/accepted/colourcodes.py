#!/usr/bin/env python3
def gen_gray(n):
    if n == 0:
        return [0]
    R = gen_gray(n-1)
    return R + list(reversed([r ^ (1<<n-1) for r in R]))

def gen_odd(n, d):
    if d == 1:
        return gen_gray(n)
    sub = [gen_odd(n-2, d-2)]
    sub.append(list(reversed([r ^ ((1<<d-1)-1) for r in sub[0]])))
    R = []
    for i in range(4):
        cur_high = [0,1,3,2][i] << n-2
        for v in sub[i%2]:
            R.append(v | cur_high)
            cur_high ^= 3 << n-2
    return R

def gen_even(n, d):
    R = gen_odd(n-1, d-1)
    for i in range(1, len(R), 2):
        R[i] ^= 1 << n-1
    return R + list(reversed([r ^ ((1<<n)-1) for r in R]))

def solve(n, D):
    for d in D:
        if d == 1 or d % 2 == 1 and d < n:
            return gen_odd(n, d)
    for opp in D:
        if opp == n and opp % 2 == 1:
            for d in D:
                if d < n:
                    return gen_even(n, d)
    return []

(n, _) = map(int, input().split())
D = list(map(int, input().split()))
R = solve(n, D)
if R:
    for v in R:
        w = bin(v)[2:]
        print('0'*(n-len(w)) + w)
else:
    print('impossible')
