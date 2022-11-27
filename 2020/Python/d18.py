import utilities.polishReverse as polish

file = open('../input/18.txt', 'r').read()

results = []
results2 = []
for expression in file.split('\n'):
    line = polish.parsing(expression, 1, 1)
    line2 = polish.parsing(expression, 2, 1)
    results.append(polish.resolve(line))
    results2.append(polish.resolve(line2))

print(f"Part 1: {sum(results)}")
print(f"Part 2: {sum(results2)}")


