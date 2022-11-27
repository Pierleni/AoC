from collections import defaultdict

INPUT = '''24/14
30/24
29/44
47/37
6/14
20/37
14/45
5/5
26/44
2/31
19/40
47/11
0/45
36/31
3/32
30/35
32/41
39/30
46/50
33/33
0/39
44/30
49/4
41/50
50/36
5/31
49/41
20/24
38/23
4/30
40/44
44/5
0/43
38/20
20/16
34/38
5/37
40/24
22/17
17/3
9/11
41/35
42/7
22/48
47/45
6/28
23/40
15/15
29/12
45/11
21/31
27/8
18/44
2/17
46/17
29/29
45/50'''

# start, bridges = [], []
# for line in INPUT.split('\n'):
#     couple = line.split('/')
#     a, b = int(couple[0]), int(couple[1])
#     if a == 0: start.append([a, b])
#     else: bridges.append(sorted((a, b)))
#
# print(bridges)
# print(start)
#
# solution = []
# seen = []
# que = []
#
#
#
# for el in start:
#     solution.append(el)
#     que.append(el)
#     while que:
#         rif = que.pop(0)
#         for couple in bridges:
#             if rif[-1] == couple[0] or \
#                 rif[-1] == couple[1] and rif[-1] == couple[0]+1:
#                 if couple != rif[-2:] :
#                     solution.append(rif + couple)
#                     que.append(rif + couple)
#                     print('SOLUT', solution)
#                     #print('QUE', que)
#                     #input()
#
# solution = sorted(solution)
# for r in solution:
#     print(r)
# print(max(sum(r) for r in solution))


def gen_bridges(library, bridge=None):
    l, s, components, a = bridge or (0, 0, set(), 0)
    for b in library[a]:
        next = (a, b) if a <= b else (b, a)
        if next not in components:
            new = l+1, s+a+b, (components | {next}), b
            yield new; yield from gen_bridges(library, new)

def solve(input):
    library = defaultdict(set)
    for l in input.strip().splitlines():
        a, b = [int(x) for x in l.split('/')]
        library[a].add(b); library[b].add(a)
    return [b[:2] for b in gen_bridges(library)]

bridges = solve(INPUT)  # A list of (length, strength) tuples
part1 = sorted(bridges, key=lambda x: x[1])[-1][1]  # Sort by strength only
part2 = sorted(bridges)[-1][1]  # Sort by length, then by strength

print(part1)
print(part2)