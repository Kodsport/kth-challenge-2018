import sys

t = int(input())

C1 = input().split()
d1 = C1[0]
(x1,y1,_,w1,h1) = map(int, C1[1:])

C2 = input().split()
d2 = C2[0]
(x2,y2,_,w2,h2) = map(int, C2[1:])

if d1 in 'WE': (w1, h1) = (h1, w1)
if d2 in 'WE': (w2, h2) = (h2, w2)

assert (2*abs(x1-x2) >= w1 + w2 or 2*abs(y1-y2) >= h1+h2)

sys.exit(42)
