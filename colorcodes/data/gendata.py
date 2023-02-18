import os
import random
import sys

MAX_DIM = 16

CASE = 1
DEST = os.path.join(os.path.dirname(__file__), 'secret')

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

def save_case(n, P, short_desc=None, long_desc=None):
    sys.stderr.write('save_case n %d palette %s shortdesc %s\n' % (n, P, short_desc))
    f = next_file(short_desc, long_desc)
    f.write('%d %d\n' % (n, len(P)))
    f.write('%s\n' % ' '.join(map(str, P)))
    f.close()



def gen_random(n, p):
    P = random.sample(range(1, n+1), p)
    save_case(n, P, short_desc='n%d-random' % n)



def main():
    random.seed(23)

    # Frontload large cases (n=16 and n=15 since parity of n matters)
    save_case(16, [2, 4, 6, 8, 10, 12, 14, 16, 13], short_desc='n16-possible')
    save_case(16, [15], short_desc='n16-possible')
    save_case(16, [7], short_desc='n16-possible')
    save_case(16, range(1, 17), short_desc='n16-fullpalette')
    save_case(16, [2, 4, 6, 8, 10, 12, 14, 16], short_desc='n16-impossible')
    gen_random(16, 4)

    save_case(15, [10, 15], short_desc='n15-possible')
    save_case(15, [13], short_desc='n15-possible')
    save_case(15, [2, 4, 6, 8, 10, 12, 14], short_desc='n15-impossible')
    save_case(15, [15], short_desc='n15-impossible')
    gen_random(15, 4)

    # Now we return to our regular programming

    save_case(1, [1], short_desc='n1')

    save_case(2, [1], short_desc='n2-possible')
    save_case(2, [2], short_desc='n2-impossible')

    save_case(3, [2], short_desc='n3-impossible')
    save_case(3, [3], short_desc='n3-impossible')
    save_case(3, [2, 3], short_desc='n3-possible')

    save_case(4, [2, 4], short_desc='n4-impossible')
    save_case(4, [3], short_desc='n4-possible')

    for n in range(5, 15):
        save_case(n, range(2, n, 2), short_desc='n%d-impossible' % n)
        gen_random(n, 1)
        gen_random(n, 2)
        gen_random(n, random.randint(1, n))
        gen_random(n, n/2)

    gen_random(15, 2)
    gen_random(15, 3)
    gen_random(15, 8)
    gen_random(16, 2)
    gen_random(16, 3)
    gen_random(16, 8)

if __name__=='__main__':
    main()
