class Iterator:
    
    def __init__(self, max=0):
        self.max = max

    def __iter__(self):
        self.i = 0
        return self

    def __next__(self):
        print(f"Ho appena imparato a contare fino a {self.i}")
        self.i += 1

t = Iterator(18)
i = iter(t)

for _ in range(28):
    next(i)
