#!/usr/bin/env python3

bits, _ = map(int, input().split())
diffs = sorted(map(int, input().split()))
fmt_str = "{0:0" + str(bits) + "b}"
for i in range(2**bits):
  print(fmt_str.format((1 << diffs[0]) - 1 if i % 2 == 1 else 0))
