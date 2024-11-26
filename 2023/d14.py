from collections import defaultdict

data = open("input/d14.txt",'r').readlines()

matrix = [[x for x in row] for row in data]

def moveNorth(x, y, matrix):
    matrix[y][x] = '.'
    while (y > 0 and matrix[y-1][x] == '.'):
        y -= 1
    matrix[y][x] = 'O'

for y in range(len(matrix)):
    for x in range(len(matrix[y])):
        if matrix[y][x] == 'O':
            moveNorth(x, y, matrix)

def score(matrix):
    ans = 0
    for y in range(len(matrix)):
        for x in range(len(matrix[y])):
            if matrix[y][x] == 'O':
                ans += len(matrix) - y
    return ans
print(score(matrix))

########################## PART 2 ############################

matrix = [[x for x in row] for row in data]

BY_SCORE = defaultdict(list)

def nn(x, y, matrix):
    matrix[y][x] = '.'
    while (y > 0 and matrix[y-1][x] == '.'):
        y -= 1
    matrix[y][x] = 'O'

def ww(x, y, matrix):
    matrix[y][x] = '.'
    while(x < len(matrix[y])-1 and matrix[y][x-1] == '.'):
        x -= 1
    matrix[y][x] = 'O'

def ss(x, y, matrix):
    matrix[y][x] = '.'
    while(y < len(matrix)-1 and matrix[y+1][x] == '.'):
        y += 1
    matrix[y][x] = 'O'

def ee(x, y, matrix):
    matrix[y][x] = '.'
    while(x < len(matrix[y])-1 and matrix[y][x+1] == '.'):
        x += 1
    matrix[y][x] = 'O'

target = 10**9
t = 0
while t < target:
    for func in [nn,ww]:
        for y in range(len(matrix)):
            for x in range(len(matrix[y])):
                if matrix[y][x] == 'O':
                    func(x, y, matrix)

    for func in [ss,ee]:
        for y in range(len(matrix)-1,-1,-1):
            for x in range(len(matrix[y])-1,-1,-1):
                if matrix[y][x] == 'O':
                    func(x, y, matrix)
    sc = score(matrix)
    BY_SCORE[sc].append(t)
    timestep = BY_SCORE[sc]
    if (len(timestep) >= 6):
        cycleLength = timestep[-1]-timestep[-2]
        if (cycleLength == timestep[-2]-timestep[-3] and cycleLength != 0):
            amt = (target-t)//cycleLength
            t += amt * cycleLength
print(score(matrix)) #96003

# BY_GRID = {}

# target = 10**9
# t = 0
# while t<target:
#   t += 1
#   for j in range(4):
#     G = roll(G)
#     if t==1 and j==0:
#       print(score(G)) # part1
#     G = rotate(G)
#   #print('='*80)
#   #show(G)
#   #print('='*80)
#   Gh = tuple(tuple(row) for row in G)
#   if Gh in BY_GRID:
#     cycle_length = t-BY_GRID[Gh]
#     amt = (target-t)//cycle_length
#     t += amt * cycle_length
#   BY_GRID[Gh] = t
# print(score(G))