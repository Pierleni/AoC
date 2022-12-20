coor = '''<x=-1, y=-4, z=0>
<x=4, y=7, z=-1>
<x=-14, y=-10, z=9>
<x=1, y=2, z=17>'''

"""
        (a * b)         Formula per il Minimo Comune Multiplo.
lcm = ------------      Poichè i 3 assi si muovono con dei cilci indipendenti
       gcd(a, b)        una volta trovato il ciclo ricorsivo dei 3 assi, calcoli il loro lcm
"""

import math


class Planets(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.vx = 0
        self.vy = 0
        self.vz = 0


def calc(a, b):
    return 1 if a < b else 0 if a == b else -1


def lcm(a, b):
    return (a * b) // math.gcd(a, b)


matrix = []
for line in coor.split('\n'):
    line = line.split('<')[1].split('>')[0].split(', ')
    x, y, z = line[0][2:], line[1][2:], line[2][2:]
    matrix.append([int(x), int(y), int(z)])

pl = [Planets(matrix[i][0], matrix[i][1], matrix[i][2]) for i in range(4)]

calculation = True
x_axs, y_axs, z_axs = set(), set(), set()

while calculation:
    for i in range(4):
        for j in range(4):
            if i == j:
                continue
            pl[i].vx += calc(pl[i].x, pl[j].x)
            pl[i].vy += calc(pl[i].y, pl[j].y)
            pl[i].vz += calc(pl[i].z, pl[j].z)

    for i in range(4):
        pl[i].x += pl[i].vx
        pl[i].y += pl[i].vy
        pl[i].z += pl[i].vz

    x_stat = tuple((p.x, p.vx) for p in pl)  # separo l'asse x e vx di ogni pianeta
    y_stat = tuple((p.y, p.vy) for p in pl)  # separo l'asse y e vy di ogni pianeta
    z_stat = tuple((p.z, p.vz) for p in pl)  # separo l'asse z e vz di ogni pianeta

    if x_stat in x_axs and y_stat in y_axs and z_stat in z_axs:  # finchè non si ripetono aggiungo coordinate
        break
    else:
        x_axs.add(x_stat)
        y_axs.add(y_stat)
        z_axs.add(z_stat)

a, b, c = len(x_axs), len(y_axs), len(z_axs)  # la loro len() sono gli step totali prima che il ciclo si ripeta
print(f"a: {a} \nb: {b} \nc: {c}")
print(lcm(a, lcm(b, c)))  # calcolo il minimo comune multiplo degli step dei 3 assi

################# Bravo ma toooooo slow :'( ##########################
#
#     pos = (pl[0].x, pl[0].y, pl[0].z, pl[0].vx, pl[0].vy, pl[0].vz,
#            pl[1].x, pl[1].y, pl[1].z, pl[1].vx, pl[1].vy, pl[1].vz,
#            pl[2].x, pl[2].y, pl[2].z, pl[2].vx, pl[2].vy, pl[2].vz,
#            pl[3].x, pl[3].y, pl[3].z, pl[3].vx, pl[3].vy, pl[3].vz,)
#
#     if pos not in position:
#         position.append(pos)
#     else: calculation = False
#
# print(count)
