"""
- Un insetto muore a meno che non vi sia esattamente un insetto adiacente ad esso.
- Uno spazio vuoto diventa infestato da un bug se esattamente uno o due bug sono adiacenti ad esso.
"""
import os

INPUT = '''#.##.
###.#
#...#
##..#
.#...'''

# CONVERSION
matrix = []
for line in INPUT.split('\n'):
    matrix.append([])
    for el in line:
        matrix[-1].append(1 if el == '#' else 0)

def display_all(fields, step):
    for field in fields:
        for row in field:
            #print(''.join(row))
            print(''.join('#' if x == 1 else '.' for x in row))
        print(step)


def check_level_below(fields, level, pos):
    if pos[0] == 1:
        return sum(fields[level-1][0][x] for x in range(5))

    if pos[0] == 3:
        return sum(fields[level-1][4][x] for x in range(5))

    if pos[1] == 1:
        return sum(fields[level-1][y][0] for y in range(5))

    if pos[1] == 3:
        return sum(fields[level-1][y][4] for y in range(5))


def check_for_bug(fields, level, pos):
    count = 0

    for side in [(0, -1), (0, 1), (-1, 0), (1, 0)]:
        new_pos = (pos[0] + side[0], pos[1] + side[1])

        if new_pos[0] == 2 and new_pos[1] == 2:
            count += check_level_below(fields, level, pos)

        elif new_pos[0] == -1:
            count += fields[level+1][1][2]

        elif new_pos[0] == 5:
            count += fields[level+1][3][2]

        elif new_pos[1] == -1:
            count += fields[level+1][2][1]

        elif new_pos[1] == 5:
            count += fields[level+1][2][3]

        elif fields[level][new_pos[0]][new_pos[1]] == 1:
            count += 1

    return count


def evolve(fields, iterations):
    new_fields = [[[0]*5 for _ in range(5)] for _ in range(iterations*2+3)]

    for level in range(iterations*2+1):
        for y in range(5):
            for x in range(5):
                if x == 2 and y == 2:
                    continue

                if fields[level][y][x] == 1:
                    if check_for_bug(fields, level, (y,x)) == 1:
                        new_fields[level][y][x] = 1

                elif fields[level][y][x] == 0:
                    if check_for_bug(fields, level, (y, x)) in (1, 2):
                        new_fields[level][y][x] = 1

    return new_fields


def solve():
    iterations = 200
    fields = [[[0]*5 for _ in range(5)] for _ in range(iterations*2+3)]

    for r in range(5):
        for c in range(5):
            fields[iterations+1][r][c] = matrix[r][c]

    for step in range(iterations):
        fields = evolve(fields, iterations)

        display_all(fields, step)

    return sum(fields[level][y][x] for level in range(iterations*2+3) for y in range(5) for x in range(5))

result = solve()
print(f"Solution: {result}")