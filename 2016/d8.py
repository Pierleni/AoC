import sys
sys.path.insert(0, "C:/Users/Marco/Documents/python/AoC/advent-of-code")
import lib.mylib as mlib
import time
import os


TALL = 6
WIDE = 50
matrix = [[0] * WIDE for _ in range(TALL)]


def show_matrix(matrix):
    for r in matrix:
        print(''.join('#' if x == 1 else '.' for x in r))

        

def make_a_rect(a, b):
    for y in range(b):
        for x in range(a):
            matrix[y][x] = 1



data = open("./input/d8.txt", "r").read()
for line in data.split('\n'):
    line = line.split()

    if line[0] == "rect":
        a, b = line[1].split('x')
        make_a_rect(int(a), int(b))
    
    else:
        if line[1] == "column":
            col = int(line[2].split('=')[1])
            val = int(line[-1])
            mlib.rotate_column(col, val, matrix)

        elif line[1] == "row":
            row = int(line[2].split('=')[1])
            val = int(line[-1])
            mlib.rotate_row(row, -val, matrix)

    os.system("cls")
    show_matrix(matrix)
    time.sleep(0.05)