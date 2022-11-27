class Game:

    def __init__(self, pl1, pl2):
        self.pl1 = pl1
        self.pl2 = pl2
        self.score = 0

    def run(self):
        while (len(self.pl1) > 0) and (len(self.pl2) > 0):
            a, b = [self.pl1.pop(0), self.pl2.pop(0)]
            if (a > b): self.pl1 += [a, b]
            else: self.pl2 += [b,a]

        winner = self.pl1 if len(self.pl1) > 0 else self.pl2
        self.scoring(winner, 1)
        
    
    def scoring(self, winner, part):
        self.score = 0        
        index = 0
        for i in range(len(winner), 0, -1):
            self.score += winner[index] * i
            index += 1
        print(f"Part {part}: {self.score}")

            
def run2(pl1, pl2):
    seen1, seen2 = set(), set()
    
    while len(pl1) > 0 and len(pl2) > 0:
        s1, s2 = ','.join([str(c) for c in pl1]), ','.join([str(c) for c in pl2])
        if s1 in seen1 or s2 in seen2:
            return "p1", pl1
        
        seen1.add(s1)
        seen2.add(s2)

        a, b = pl1.pop(0), pl2.pop(0)
        if a <= len(pl1) and b <= len(pl2):
            winner, _ = run2(pl1.copy()[:a], pl2.copy()[:b])
        else:
            if (a > b): winner = "p1"
            else: winner = "p2"

        if winner == "p1":
            pl1 += [a, b]
        else: pl2 += [b, a]

    
    if len(pl1) > 0: return "p1", pl1
    else: return "p2", pl2
    

file = open("../input/d22.txt", 'r').read()
pl1, pl2 = file.split('\n\n')
pl1 = [int(x) for x in pl1.split(':')[1].split('\n')[1:]]
pl2 = [int(x) for x in pl2.split(':')[1].split('\n')[1:]]

game = Game(pl1.copy(), pl2.copy())
game.run()

_, winner = run2(pl1.copy(), pl2.copy())
print(winner)
game.scoring(winner, 2)
