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
        prev_rank = 1
        cur_need = needs[m-1]
        cur_tot = points(1)
        next_rank = 2
        for i in range(m-2,-1,-1):
            if (cur_tot + points(next_rank) + next_rank - prev_rank) // (next_rank - prev_rank + 1) >= cur_need:
                cur_tot += points(next_rank)
            else:
                prev_rank = next_rank
                cur_need = needs[i]
                cur_tot = points(next_rank)
                if cur_tot < cur_need:
                    hi = m
                    break
            next_rank += 1
        else:
            lo = m
    return lo

print(my_rank + solve(needs))
