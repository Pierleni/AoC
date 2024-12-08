rules = []
rule_map = {}
are_good = []
not_good = []
data = open("input/d5.txt",'r').read()
orders, pages = data.split('\n\n')

    
for order in orders.split('\n'):
    a, b = order.split('|')
    rules.append((int(a), int(b)))

for line in pages.split('\n'):
    line = [int(x) for x in line.split(',')]
    bad = 0
    for i in range(len(line)):
        for j in range(i,len(line)):
            if i == j: continue
            a, b = line[i], line[j]
            if (a, b) not in rules:
                bad += 1
    if (bad == 0): are_good.append(line)
    else: not_good.append(line)

ans = 0
ans2 = 0

for g in are_good:
    ans += g[len(g)//2]
print(f'Part 1: {ans}')

def re_order(line):
    pointer = 0
    while pointer != len(line)-1:
        last_p = pointer
        for j in range(pointer + 1, len(line)):
            if line[pointer] in rule_map.get(line[j], []):
                last_p = j
        if last_p != pointer:
            line.insert(last_p, line.pop(pointer))
        else:
            pointer += 1
for rule in rules:
    f, s = rule
    if f not in rule_map:
        rule_map[f] = []
    rule_map[f].append(s)

for upd in not_good:
    re_order(upd)
    ans2 += int(upd[len(upd)//2])
print(f'Part 2: {ans2}')