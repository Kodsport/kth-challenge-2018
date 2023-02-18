#!/usr/bin/env python3
N = int(input())
socks = list(map(int, reversed(input().split())))
aux = []
while socks:
    if aux and aux[-1] == socks[-1]:
        aux.pop()
    else:
        aux.append(socks[-1])
    socks.pop()
print(2*N if not aux else 'impossible')

