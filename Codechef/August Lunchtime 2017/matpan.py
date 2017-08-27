# Problem: Mathison and pangrams
# Author: Alexandru Valeanu
# Score: 100p

T = int(input())

for test in range(T):
    prices = list(map(int, input().split()))
    text = input()

    assert 1 <= len(text) and len(text) <= 50000
    assert 1 <= min(prices) and max(prices) <= 10 ** 6

    cost = 0
    for l in [chr(x) for x in range(ord('a'), ord('z') + 1)]:
        if l not in text:
            cost += prices[ord(l) - ord('a')]

    print(cost)
