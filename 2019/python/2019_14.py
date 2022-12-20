"""
https://github.com/metalim/metalim.adventofcode.2019.python/blob/master/14_ore_reactions.ipynb
"""

import math

INPUT = '''10 ORE => 10 A
1 ORE => 1 B
7 A, 1 B => 1 C
7 A, 1 C => 1 D
7 A, 1 D => 1 E
7 A, 1 E => 1 FUEL'''

reacts = {}
for line in INPUT.split('\n'):
    l, r = line.split(' => ')
    rq, rn = r.split()
    ls = {}
    for lv in l.split(', '):
        lvq, lvn = lv.split()
        ls[lvn] = int(lvq)
    reacts[rn] = (int(rq), ls)

print(reacts)

def getore(fuel):
    got = {k:0 for k in reacts}
    need = {k:0 for k in reacts}
    got['ORE'] = need['ORE'] = 0
    need['FUEL'] = fuel
    needs = fuel
    while needs>0:
        for c in need:
            if c == 'ORE' or need[c] == 0:
                continue
            add = need[c]-got[c]
            if add>0:
                repeat = math.ceil(add / reacts[c][0])
                got[c] += reacts[c][0] * repeat
                for c2, need2 in reacts[c][1].items():
                    need[c2] += need2 * repeat
                    if c2 != 'ORE': needs += need2 * repeat
            got[c] -= need[c]
            needs -= need[c]
            need[c] = 0

    for k,v in need.items():
        if k!='ORE' and v!=0:
            print('something wrong:', k, v)

    return need['ORE']
print(getore(1))

