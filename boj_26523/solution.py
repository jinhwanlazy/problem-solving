import sys
input = sys.stdin.readline

from math import log, pi, exp
import random

def normal(mu, sigma, x):
    return 1 / (sigma * (2 * pi)**0.5) * exp(-0.5 * ((x - mu) / sigma)**2.0)

def KLD(h1, h2):
    return sum(h1[i] * log(h1[i] / h2[i]) for i in range(N_BINS))

N_SAMPLE = 5000
N_BINS = 20
D_a = [1 / N_BINS] * N_BINS
D_b = [normal(0.5, 0.1, i / N_BINS) / N_BINS + 1e-9 for i in range(N_BINS)]

def make_hist(xs):
    res = [1e-9] * N_BINS
    for x in xs:
        res[min(N_BINS-1, max(0, int(x * N_BINS)))] += 1
    return res

def solve():
    xs = [float(input()) for _ in range(5000)]
    h = make_hist(xs)
    print('A' if KLD(h, D_a) < 0.1 else 'B')
    # print('A' if KLD(h, D_a) < KLD(h, D_b) else 'B')
    # print(KLD(h, D_a))
    # print(KLD(h, D_b))


def make_sample_A():
    for _ in range(N_SAMPLE):
        print(random.uniform(0, 1))

def make_sample_B():
    count = 0
    for _ in range(N_SAMPLE):
        x = random.gauss(0.5, 0.1)
        if x < 0 or 1 < x:
            continue
        count += 1
        print(x)
    
for _ in range(1):
    solve()
    
    
