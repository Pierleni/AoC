file = open("input/d10.txt", 'r').read()

data = []
for line in file.split('\n'):                                                       # Parsing
    pos, vel = line.split('> ')[0], line.split('> ')[1]
    x, y = int(pos[10:].split(',')[0]), int(pos[10:].split(',')[1])
    vx, vy = int(vel[10:].split(',')[0]), int(vel[10:len(vel)-1].split(',')[1])
    data.append([x, y, vx, vy])

seconds = {}
for i in range(10200):                                                              # Find the second where dots
    min_x = min(x + i * vx for (x, y, vx, vy) in data)                              # are in closet position
    max_x = max(x + i * vx for (x, y, vx, vy) in data)
    min_y = min(y + i * vy for (x, y, vx, vy) in data)
    max_y = max(y + i * vy for (x, y, vx, vy) in data)

    distance = (max_x - min_x + max_y - min_y)
    seconds[i] = distance

second = min(seconds, key=seconds.get)                                              # here we go (for Part 2)

dots = []
for (x, y, vx, vy) in data:                                                         # Find the position of every dot
    x_coord = (x + second * vx)                                                     # at that second
    y_coord = (y + second * vy)
    dots.append((x_coord, y_coord))

min_Yrange = min(dots, key=lambda t: t[0])[0]                                       # Find min e max range
max_Yrange = max(dots, key=lambda t: t[0])[0]                                       # of dots coordinate needed
min_Xrange = min(dots, key=lambda t: t[1])[1]                                       # to build a grid
max_Xrange = max(dots, key=lambda t: t[1])[1]

grid = []
for x in range(min_Xrange,max_Xrange + 1):                                           # Put them on a grid
    grid.append([])
    for y in range(min_Yrange, max_Yrange + 1):
        if (y, x) in dots:
             grid[-1].append('#')
        else: grid[-1].append(' ')

for r in grid:                                                                       # Show it (Part 1)
    print(*r)

print(f"Second {second}")