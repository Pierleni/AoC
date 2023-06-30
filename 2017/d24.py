from collections import defaultdict
import sys
sys.path.append("../")

def get_value(cur):
    v = 0
    for (a, b) in cur:
        v += a + b
    return v

components = defaultdict(set)
with open("input/d24.txt", 'r') as data:
    for line in data:
        a, b = [int(x) for x in line.split('/')]
        components[a].add(b)
        components[b].add(a)

#print(components)

def bfs():
    que = []
    best, best2, maxL = 0, 0, 0
    seen = set()
    for c in components[0]:
        que.append([(0,c)])

    while (len(que) > 0):
        cur = que.pop(0)
        a, b = cur[-1]
        best = max(best, get_value(cur))
        if (len(cur) >= maxL):
            if len(cur) != maxL:
                maxL = len(cur)
                best2 = 0
            best2 = max(best2, get_value(cur))
        for x in components[b]:
            if (b, x) not in cur and (x, b) not in cur:
                tmp = cur + [(b, x)]
                que.append(tmp)
                    
    return best, best2
print("result:", bfs())