#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n, m = map(int, input().split())
letters = list(input() for i in range(n))
match_word = sorted("face")
faces = 0

for i in range(n-1):
    for j in range(m-1):
        faces += sorted(letters[i][j:j+2] + letters[i+1][j:j+2]) == match_word
        
print(faces)