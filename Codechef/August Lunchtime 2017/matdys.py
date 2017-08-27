# Problem: Mathison and the Dynamo shuffle
# Author: Alexandru Valeanu
# Score: 100p

T = int(input())
assert 1 <= T <= 1000

for test in range(T):
    N, K = map(int, input().split())
    assert 1 <= N <= 64
    assert 0 <= K < 2 ** N

    bin_rep = bin(K)[2:]
    bin_rep = '0' * (N - len(bin_rep)) + bin_rep
    print(int(bin_rep[::-1], 2))
