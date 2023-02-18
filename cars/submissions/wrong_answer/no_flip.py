#!/usr/bin/env python3
def read_car():
    t = input().split()
    (vx, vy) = {'N': [0,1], 'S': [0,-1], 'W': [-1,0], 'E': [1,0]}[t[0]]
    (x, y, s, w, l) = map(int, t[1:])
    w /= 2.0
    l /= 2.0
    if vx: (w, l) = (l, w)
    vx *= s
    vy *= s
    return (x, y, vx, vy, w, l)

def ival(x, vx, w):
    if not vx:
        return (-1e30, 1e30) if abs(x) < w else (0,0)
    t1 = 1.0*(-w-x)/vx
    t2 = 1.0*(w-x)/vx
    return (min(t1, t2), max(t1, t2))

def isect(I):
    return max(i[0] for i in I) < min(i[1] for i in I)

def check(x, y, vx, vy, t, w, h):
    return isect([(0,t), ival(x, vx, w), ival(y, vy, h)])

def solve():
    t = int(input())
    (x1, y1, vx1, vy1, w1, l1) = read_car()
    (x2, y2, vx2, vy2, w2, l2) = read_car()
    if vx2: (w2, l2) = (l2, w2) #oops
    return check(x1-x2, y1-y2, vx1-vx2, vy1-vy2, t, w1+w2, l1+l2)

print(['safe', 'crash'][solve()])
