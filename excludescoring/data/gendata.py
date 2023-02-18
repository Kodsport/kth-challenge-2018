import os
import random
import sys

MIN_N = 2
MAX_N = 10
MIN_M = 1
MAX_M = 10**5

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

def save_case(results, short_desc=None, long_desc=None):
    n = max(len(res) for res in results) + 1
    m = len(results)
    assert 2 <= n <= MAX_N
    assert 1 <= m <= MAX_M
    sys.stderr.write('save_case n %d m %d shortdesc %s\n' % (n, m, short_desc))
    me = results[0]
    others = results[1:]
    if SHUFFLE:
        random.shuffle(others)
    results = [me] + others
    f = next_file(short_desc=short_desc, long_desc=long_desc)
    f.write('%d %d\n' % (n, m))
    for res in results:
        while len(res) < n-1:
            res.append(0)
        if SHUFFLE:
            random.shuffle(res)
        f.write('%s\n' % ' '.join(map(str, res)))
    f.close()



def gen_random(n, m):
    results = [[random.randint(0, 101) for _ in range(n-1)] for _ in range(m)]
    save_case(results, short_desc='random')


_pts = [100,75,60,50,45,40,36,32,29,26,24,22,20,18,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]
def points(rank):
    return 1 + (_pts[rank-1] if rank <= 30 else 0)

def points_range(lo, hi):
    tot = 0
    for i in range(lo, hi):
        tot += points(i)
    return (tot + hi-lo-1) / (hi-lo)

def gen_rand_res(n, min_score=0, max_score = 101*4):
    if max_score > 101*(n-1): max_score = 101*(n-1)
    assert min_score <= max_score
    score = random.randint(min_score, max_score)
    n0 = min(n-1, 4)
    res = []
    while n0:
        lo = max(0, score - 101*(n0-1))
        hi = min(101, score)
        res.append(random.randint(lo, hi))
        score = max(0, score - res[-1])
        n0 -= 1
    res.sort(reverse=True)
    lim = res[-1]
    score = sum(res)
    for _ in range(n-1-4):
        res.append(random.randint(0, lim))
    return (res, score)

def gen_groups(n, m, pre_won=0, pre_lost=0):
    while True:
        (me, my_score) = gen_rand_res(n)
        if not pre_won or my_score > 110:
            break

    pre_cands = m-1 - pre_won - pre_lost
    print 'gen tight my score %d, pre_won %d pre_lost %d pre_cands %d' % (my_score, pre_won, pre_lost, pre_cands)

    results = [me]
    for _ in range(pre_lost):
        results.append(gen_rand_res(n, min_score=my_score+1)[0])

    while pre_won:
        (res, score) = gen_rand_res(n, max_score=my_score)
        assert score <= my_score
        if score - (0 if n <= 4 else res[3]) + 101 <= my_score:
            results.append(res)
            pre_won -= 1

    while pre_cands:
        (res, score) = gen_rand_res(n,
                                    min_score=max(0, my_score-101),
                                    max_score=my_score)
        assert score <= my_score
        if score - (0 if n <= 4 else res[3]) + 101 > my_score:
            results.append(res)
            pre_cands -= 1

    save_case(results)

def gen_special():
    m = MAX_M
    n = 10
    scores = [[101]*(n-1) for _ in range(m)]
    save_case(scores, short_desc='all_equal')

    n = 4
    scores = [[101]*(n-1) for _ in range(m)]
    save_case(scores, short_desc='all_equal')

    for i in range(1,m):
        scores[i][n-2] = 100
    save_case(scores, short_desc='one_point_ahead')

    for i in range(1,m):
        scores[i][n-2] = 99
    save_case(scores, short_desc='two_points_ahead')

    scores = [[random.randint(99, 101)] for _ in range(m)]
    scores[0][0] = 101
    save_case(scores, short_desc='mix')

    scores = [[100] for _ in range(m)]
    scores[0][0] = 101
    for i in range(1, 30):
        scores[i][0] = 102 - points(i)
    save_case(scores, short_desc='murphys_law')

    group_sizes = [7,13,5,4]
    i = 1
    scores = [[100] for _ in range(m)]
    scores[0][0] = 101
    for g in group_sizes:
        sc = points_range(i, i+g)
        for j in range(i, i+g):
            scores[j][0] = 102 - sc
        i = i+g
    save_case(scores, short_desc='murphys_law_groups')



def main():
    random.seed(23)

    gen_random(MIN_N, 1)
    gen_random(MIN_N, 2)
    gen_random(MIN_N, 2)
    gen_random(MAX_N, 1)
    gen_random(MAX_N, 2)

    gen_special()

    for n in [4, MAX_N]:
        gen_groups(n, MAX_M)
        gen_groups(n, MAX_M, pre_won=MAX_M-1)
        gen_groups(n, MAX_M, pre_lost=MAX_M-1)

    for _ in range(20):
        n = random.randint(3, MAX_N)
        m = random.randint(1, MAX_M)
        a = random.randint(0, m-1)
        b = random.randint(0, m-1)
        if a > b: (a, b) = (b, a)
        pre_won = a
        pre_lost = b-a
        gen_groups(n, m, pre_won=pre_won, pre_lost=pre_lost)

    gen_random(MIN_N, MAX_M)
    gen_random(MIN_N+1, MAX_M)
    gen_random(MIN_N+2, MAX_M)
    gen_random(MIN_N+3, MAX_M)
    gen_random(MAX_N, MAX_M)
    gen_random(MAX_N, MAX_M)

if __name__=='__main__':
    main()
