data = open("../input/03.txt", 'r').read()
matrix = [[x for x in line] for line in data.split('\n')]

def traverse(right, down):
    y, x, count = 0, 0, 0
    while y < len(matrix)-1:
        x = (x + right) % len(matrix[0])
        y += down
        if matrix[y][x] == '#':
            count += 1
    return count

print(f"Part 1: {traverse(3, 1)}")

a, b, c, d, e = traverse(1,1), traverse(3,1), traverse(5,1), traverse(7,1), traverse(1,2)
print(f"Part 2: {a*b*c*d*e}")
