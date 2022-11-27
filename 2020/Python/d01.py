from itertools import combinations

data = open("../input/01.txt").read()
line = [int(x) for x in data.split('\n')]

def solve(n, part):
    comb = list(combinations(line, n))
    for el in comb:
        if sum(el) == 2020:
            print(f"Part 1: {el[0] * el[1]}" if part == 1 else f"Part 2: {el[0] * el[1] * el[2]}")

solve(2, part=1)
solve(3, part=2)