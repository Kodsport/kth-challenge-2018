#!/usr/bin/env python3
y = int(input())
cur = 2018*12 + 3
while cur//12 < y: cur += 26
print(['no', 'yes'][cur//12==y])

