matrix = []
with open("./input/d6.txt",'r') as f:
    matrix = [[x for x in line] for line in f.read().splitlines()]

steps = []
dir = 'u'
directions = {'u':'e','e':'s','s':'w','w':'u'}
mov = {'u':(-1,0),'e':(0,1),'s':(1,0),'w':(0,-1)}
for y in range(len(matrix)):
    for x in range(len(matrix[y])):
        if matrix[y][x] == '^':
            steps.append((y, x))

pos = steps[0]
print(pos)

def in_bound(pos):
    return 0<=pos[0]<len(matrix) and 0<=pos[1]<len(matrix[0])

while in_bound(pos):
    new_pos = (pos[0]+mov[dir][0], pos[1]+mov[dir][1])
    yy = new_pos[0]
    xx = new_pos[1]
    if not in_bound(new_pos):
        break
    elif matrix[yy][xx] == '#':
        dir = directions[dir]
    else:
        pos = new_pos
        steps.append(pos)
print(len(set(steps)))