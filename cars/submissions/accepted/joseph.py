#!/usr/bin/env python3
num_dir = { \
    'N': [0, 1], \
    'E': [1, 0], \
    'S': [0, -1], \
    'W': [-1, 0]}

t1 = int(input())

vec = input().split()
dir1 = num_dir[vec[0]]
x1, y1, s1, w1, l1 = map(int, vec[1:])

vec = input().split()
dir2 = num_dir[vec[0]]
x2, y2, s2, w2, l2 = map(int, vec[1:])

# Swap l1, w1 based on direction faced.
if dir1[0]:
    l1, w1 = w1, l1
if dir2[0]:
    l2, w2 = w2, l2

def ball_overlap(x1, r1, x2, r2):
    return overlap([2*x1 - r1, 2*x1 + r1], [2*x2 - r2, 2*x2 + r2])

def overlap(int1, int2):
    return max(0, min(int1[1], int2[1]) - max(int1[0], int2[0]))

crash = False
t = 0
min_dist = 10**4

# Simulate the fast car moving across the starting grid.
for i in range(2*max(x1, y1, x2, y2, t1)):
    delt = min(0.5/max(s1, s2), t1 - t)
    x1 += delt * s1 * dir1[0]
    y1 += delt * s1 * dir1[1]
    x2 += delt * s2 * dir2[0]
    y2 += delt * s2 * dir2[1]
    t += delt
    #print "%s %s %s %s" % (x1, y1, x2, y2)
    if ball_overlap(x1, w1, x2, w2) > 0.1 and ball_overlap(y1, l1, y2, l2) > 0.1:
        crash = True

# Simulate far away crashes.
relative_s = max(s1, s2) - min(s1, s2)
for i in range(int(max(x1, y1, x2, y2, t1))):
    relative_s = max(s1, s2) - min(s1, s2)
    if not relative_s:
        break
    delt = min(1.0/relative_s, t1 - t)
    x1 += delt * s1 * dir1[0]
    y1 += delt * s1 * dir1[1]
    x2 += delt * s2 * dir2[0]
    y2 += delt * s2 * dir2[1]
    t += delt
    a = ball_overlap(x1, w1, x2, w2)
    b = ball_overlap(y1, l1, y2, l2)
    #print "%s %s" % (a, b)
    if ball_overlap(x1, w1, x2, w2) > 0.1 and ball_overlap(y1, l1, y2, l2) > 0.1:
        crash = True

print("crash" if crash else "safe")
