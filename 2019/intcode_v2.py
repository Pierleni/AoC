
class IntCode():
    def __init__(self, line):
        self.line = line + [0 for _ in range(10000)]
        self.ip = 0
        self.input = []
        self.CMD = []
        self.halt = False
        self.output = None
        self.input_process = 0
        self.relative_base = 0
        self.load_game()


    def parse_instruction(self, op):
        modes = str(op)[:-2]
        opcode = str(op)[-1:]
        if len(modes) != 3:
            modes = modes.zfill(3)
        return int(opcode), list(int(x) for x in modes)


    def load_game(self):
        ask = input('Load Game?')
        if ask:
            with open('path.txt', 'r') as f:
                saves = f.readlines()

            for data in saves:
                for letter in data:
                    self.input.append(ord(letter))
        return


    def check_input(self, cmd):
        if cmd in ('quit', 'exit', 'basta', 'stop', 'halt'):
            exit(0)


    def get_input(self, keep_track):
        cmd = input('> ')
        self.check_input(cmd)

        if keep_track:
            with open('path.txt', 'a') as f:
                f.write(cmd + '\n')

        for w in cmd:
            self.input.append(ord(w))
        self.input = self.input + [ord('\n')]
        return


    def run(self, stop4=False, keep_track=False):
        while not self.halt:
            op = self.line[self.ip]

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


            elif op == 3:  # input
                if self.input:
                    self.line[a] = self.input.pop(0)
                    self.ip += 2
                else:
                    self.get_input(keep_track)


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