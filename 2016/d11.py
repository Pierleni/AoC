import re
import sys
from copy import deepcopy
from itertools import permutations, combinations, chain
sys.path.append("../")
import libpy.polishReverse as pr

elements = []
elevator = 0
floors = []

file = open("input/d11.txt", 'r').read()
pattern = r"(\w+)(?:-compatible)? (microchip|generator)"
for line in file.split('\n'):
    floor = re.findall(pattern, line)   
    floors.append(set())
    for f in floor:
        if (f[0] not in elements):
            elements.append(f[0])
        floors[-1].add(((1 + elements.index(f[0])) * (1 if f[1] == "generator" else -1)))
num_elements = len(elements)

TOP = len(floors)-1

def getState(floors, elevator):
    positions = [[None] * 2 for _ in range(num_elements)]
    for f, floor in enumerate(floors):
        for el in floor:
            positions[abs(el) - 1][0 if el > 0 else -1] = f 
    return (elevator,) + tuple(tuple(x) for x in sorted(positions))


def isWin(current_floors):
    for f, floor in enumerate(current_floors):
        if f < TOP and floor:
            return False
    return True


def isValid(floor):
    generatorExist = any(x > 0 for x in floor)
    microchipUnplu = any(x < 0 and -x not in floor for x in floor)
    return not (generatorExist and microchipUnplu)


def moves(floors, elevator):
    pairs = tuple(combinations(floors[elevator], 2))
    single = tuple(({x} for x in floors[elevator]))
    for direction in [1, -1]:
        new_elevator = elevator + direction
        if 0 <= new_elevator <= TOP:
            payload = chain(pairs, single) if direction > 0 else chain(single, pairs)
            for pay in payload:
                new_floors = deepcopy(floors)
                new_floors[elevator] -= set(pay)
                if not isValid(new_floors[elevator]):
                    continue
                new_floors[new_elevator] |= set(pay)
                if not isValid(new_floors[new_elevator]):
                    continue
                yield new_floors, new_elevator



def BFS():
    seen = set()
    queue = [(elevator, floors, getState(floors, elevator), 0)]
    while queue:
        current_elevator, current_floors, current_state, current_step = queue.pop(0)
        #print(current_floors)
        if (isWin(current_floors)): return current_step
        if (current_state in seen): continue
        
        seen.add(current_state)
        for new_floors, new_elevator in moves(current_floors, current_elevator):
            new_state = getState(new_floors, new_elevator)
            if (new_state not in seen):
                queue.append((new_elevator, new_floors, new_state, current_step + 1))

ans1 = BFS()
print(ans1)

for el in range(2):
    num_elements += 1
    for j in (1, -1):
        floors[0].add(j * (num_elements))

ans2 = BFS()
print(ans2)