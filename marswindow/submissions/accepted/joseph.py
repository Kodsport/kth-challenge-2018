#!/usr/bin/env python3
y = int(input())
y = (y - 2018) % 13
print('yes' if y in [0, 2, 4, 6, 8, 11] else 'no')
