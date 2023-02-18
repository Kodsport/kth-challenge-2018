#!/usr/bin/env python3
n = int(input())
S = input()
T = input()
def solve(S, T):
    if S == T: return True
    s = sum(1 for i in range(n) if S[i-1] != S[i])
    t = sum(1 for i in range(n) if T[i-1] != T[i])
    if s == 0: return False
    return s - 2*(s == n) >= t
print(['no', 'yes'][solve(S, T)])
