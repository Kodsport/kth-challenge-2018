#!/usr/bin/env python3
n = int(input())
a = list(map(int, input().split()))
stack = []
for i in range(2*n):
    if stack and stack[-1] == a[i]:
        stack.pop()
    else:
        stack.append(a[i])

print(2*n if not stack else 'impossible')
