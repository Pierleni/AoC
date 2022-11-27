"""
https://github.com/mebeim/aoc/blob/master/2019/README.md#day-16---flawed-frequency-transmission    # guarda bene
"""

class IntCode():
    def __init__(self, line):
        self.line = line + [0 for _ in range(10000)]
        self.ip = 0
        self.halt = False
        self.output = None
        self.input_process = 0
        self.relative_base = 0

    def parse_instruction(self, op):
        modes = str(op)[:-2]
        opcode = str(op)[-1:]
        if len(modes) != 3:
            modes = modes.zfill(3)
        return int(opcode), list(int(x) for x in modes)

    def run(self, id, stop4=False, i_rep=False, idle=False, wait=False):
        while not self.halt:
            op = self.line[self.ip]
            #print(self.ip, op, id)

            if op == 99:
                self.halt = True
                continue  # per interrompere

            if op > 100:
                op, modes = self.parse_instruction(op)
            else:
                modes = [0, 0, 0]

            a = self.ip + 1 if modes[2] == 1 else (self.relative_base + self.line[self.ip + 1]) if modes[2] == 2 else self.line[self.ip + 1]
            b = self.ip + 2 if modes[1] == 1 else (self.relative_base + self.line[self.ip + 2]) if modes[1] == 2 else self.line[self.ip + 2]
            c = self.ip + 3 if modes[0] == 1 else (self.relative_base + self.line[self.ip + 3]) if modes[0] == 2 else self.line[self.ip + 3]

            if op == 1:
                self.line[c] = self.line[a] + self.line[b]
                self.ip += 4

            elif op == 2:
                self.line[c] = self.line[a] * self.line[b]
                self.ip += 4

            elif op == 3:                       # input
                #1
                if i_rep:                       # recursive take 2nd element (day 7)
                    if self.input_process == 0:
                        self.line[a] = id[0]
                        self.input_process += 1
                    else: self.line[a] = id[self.input_process]

                #2
                if wait and not id:             # for text adventure day 25
                    self.halt = True

                #3
                else:
                    self.line[a] = id.pop(0)
                    self.ip += 2
                    if idle:                    # for day 23
                        self.output = None
                        break                   # to interrupt

            elif op == 4:
                self.output = self.line[a]
                self.ip += 2
                if stop4 is True:
                    return self.output  # day 7


            elif op == 5:
                if self.line[a] != 0:
                    self.ip = self.line[b]
                else:
                    self.ip += 3

            elif op == 6:
                if self.line[a] == 0:
                    self.ip = self.line[b]
                else:
                    self.ip += 3

            elif op == 7:
                if self.line[a] < self.line[b]:
                    self.line[c] = 1
                else:
                    self.line[c] = 0
                self.ip += 4

            elif op == 8:
                if self.line[a] == self.line[b]:
                    self.line[c] = 1
                else:
                    self.line[c] = 0
                self.ip += 4

            elif op == 9:
                self.relative_base += self.line[a]
                self.ip += 2

        return self.output