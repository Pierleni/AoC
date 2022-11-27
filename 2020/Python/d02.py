file = open("../input/02.txt", 'r').read()
count, valid = 0, 0

for line in file.split('\n'):
    m, M, ref, line = int(line.split()[0].split('-')[0]), \
        int(line.split()[0].split('-')[1]),\
            line.split()[1][-2], line.split()[2]
    
    fact = line.count(ref)
    if fact in range(m, M+1):
        count += 1

    # per verificare se è vera una O l'altra non entrambe
    if (line[m-1] == ref) ^ (line[M-1] == ref):         
        valid += 1

print(f"Part 1: {count}")
print(f"Part 2: {valid}")