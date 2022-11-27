def addDigit(n):
    return [int(x) for x in str(n)]

limit = 540391
a, b = 0, 1
rec = [3, 7]
while (len(rec) < limit + 10):
    summ = rec[a] + rec[b]
    rec += addDigit(summ)
    newA, newB = rec[a] + 1, rec[b] + 1
    a, b = (a + newA)%len(rec), (b + newB)%len(rec)

print(''.join([str(n) for n in rec[limit:limit+10]]))


#Part2
digits = [int(digit) for digit in str(limit)]

class Scoreboard(list):
    def __init__(self):
        super().__init__([3,7])
        self.elf1 = 0
        self.elf2 = 1
    
    def __next__(self):
        total = self[self.elf1] + self[self.elf2]
        self.extend(divmod(total, 10) if total >= 10 else (total,))
        self.elf1 = (self.elf1 + 1 + self[self.elf1]) % len(self)
        self.elf2 = (self.elf2 + 1 + self[self.elf2]) % len(self)

scores = Scoreboard()
while scores[-len(digits):] != digits and scores[-len(digits)-1:-1] != digits:
    next(scores)

print(len(scores) - len(digits) - (0 if scores[-len(digits):] == digits else 1))