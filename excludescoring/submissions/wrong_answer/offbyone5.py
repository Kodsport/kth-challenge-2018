#!/usr/bin/env python3
_pts = [100,75,60,50,45,40,36,32,29,26,24,22,20,18,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]
def points(rank):
    return 1 + (_pts[rank-1] if rank <= 30 else 0)

(_,M) = map(int, input().split())
results = [sorted(map(int, input().split()), reverse=True)[:4] for _ in range(M)]

my_score = sum(results[0])
my_rank = 1

needs = []
for res in results[1:]:
    if sum(res) > my_score:
        my_rank += 1
    elif my_score - sum(res[:3]) + 1 <= points(1):
        needs.append(my_score - sum(res[:3]) + 1)
needs.sort()

def solve(needs):
    lo = 0
    hi = len(needs) + 1
    while hi - lo > 1:
        m = (lo+hi)//2
        cur_need = needs[0]
        cur_tot = cur_group = 0
        for i in range(m):
            cur_group += 1
            cur_tot += points(m-i)
            cur_need = needs[i]
            if (cur_tot + cur_group - 1 - 1) // cur_group >= cur_need:
                cur_tot = cur_group = 0
        if cur_group == 0:
            lo = m
        else:
            hi = m
    return lo

print(my_rank + solve(needs))
