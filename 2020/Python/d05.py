data = open("../input/05.txt", 'r').read()
long = [int(x) for x in range(128)]
short = [int(x) for x in range(8)]

# Parse binary number
def parse(ticket, matrix, n, low):
    s = n
    for c in ticket:
        s //= 2
        if c == low: matrix = matrix[:s]
        else: matrix = matrix[s:]
    return matrix[0]

# Part 1
_ids = list()
for ticket in data.split('\n'):
    column = parse(ticket[:7], long, len(long), 'F')
    row = parse(ticket[7:], short, len(short), 'L')
    _ids.append(column * 8 + row)

print(f"Part 1: {max(_ids)}")

# Part 2
_ids = sorted(_ids)
for i in range(len(_ids)):
    if i + _ids[0] != _ids[i]:
        print(f"Part 2: {_ids[i]-1}")
        break