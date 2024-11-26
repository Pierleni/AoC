
vertical = 0
horizont = 0

data = open("input/d13.txt",'r').read().split("\n\n")

for part2 in [False,True]:
    ans = 0
    for graph in data:
        graph = graph.split("\n")

        matrix = []
        for line in graph:
            matrix.append([])
            for x in line:
                matrix[-1].append(x)

        Y, X = len(matrix), len(matrix[0])
        
        # horizontal check
        for x in range(X-1):
            ok = 0
            for xx in range(X):
                left = x - xx
                right = x + 1 + xx
                if 0 <= left < right < X:
                    for y in range(Y):
                        if matrix[y][left] != matrix[y][right]:
                            ok += 1
            if ok == (1 if part2 else 0):
                ans += x+1

        # vertical check (x 100)
        for y in range(Y-1):
            ok = 0
            for yy in range(Y):
                up = y - yy
                down = y+1+yy
                if 0 <= up < down < Y:
                    for x in range(X):
                        if matrix[up][x] != matrix[down][x]:
                            ok += 1
            if ok == (1 if part2 else 0):
                ans += 100 * (y+1)
        
    print(ans)