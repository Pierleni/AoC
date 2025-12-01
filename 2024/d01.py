left, right = [], []
with open("./input/d1.txt", 'r') as f:
    for line in f.read().splitlines():
        a, b = line.split()
        left.append(int(a))
        right.append(int(b))

sortLeft = sorted(left)
sortRight = sorted(right)

ans = 0
for i in range(len(sortLeft)):
    b = min(sortRight[i],sortLeft[i])
    a = max(sortRight[i], sortLeft[i])
    ans += a - b
    
print(f'Part 1: {ans}') # 2430334

ans2 = 0
for n in left:
    ans2 +=  n * right.count(n)
print(f'Part 2: {ans2}') # 28786472