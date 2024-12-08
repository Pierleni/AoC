from collections import defaultdict

data = open("./input/d8.txt",'r').read().splitlines()
m = [[c for c in line] for line in data]
antennas = defaultdict(list)
for y in range(len(data)):
    for x in range(len(data[y])):
        if data[y][x] != '.':
            antennas[data[y][x]].append((y, x))

antinodes = set()
antinode2 = set()
for k, values in antennas.items():
    for (ay, ax) in values:
        for (by,bx) in values:
            if ((ay,ax) != (by,bx)):
                dy = ay-by
                dx = ax-bx
                p1 = (ay+dy, ax+dx)
                p2 = (ay-dy, ax-dx)               

                # part 1
                if (p1 not in values and 0<=p1[0]<len(m) and 0<=p1[1]<len(m[0])):
                    antinodes.add(p1)
                if (p2 not in values and 0<=p2[0]<len(m) and 0<=p2[1]<len(m[0])):
                    antinodes.add(p2)

                # part 2
                for y in range(len(m)):
                    for x in range(len(m[y])):
                        dy1 = y - ay
                        dy2 = y - by
                        dx1 = x - ax
                        dx2 = x - bx

                        if (dy1 * dx2 == dy2 * dx1):
                            antinode2.add((y, x))

print(len(antinodes))
print(len(antinode2)) 