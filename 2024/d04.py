data = open("2024/input/d4.txt", 'r').read().splitlines()
matrix = [[c for c in line] for line in data]

xmas = "XMAS"

result = 0
resul2 = 0
#horizontal():
for y in range(len(matrix)):
    for x in range(len(matrix[y])-3):
        tmp = ''.join(matrix[y][x:x+4])
        rtmp = ''.join(tmp[::-1])
        if (tmp == xmas or rtmp == xmas):
            result += 1

#vertical():
for y in range(len(matrix)-3):
    for x in range(len(matrix[y])):
        tmp = ''
        for yy in range(4):
            tmp += matrix[y+yy][x]
        rtmp = ''.join(tmp[::-1])
        if (tmp == xmas or rtmp == xmas):
            result += 1

#diagonalR():
for y in range(len(matrix)-3):
    for x in range(len(matrix[y])-3):
        tmp = ''
        for k in range(4):
            tmp += matrix[y+k][x+k]
        rtmp = ''.join(tmp[::-1])
        if (tmp == xmas or rtmp == xmas):
            result += 1

#diagonalL():
for y in range(len(matrix)-3):
    for x in range(3,len(matrix[y])):
        tmp = ''
        for k in range(4):
            tmp += matrix[y+k][x-k]
        rtmp = ''.join(tmp[::-1])
        if (tmp == xmas or rtmp == xmas):
            result += 1

print(f'Part 1: {result}')

#x_mas():
for y in range(1,len(matrix)-1):
    for x in range(1,len(matrix[0])-1):
        d1 = matrix[y-1][x-1]+matrix[y][x]+matrix[y+1][x+1]
        d2 = matrix[y+1][x-1]+matrix[y][x]+matrix[y-1][x+1]
        if (d1 == "MAS" or d1 == "SAM") and (d2 == "MAS" or d2 == "SAM"):
            resul2 += 1

print(f'Part 1: {resul2}')