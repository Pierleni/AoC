import hashlib
import collections

INPUT = '''pslxynzg'''
goal = 3+3j


def solve():
    solutions = []
    que = collections.deque([(0+0j, '')])

    while que:
        pos, path = que.popleft()

        if pos == goal:
            solutions.append(path)
            continue

        u, d, l, r = hashlib.md5((INPUT+path).encode()).hexdigest()[:4]

        if u > 'a' and pos.imag > 0:            # pos.imag 2j di 1+2j
            que.append((pos-1j, path+'U'))
        if d > 'a'and pos.imag < 3:
            que.append((pos+1j, path+'D'))      # pos.real 1 di 1+2j
        if l > 'a' and pos.real > 0:
            que.append((pos-1, path+'L'))
        if r > 'a' and pos.real < 3:
            que.append((pos+1, path+'R'))

    return solutions[0], len(solutions[-1])



part1, part2 = solve()
print(part1, part2)
