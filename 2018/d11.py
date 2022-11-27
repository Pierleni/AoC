
serial = int(input("Serial: "))
MAX_SIZE = 300
container = [(0,0), 0, 0]

def setPower(y, x, serial):
    id = x + 10
    power = id * y
    partial = (power + serial) * id
    lighted = (partial // 100) % 10
    result = lighted - 5
    return result

def powerCell(y, x, size):
    result = 0
    options = [(y, x) for y in range(size) for x in range(size)]
    for YY, XX in options:
        result += matrix[y+YY][x+XX]
    return result

matrix = []
for y in range(MAX_SIZE):
    matrix.append([])
    for x in range(MAX_SIZE):
        matrix[-1].append(0)

# Set Power
for y in range(MAX_SIZE):
    for x in range(MAX_SIZE):
        matrix[y][x] = setPower(y+1, x+1, serial)

# Find 3x3 cell
size = 3
for y in range(MAX_SIZE - size):
    for x in range(MAX_SIZE - size):
        power = powerCell(y, x, size)
        
        if (power > container[1]):
            container[0] = (x+1, y+1)
            container[1] = power
            container[2] = size

print(container)
print(f"Part 1: {container[0][0]},{container[0][1]}")

container = [(0,0), 0, 0]
previous = decreasing_count = 0
for size in range(1, 20):
    for y in range(MAX_SIZE - size):
        for x in range(MAX_SIZE - size):
            power = powerCell(y, x, size)
            
            if (power > container[1]):
                container[0] = (x+1, y+1)
                container[1] = power
                container[2] = size

print(container)
print(f"Part 2: {container[0][0]},{container[0][1]},{container[2]}")