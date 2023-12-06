import sys

reds = 12
greens = 13
blues = 14

class Dice:
    def __init__(self, game, dices) -> None:
        self.r = 0
        self.g = 0
        self.b = 0
        self.id = int(game.split()[1])
        self.possible = 1
        self.power = 0
        self.configure(dices)

    def configure(self, dices):
        sets = dices.split(';')
        for group in sets:
            dice = group.split(',')
            for d in dice:
                d = d.split()
                n = int(d[0])
                if d[1] == "blue":
                        if (self.b <= n): self.b = n
                        if n > blues: self.possible = 0
                elif d[1] == "red":
                        if (self.r <= n): self.r = n
                        if n > reds: self.possible = 0
                elif d[1] == "green": 
                        if (self.g <= n): self.g = n
                        if n > greens :self.possible = 0

        self.power = self.r * self.g * self.b

part1 = 0
part2 = 0
bags = list()

data = open("input/d02.txt", 'r').read().splitlines()
for line in data:
    game, dices = line.split(':')
    dice = Dice(game, dices)
    bags.append(dice)

for dice in bags:
    part2 += dice.power
    if (dice.possible == 1):
        part1 += dice.id
print(f"Part 1: {part1}")
print(f"Part 2: {part2}")