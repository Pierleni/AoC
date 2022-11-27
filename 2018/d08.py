file = open('input/d08.txt', 'r').read()
sequence = [int(n) for n in file.split(' ')]

def parse(data):
    nodes, metas = data[:2]
    remeaning = data[2:]
    totals = 0
    scores = []

    for _ in range(nodes):
        total, remeaning, root = parse(remeaning)
        totals += total
        scores.append(root)

    totals += sum(remeaning[:metas])

    if nodes == 0:
        return totals, remeaning[metas:], sum(remeaning[:metas])
    
    return totals, \
    remeaning[metas:], \
    sum(scores[ k - 1] for k in remeaning[:metas] if k > 0 and k <= len(scores))


total, sequence, root = parse(sequence)
print(f"Part 1: {total}")
print(f"Part 2: {root}")