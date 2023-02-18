import sys
import re

def read(n):
    line = sys.stdin.readline()
    assert line[-1] == '\n'
    line = line[:-1]
    assert len(line) == n
    for sym in set(line): assert sym in 'BR'
    return line

line = sys.stdin.readline()
assert re.match('^(0|[1-9][0-9]*)\n$', line)
n = int(line)
assert 3 <= n <= 10**5

pre = read(n)
post = read(n)
assert pre != post

assert sys.stdin.read() == ''
sys.exit(42)

