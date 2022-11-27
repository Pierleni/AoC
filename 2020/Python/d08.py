class Emu:

    def __init__(self):
        self.data = open("../input/08.txt", 'r').read()
        self.instructions = [line for line in self.data.split('\n')]
        self.accumulator = 0
        self.halt = False
        self.index = set()
        self.ip = 0

    def run(self, instructions, debug=False):
        self.ip = 0
        self.accumulator = 0

        while (self.halt != True and self.ip < len(self.instructions)):
            instr = instructions[self.ip]
            op, n = instr.split()[0], int(instr.split()[1])

            if self.ip not in self.index:
                self.index.add(self.ip)
            else:
                self.halt = True

            if op == "acc":
                self.ip += 1
                self.accumulator += n
            elif op == "jmp":
                self.ip += n
            else:
                self.ip += 1

        if self.halt == True:
            if debug == False:
                print(f"Test Failed: Accomulator = {self.accumulator}")
            else:
                self.halt = False
                self.index.clear()
        else:
            print(f"Test passed: Accomulator = {self.accumulator}")

    
    def debug(self):
        for i in range(len(self.instructions)):
            newIstr = [line for line in self.data.split('\n')]

            _n = newIstr[i].split()[1]
            if self.instructions[i].split()[0] == 'jmp':
                newIstr[i] = "nop " + _n
            elif self.instructions[i].split()[0] == 'nop':
                newIstr[i] = "jmp " + _n

            self.run(newIstr, debug=True)


emu = Emu()
emu.run(emu.instructions) # Part 1
emu.debug() # Part 2
