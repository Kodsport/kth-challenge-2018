#!/usr/bin/python
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
name = "([A-Za-z]{1,10})"

line = stdin.readline();
assert re.match(integer+" "+integer+" "+integer+"\n", line)
[n,k,c] = [int(x) for x in line.split()]
assert(1 <= n and n <= 17 and 0 <= k and k <= (n*(n-1))/2 and 1 <= c and c <= n)
names = []
for i in range(0, n):
  line = stdin.readline()
  assert re.match(name+"\n", line)
  f = re.search(name, line).group(1)
  if(names.count(f) != 0):
    raise Exception('duplicate name')
  names.append(f)
seen = []
for i in range(0, k):
  line = stdin.readline()
  assert re.match(name+" "+name+"\n", line)
  res = re.search(name+" "+name+"\n", line);
  [a, b] = [names.index(res.group(1)), names.index(res.group(2))]
  if(a == b):
    raise Exception('his own worst enemy')
  if(seen.count([a,b]) or seen.count([b,a])):
    raise Exception('multiple enemy')
  seen.append([a,b])
  seen.append([b,a])

assert stdin.readline() == ''

sys.exit(42)
