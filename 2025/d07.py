from collections import defaultdict

beans = set()
splits_p1 = 0
start = (0, 0)
with open("./input/d07.txt", 'r') as f:
        data = f.read().splitlines()
        matrix = [[x for x in line] for line in data]
        for d in range(len(matrix[0])):
                if matrix[0][d] == 'S': start = (0, d)
        beans.add(start)
        yy = 0
        while (yy < len(matrix)-1):
                for x in range(len(matrix[yy])):
                        if (yy, x) in beans:
                                ny = yy + 1
                                if matrix[ny][x] == '.':
                                        beans.add((ny, x))
                                elif matrix[ny][x] == '^':
                                        beans.add((ny, x-1))
                                        beans.add((ny, x+1))
                                        splits_p1 += 1
                yy += 1
        print(f"Part 1: {splits_p1}")

ll = len(matrix)-1
dp = defaultdict(int)
dp[start] = 0
def dfs(pos):        
        y, x = pos[0], pos[1]

        while (y < ll) and matrix[y][x] != '^':
                y += 1

        if y == ll:
                return 1
        
        if dp[(y, x)]:
                return dp[(y, x)]
        
        dp[(y, x)] += dfs((y, x + 1))
        dp[(y, x)] += dfs((y, x - 1))

        return dp[(y, x)]
        
print(f"Part 2: {dfs(start)}")