import collections

line = open("input/d09.txt", 'r').read()

players = int(line.split()[0])
balls = int(line.split()[-2])
circle = collections.deque([0])

def solve(maxPlayer, totalMurble, part):
    scores = collections.defaultdict(int)
    for i in range(1, totalMurble + 1):
        if i % 23 == 0:
            circle.rotate(7)
            scores[i % maxPlayer] += i + circle.pop()
            circle.rotate(-1)
        else:
            circle.rotate(-1)
            circle.append(i)

    print(f"Part {part}: {max(scores.values())}")

solve(players, balls, 1)
solve(players, balls * 100, 2)