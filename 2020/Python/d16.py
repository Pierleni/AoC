text = open('../input/16.txt', 'r').read()

types = []
yourTicket = []
nearbyTickets = []

isValid = False
notValid = []

elements = []
for element in text.split('\n\n'):
    elements.append(element)

for line in elements[0].split('\n'):
    number = line.split(': ')[1].split(' or ')
    for r in number:
        types.append((int(r.split('-')[0]), int(r.split('-')[1])))

for line in elements[1].split('\n'):
    if line == 'your ticket:': continue
    yourTicket = [int(x) for x in line.split(',')]

for line in elements[2].split('\n'):
    if line == 'nearby tickets:': continue
    values = [int(x) for x in line.split(',')]
    for v in values:
        nearbyTickets.append(v)


for n in nearbyTickets:
    isValid = False
    for (a, b) in types:
        ranges = range(a, b + 1)
        if n in ranges:
            isValid = True

    if isValid == False:
        notValid.append(n)

print(sum(notValid))