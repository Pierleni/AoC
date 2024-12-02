with open("2024/input/d2.txt", 'r') as f:
    matrix = [[int(x) for x in line.split()] for line in f.read().splitlines()]

def is_safe(line):
    ans = 0
    if (line[0] < line[-1]): # increasing
        for i in range(len(line)-1):
            if (3 >= line[i+1] - line[i] and line[i+1] != line[i] and line[i+1] > line[i]):
                ans += 1
    
    else: # decreasing
        for i in range(len(line)-1):
            if (3 >= line[i] - line[i+1] and line[i+1] != line[i] and line[i+1] < line[i]):
                ans += 1

    return True if ans == len(line)-1 else False

def part2(line):
    if is_safe(line):
        return True
    for i in range(len(line)):
        nwLine = line[:i] + line[i+1:]
        if is_safe(nwLine):
            return True
    return False

print("Part 1:",sum([1 for line in matrix if is_safe(line)])) #402
print("Part 2:",sum([1 for line in matrix if part2(line)])) #455