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

# CONVERT INPUT IN MATRIX:
matrix = []
for line in INPUT.split('\n'):
    matrix.append([])
    for dot in line:
        matrix[-1].append(1 if dot == '#' else 0)

# MATRICE NUMERATA PROGRESSIVAMENTE (i numeri saranno le potenze)
rating, n, results = [[0] * 5 for _ in range(5)], 0, set()
for r in range(5):
    for c in range(5):
        rating[r][c] = n
        n += 1


def IsSafe(y, x):
    if 0 <= x < len(matrix[0]) and 0 <= y < len(matrix):
        return matrix[y][x]
    return 0


def display(line):
    os.system('cls')
    for row in line:
        print(''.join('#' if x == 1 else '.' for x in row))



n = 0
while 1:
    count = 0
    new_matrix = [[0] * 5 for _ in range(5)]

    for y in range(len(matrix)):
        for x in range(len(matrix[0])):
            cell = matrix[y][x]

            if not cell:
                if sum((IsSafe(y - 1, x), IsSafe(y + 1, x),
                        IsSafe(y, x - 1), IsSafe(y, x + 1))) in (1, 2):
                    new_matrix[y][x] = 1
            else:
                if sum((IsSafe(y - 1, x), IsSafe(y + 1, x),
                        IsSafe(y, x - 1), IsSafe(y, x + 1))) == 1:
                    new_matrix[y][x] = 1

    matrix = new_matrix
    n += 1

    for r in range(5):
        for c in range(5):
            if new_matrix[r][c] == 1:
                count += 2 ** rating[r][c]

    if count not in results:
        results.add(count)
        continue

    display(new_matrix)
    print(count)
    break
