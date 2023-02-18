#!/usr/bin/env python3
from sys import exit

def with_mask(a, mask):
  return [i ^ mask for i in a]

def with_odd_mask(a, mask, other=0):
  return [x ^ (mask if i % 2 == 1 else other) for i,x in enumerate(a)]

def gen_answer(n, k):
  if n == 0:
    return [0]
  else:
    assert k <= n, 'n=%d k=%d' % (n,k)

  if k == 1:
    rec = gen_answer(n-1, k)
    return \
        with_mask(rec[::+1], 0) + \
        with_mask(rec[::-1], (1<<(n-1)))
  elif k == 2:
    rec = gen_answer(n-1, k)
    res = \
        with_mask(rec[::+1], 0) + \
        with_mask(rec[::-1], (1<<(k-1))-1)
    msk = (1<<(n-1))
    return [v ^ (msk*0 if i % 2 == 1 else 0) for i,v in enumerate(res)]
  else:
    rec = gen_answer(n-2, k-2)
    inv = with_mask(rec, (1<<(k-1))-1)
    mul = (1<<(n-2))
    return \
        with_odd_mask(rec[::+1], 3*mul, 0*mul) + \
        with_odd_mask(inv[::-1], 2*mul, 1*mul) + \
        with_odd_mask(rec[::+1], 0*mul, 3*mul) + \
        with_odd_mask(inv[::-1], 1*mul, 2*mul)

bits, _ = map(int, input().split())
diffs = set(map(int, input().split()))
fmt_str = "{0:0" + str(bits) + "b}"

for diff in diffs:
  if 0 < diff < bits or bits <= diff <= 1:
    if diff % 2 == 1 or diff == 0 or bits in diffs and bits % 2 == 1:
      for i in range(2**bits):
        print(fmt_str.format((1 << diff) - 1 if i % 2 == 1 else 0))
      exit(0)

print('impossible')
