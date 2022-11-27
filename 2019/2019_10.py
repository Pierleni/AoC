"""
https://0xdf.gitlab.io/adventofcode2019/10
"""

INPUT = '''.###.###.###.#####.#
#####.##.###..###..#
.#...####.###.######
######.###.####.####
#####..###..########
#.##.###########.#.#
##.###.######..#.#.#
.#.##.###.#.####.###
##..#.#.##.#########
###.#######.###..##.
###.###.##.##..####.
.##.####.##########.
#######.##.###.#####
#####.##..####.#####
##.#.#####.##.#.#..#
###########.#######.
#.##..#####.#####..#
#####..#####.###.###
####.#.############.
####.#.#.##########.'''

import math
def dist(a1,a2):  #manhattan distance
    return math.sqrt(pow(a1[0] - a2[0], 2) + pow(a1[1] - a2[1], 2))

def can_see(x, y):
    if x == y:
        return False
    for z in asteroids:
        if x == z or y == z:
            continue
        if ((dist(x,y) + dist(y,z)) - dist(x,z)) < 0.0001:
            return False
    return True

lines = [line for line in INPUT.split('\n')]

asteroids = []
for x in range(len(lines)):
    for y in range(len(lines[x])):
        if lines[x][y] == '#':
            asteroids.append((x,y))

matrix = {}
for a in asteroids:
    matrix[a] = 0

for i in range(len(asteroids)):
    for j in range(len(asteroids)):
        x, y = asteroids[i], asteroids[j]
        if can_see(x,y):
            matrix[x] +=1

print(matrix)
massimo=max(matrix, key=matrix.get)
print(massimo, matrix[massimo])
