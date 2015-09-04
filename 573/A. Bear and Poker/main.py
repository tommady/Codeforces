#!/usr/bin/env python3
# -*- coding: utf-8 -*-


players = int(input())
bids = list(map(int, input().split()))

for player in range(players):
    while bids[player] % 2 == 0:  bids[player] //= 2
    while bids[player] % 3 == 0:  bids[player] //= 3

print("YES" if max(bids) == min(bids) else "NO")
