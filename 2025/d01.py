dial = []
part1 = part2 = 0

for i in range(100):
        dial.append(i)

ptr = ptr2 = 50
with open("./input/d01.txt", 'r') as f:
        lines = f.read().splitlines()
        for line in lines:
                #part1
                dist = int(line[1:]) * (1 if line[0] == "R" else -1)
                ptr  = (ptr + dist) % 100
                if (dial[ptr] == 0): part1 += 1
                #part2
                dir = 1 if line[0] == "R" else -1
                for _ in range(abs(dist)):
                        ptr2 += dir
                        ptr2 %= 100
                        if (dial[ptr2] == 0): part2 += 1
print(f"part 1: {part1}")
print(f"part 2: {part2}")