def inBound(y, x, Y, X):
    return 0<=y<Y and 0<=x<X

rolls = []
avaiable = []
movable = True
with open("./input/d04.txt", 'r') as f:
    lines = f.read().splitlines()
    matrix = [[x for x in line] for line in lines]
    Y = len(matrix)
    X = len(matrix[0])

for y in range(Y):
    for x in range(X):
        if matrix[y][x] == '@':
            rolls.append((y, x))
for (y, x) in rolls:
    count_roll = 0
    for (dy, dx) in [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]:
        ny = y + dy
        nx = x + dx
        if (not inBound(ny, nx, Y, X)): continue
        if matrix[ny][nx] == '@': count_roll += 1
    if (count_roll < 4): avaiable.append((y, x))
print(f"Part 1: {len(avaiable)}")

# part 2
count = 0
rolls = {(y, x) for y in range(Y) for x in range(X) if matrix[y][x] == '@'}

while True:
    avaiable = []
    for (y, x) in rolls:
        cnt = 0
        for (dy, dx) in [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]:
            ny, nx = y + dy, x + dx
            if (ny, nx) in rolls:
                cnt += 1
        if (cnt < 4): 
            avaiable.append((y, x))
    # exit if found any
    if not avaiable:
        break
    count += len(avaiable)
    # remove them
    for cell in avaiable:
        rolls.remove(cell)

print(f"Part 2: {count}")