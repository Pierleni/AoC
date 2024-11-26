import sys
from math import ceil
from collections import defaultdict


def minimum_ore(reactions, chem='FUEL', units=1, waste=None):

    if waste is None:
        waste = defaultdict(int)
    
    if chem == 'ORE':
        return units

    # Re-use waste chemicals
    reuse = min(units, waste[chem])
    units -= reuse
    waste[chem] -= reuse

    # Work out how many reactions we need to perform.
    produced, inputs = reactions[chem]
    n = ceil(units / produced)

    # Determine the minimum ore required to produce each input.
    ore = 0
    for required, inp in inputs:
        ore += minimum_ore(reactions, inp, n * required, waste)

    # Store waste so it can be re-used
    waste[chem] += n * produced - units

    return ore


def maximum_fuel(reactions):
    target = 1e12
    lower = None
    upper = 1

    # Find upper bound.
    while minimum_ore(reactions, units=upper) < target:
        lower = upper
        upper *= 2

    # Binary search to find maximum fuel produced.
    while lower + 1 < upper:
        mid = (lower + upper) // 2
        ore = minimum_ore(reactions, units=mid)
        if ore > target:
            upper = mid
        elif ore < target:
            lower = mid

    return lower


def parse_chem(line):
    value, name = line.split()
    return (int(value), name)


reactions = dict()
with open ("input/d14.txt", 'r') as data:
    data = data.readlines()
    for d in data:
        i, o = d.split(" => ")
        inputs = []
        for chem in i.split(", "):
            inputs.append(parse_chem(chem))
        o_value, o_name = parse_chem(o)
        reactions[o_name] = (o_value, inputs)
    
print(minimum_ore(reactions))
print(maximum_fuel(reactions))