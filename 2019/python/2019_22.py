INPUT = '''deal with increment 33
cut 3627
deal with increment 29
cut 1908
deal with increment 32
deal into new stack
cut 8923
deal with increment 19
cut 8560
deal with increment 73
deal into new stack
deal with increment 30
cut 8832
deal with increment 70
deal into new stack
deal with increment 11
cut -4208
deal with increment 47
deal into new stack
deal with increment 65
cut -5055
deal with increment 66
cut 12
deal with increment 24
cut 3069
deal into new stack
cut -1271
deal with increment 50
cut -7214
deal with increment 72
deal into new stack
cut 67
deal with increment 60
cut -7515
deal with increment 68
deal into new stack
cut -4640
deal with increment 68
cut -9047
deal with increment 53
cut 3616
deal with increment 39
deal into new stack
deal with increment 54
cut -6224
deal with increment 42
deal into new stack
deal with increment 35
deal into new stack
cut -4189
deal with increment 68
deal into new stack
cut 425
deal with increment 28
cut -9932
deal with increment 18
deal into new stack
cut 6404
deal with increment 64
cut -724
deal with increment 33
deal into new stack
cut -8328
deal into new stack
cut 4667
deal with increment 37
cut 3303
deal with increment 13
deal into new stack
deal with increment 56
cut 2288
deal with increment 13
cut -266
deal with increment 65
cut 445
deal with increment 33
cut 2652
deal with increment 57
cut -9924
deal with increment 56
cut 9807
deal into new stack
cut -1485
deal with increment 35
cut -4846
deal with increment 5
cut 7747
deal with increment 44
cut -7428
deal with increment 71
deal into new stack
cut -7677
deal with increment 3
cut -5335
deal with increment 31
cut 7778
deal with increment 5
cut 11
deal into new stack
deal with increment 32'''

NumberOfCards = 10007  # 10007
deck = [int(x) for x in range(NumberOfCards)]

def DealNewStack(c):
    return c[::-1]

def cutn(n, c):
    if n > 0:
        cut = c[:n]; return c[n:] + cut
    cut = c[n:]; return cut + c[:n]

def increment(n, cards):
    carte, table, factor = cards, [0] * NumberOfCards, 0
    while len(carte) > 0:
        table[factor] = carte[0]
        factor = (factor + n) % NumberOfCards
        carte = carte[1:]
    return table

shuffle = {'new': DealNewStack, 'increment': increment, 'cut': cutn}

result = deck[:]
for line in INPUT.split('\n'):
    op = line.split()[-2]

    if op == 'cut':
        n = int(line.split()[-1])
        result = shuffle[op](n, result)

    elif op == 'increment':
        n = int(line.split()[3])
        result = shuffle[op](n, result)

    elif op == 'new':
        result = shuffle[op](result)

print(result.index(2019))
