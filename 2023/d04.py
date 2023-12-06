import sys
from collections import defaultdict

class Card:
    def __init__(self, _id, _winning, _cards):
        self.score = 0
        self.id = _id
        self.winning = set(_winning)
        self.cards = set(_cards)
        self.inter = list(self.cards.intersection(self.winning))
        
        self.setScore()

    def setScore(self):
        if len(self.inter) > 0:
            self.score += 2**(len(self.inter) - 1)

N = defaultdict(int)
part1 = 0
with open("input\\d04.txt", 'r') as file:
    file = [f for f in file.read().splitlines()]
    for i, line in enumerate(file):
        N[i] += 1
        id, cards = line.split(':')
        winning, numbers = [int(w) for w in cards.split('|')[0].split()], [int(c) for c in cards.split('|')[1].split()]
        c = Card(id, winning, numbers)
        part1 += c.score
        for j in range(len(c.inter)):
            N[i+1+j] += N[i]

print(f"Part 1: {part1}")
print(f"Part 2: {sum(N.values())}")