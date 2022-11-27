data = open("../input/06.txt", 'r').read()
matrix = []

for groups in data.split('\n\n'):
    matrix.append(groups.replace('\n',''))

result = 0
for word in matrix:
    diz = set()
    for c in word:
        diz.add(c)
    result += len(diz)
print(f"Part 1: {result}")

sums = []
for groups in data.split('\n\n'):
    sl = groups.split('\n')
    sq = set(sl[0])
    for i in range(1, len(sl)):
        sq &= set(sl[i])
    sums.append(len(sq))

print(f"Part 2: {sum(sums)}")