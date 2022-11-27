import itertools

file = open("../input/09.txt", 'r').read()
data = [int(x) for x in file.split('\n')]
limit, target = 25, 0
start, end = 0, limit

# Part 1
while (start < len(data) - limit):
    window = data[start : end]
    target = data[end]

    combination = itertools.combinations(window, 2)
    checkSum = []
    for comb in combination:
        checkSum.append(sum(comb))
    if target in checkSum:
        start += 1
        end += 1
    else:
        print(f"Part 1: {target}")
        break

# Part 2
maxRange = data.index(target)
newList = data[:maxRange]
start, end = 0, 2
while True:
    while start < maxRange:
        section = newList[start : start + end]
        if sum(section) == target:
            section = sorted(section)
            print(f"Part 2: {section[0] + section[-1]}")
            exit(0)

        start += 1

    start = 0
    end += 1