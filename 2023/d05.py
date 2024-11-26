data = open("input/d05.txt", 'r').read().split("\n\n")
seeds, others = data[0].split(": ")[1:], data[1:]
seeds = [int(x) for x in seeds[0].split()]

def f(seed, oth):
    for line in oth:
        d, s, r = [int(x) for x in line.split()]
        if s <= seed < (s + r):
            return d + (seed - s)
    return seed
    
results = []

for seed in seeds:
    for oth in others:
        oth = oth.split("\n")[1:]
        seed = f(seed, oth)
    results.append(seed)

print(min(results))