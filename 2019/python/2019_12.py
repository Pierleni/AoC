coor = '''<x=-1, y=-4, z=0>
<x=4, y=7, z=-1>
<x=-14, y=-10, z=9>
<x=1, y=2, z=17>'''


class Planets(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.vx = 0
        self.vy = 0
        self.vz = 0


def calc(a, b):
    """
    To apply gravity, consider every pair of moons.
    On each axis (x, y, and z), the velocity of each moon changes by exactly
    +1 or -1 to pull the moons together. For example, if Ganymede has an x position of 3,
    and Callisto has a x position of 5, then Ganymede's x velocity changes by +1 (because 5 > 3)
    and Callisto's x velocity changes by -1 (because 3 < 5).
    However, if the positions on a given axis are the same,
    the velocity on that axis does not change for that pair of moons.
    """
    return 1 if a < b else 0 if a == b else -1


matrix = []
for line in coor.split('\n'):
    line = line.split('<')[1].split('>')[0].split(', ')
    x, y, z = line[0][2:], line[1][2:], line[2][2:]
    matrix.append([int(x),int(y), int(z)])

pl = [Planets(matrix[i][0], matrix[i][1], matrix[i][2]) for i in range(4)]

for n in range(1000):
    for i in range(4):
        for j in range(4):
            if i == j: continue
            pl[i].vx += calc(pl[i].x, pl[j].x)
            pl[i].vy += calc(pl[i].y, pl[j].y)
            pl[i].vz += calc(pl[i].z, pl[j].z)
    for i in range(4):
        pl[i].x += pl[i].vx
        pl[i].y += pl[i].vy
        pl[i].z += pl[i].vz

result = []
for i in range(4):
    pot, kin = 0, 0
    pot += abs(pl[i].x) + abs(pl[i].y) + abs(pl[i].z)
    kin += abs(pl[i].vx) + abs(pl[i].vy) + abs(pl[i].vz)
    result.append(pot * kin)

print(sum(result))
