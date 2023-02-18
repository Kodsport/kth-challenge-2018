import os
import random
import sys

MAX_VAL = 10**4

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), 'secret')
SHUFFLE = True

def next_file(short_desc=None, long_desc=None):
    global CASE
    basename = os.path.join(DEST, '%02d' % CASE)
    CASE += 1
    if short_desc is not None:
        basename += '-' + short_desc
    if long_desc is not None:
        with open(basename+'.desc', 'w') as desc_out:
            desc_out.write(long_desc)
    return open(basename+'.in', 'w')

def save_case(t, C1, C2, short_desc=None, long_desc=None):
    f = next_file(short_desc=short_desc, long_desc=long_desc)
    f.write('%d\n' % t)
    f.write('%s %s\n' % (C1[0], ' '.join(map(str, C1[1:]))))
    f.write('%s %s\n' % (C2[0], ' '.join(map(str, C2[1:]))))
    f.close()

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

def solve(t, C1, C2):
    (d1, x1, y1, s1, w1, l1) = C1
    (d2, x2, y2, s2, w2, l2) = C2
    w1 /= 2.0
    l1 /= 2.0
    w2 /= 2.0
    l2 /= 2.0
    dirs = {'N': [0,1], 'S': [0,-1], 'W': [-1,0], 'E': [1,0]}
    (vx1, vy1) = dirs[d1]
    (vx2, vy2) = dirs[d2]
    if vx1: (w1, l1) = (l1, w1)
    if vx2: (w2, l2) = (l2, w2)
    vx1 *= s1
    vy1 *= s1
    vx2 *= s2
    vy2 *= s2
    return check(x1-x2, y1-y2, vx1-vx2, vy1-vy2, t, w1+w2, l1+l2)

dirs = 'NESW'

def gen_random_car():
    d = random.choice(dirs)
    return [random.choice(dirs)] + [random.randint(i >= 2, MAX_VAL) for i in range(5)]

def valid(C1, C2):
    (d1, x1, y1, s1, w1, l1) = C1
    (d2, x2, y2, s2, w2, l2) = C2
    if d1 in 'WE': (w1, l1) = (l1, w1)
    if d2 in 'WE': (w2, l2) = (l2, w2)
    return (2*abs(x1 - x2) >= w1 + w2 or 2*abs(y1 - y2) >= l1 + l2)


def gen_random(outcome):
    print 'gen_random %d' % outcome
    while True:
        t = random.randint(1, MAX_VAL)
        C1 = gen_random_car()
        C2 = gen_random_car()
        if not valid(C1, C2): continue
        if solve(t, C1, C2) == outcome:
            break
    save_case(t, C1, C2, short_desc='random_%s' % ['safe','crash'][outcome])

def rot90(C):
    (d, x, y, s, w, h) = C
    ndir = dirs[(dirs.index(d) + 1) % 4]
    (nx, ny) = (y, MAX_VAL - x)
    (nw, nh) = (h, w)
    return (ndir, nx, ny, s, nw, nh)

def gen_special():
    save_case(10000,
              ['W', 0, 5000, 9999, 1, 1],
              ['W', 10000, 5000, 10000, 1, 1],
              short_desc='ketchup')
    save_case(9999,
              ['W', 0, 5000, 9999, 1, 1],
              ['W', 10000, 5000, 10000, 1, 1],
              short_desc='almostketchup')

    C1 = ['E', 0, 0, 1, 1, 1]
    C2 = ['S', 10000, 10000, 1, 1, 1]
    for _ in range(4):
        if random.randint(0, 1):
            (C1, C2) = (C2, C1)
        save_case(10000, C1, C2, 'corner')
        if random.randint(0, 1):
            (C1, C2) = (C2, C1)
        save_case(9999, C2, C1, 'almostcorner')
        C1 = rot90(C1)
        C2 = rot90(C2)
    
def main():
    random.seed(42)

    gen_special()
    for i in range(40):
        gen_random(True)
        gen_random(False)

if __name__=='__main__':
    main()
