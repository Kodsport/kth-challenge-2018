#!/usr/bin/env python3
def solve(n, E):
    adj = [set() for _ in range(2*n)]
    for (e, (u, v)) in enumerate(E):
        adj[v].add((n+u, e))
        adj[n+u].add((v, e))
    leaves = []
    for u in range(2, 2*n):
# oops        if not adj[u]: return 'impossible'
        if len(adj[u]) == 1: leaves.append(u)
    ans = [0]*len(E)
    while leaves:
        u = leaves.pop()
        if not adj[u]: return 'impossible'
        (v, e) = adj[u].pop()
        ans[e] = 'LR'[u>n]
        adj[v].remove((u, e))
        if len(adj[v]) == 1:
            leaves.append(v)
    for u in range(2, 2*n):
        if adj[u]:
            while adj[u]:
                (v, e) = adj[u].pop()
                ans[e] = 'LR'[u>n]
                adj[v].remove((u,e))
                u = v
    return ''.join(ans) if 0 not in ans else 'impossible'
    
n = int(input())
E = [list(map(int, input().split())) for _ in range(2*(n-1))]
print(solve(n, E))
