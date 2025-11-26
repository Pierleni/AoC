from collections import defaultdict

data = open("2024/input/d12.txt",'r').read().splitlines()
matrix = [[c for c in line]for line in data]

def nbr(y, x, m):
    dir = [(1,0),(-1,0),(0,1),(0,-1)]
    nwd = []
    for dy, dx in dir:
        ny, nx = dy + y, dx + x
        if 0<=ny<len(m) and 0<=nx<len(m[0]):
            nwd.append((ny, nx))
    return nwd

def bfs(m, p):
    c = m[p[0]][p[1]]
    q = [(p[0],p[1])]
    seen = set()
    result = set()

    while (q):
        y, x = q.pop(0)
        if (y, x) in seen:
            continue
        seen.add((y, x))
        result.add((y, x))

        for (ny, nx) in nbr(y, x, m):
            if m[ny][nx] == c and (ny, nx) not in seen:
                q.append((ny, nx))
    print(c)
    return result

def slv1(matrix):
    ans = 0
    seen = set()
    H = len(matrix)
    W = len(matrix[0])

    for y in range(H):
        for x in range(W):
            if (y, x) not in seen:
                new = bfs(matrix, (y, x))
                for (a, b) in new: seen.add((a, b))

                p = 0
                for (py, px) in new:
                    for (ny, nx) in [(py+1,px),(py-1,px),(py,px+1),(py,px-1)]:
                        if (ny,nx) not in new:
                            print(py, px, ny, nx)
                            p += 1
                print(new,len(new),p)
                ans += len(new) * p
    return ans

def inBound(p, m):
    return 0<=p[0]<len(m) and 0<=p[1]<len(m[0])

def slv2(matrix):
    ans = 0
    seen = set()
    H = len(matrix)
    W = len(matrix[0])

    for y in range(H):
        for x in range(W):
            if (y, x) not in seen:
                new = bfs(matrix, (y, x))
                for (a, b) in new: seen.add((a, b))

                sides = 0
                seen2 = set()
                for (a, b) in new: seen2.add((a, b))
                dir = [(-1,0),(0,1),(1,0),(0,-1)] # n e s w 
                for i in range(len(dir)):
                    d = dir[i]
                    boards = set()
                    for (py, px) in new:
                        ny, nx = py + d[0], px + d[1]
                        if not inBound((ny, nx), matrix) or (ny, nx) not in seen2:
                            boards.add((py, px))
                    
                    sd = set()
                    for (py, px) in boards:
                        if (py, px) not in sd:
                            sides += 1

                            q = [(py, px)]
                            while q:
                                cur = q.pop(0)
                                if cur in sd:
                                    continue
                                sd.add(cur)
                                for (ny, nx) in nbr(cur[0], cur[1], matrix):
                                    if (ny, nx) in boards:
                                        q.append((ny, nx))

                ans += len(new) * sides


    return ans

#print(slv1(matrix))
print(slv2(matrix))