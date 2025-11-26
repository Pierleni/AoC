from collections import deque

data = open("2024/input/d10.txt",'r').read()
matrix = [[c for c in line] for line in data.splitlines()]
starts = []

def inBound(matrix, p):
    return 0<=p[0]<len(matrix) and 0<=p[1]<len(matrix[0])

def bfs(matrix, start, part2):
    q = deque()
    visited = set()
    
    q.append(start)
    visited.add(start)
    
    score = 0
    
    while q:
        curr = q.popleft()
        curr_n = matrix[curr[0]][curr[1]]
        
        if curr_n == '9':
            score += 1
        
        for (dy, dx) in [(1,0),(-1,0),(0,1),(0,-1)]:
            ny = curr[0] + dy
            nx = curr[1] + dx
            
            if not inBound(matrix, (ny, nx)): continue
            if not part2 and (ny, nx) in visited: continue # for part 1
            if int(curr_n) == int(matrix[ny][nx])-1:
                new_pos = (ny, nx)
                q.append(new_pos)
                visited.add(new_pos)
    return score

for y in range(len(matrix)):
    for x in range(len(matrix[y])):
        if matrix[y][x] == '0':
            starts.append((y, x))

for part2 in [False, True]:
    ans = 0
    for start in starts:
        ans += bfs(matrix, start, part2)
    print(ans)