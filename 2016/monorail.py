"""
monorail computer
"""

class monorail(object):
    def __init__(self, input_puzzle):
        self.input_puzzle = input_puzzle
        self.mem = []
        self.outs = []
        self.halt = False
        self.regs = {'a': 0, 'b': 0, 'c': 0, 'd': 0}
        self.ip = 0
        self.opcode = {'cpy': self.cpy,
                       'inc': self.inc,
                       'dec': self.dec,
                       'jnz': self.jnz,
                       'tgl': self.tgl,
                       'out': self.out}

    def parse_input(self):
        for line in self.input_puzzle.split('\n'):
            self.mem.append(line.split())

    def get_val(self, value):
        if value.lstrip('-+').isdigit():
            return int(value)
        return self.regs[value]

    def is_valid(self, line, op):
        """jnz x is a register | cpy y is a register """
        if len(line) > 2 and op == 'cpy':
            if line[2] not in 'abcd':
                self.ip += 1
                return False
        return True

    # OPCODES
    def cpy(self, line):
        x, y = self.get_val(line[1]), line[2]
        self.regs[y] = x
        self.ip += 1
        return

    def inc(self, line):
        x = line[1]
        self.regs[x] += 1
        self.ip += 1
        return

    def dec(self, line):
        x = line[1]
        self.regs[x] -= 1
        self.ip += 1
        return

    def jnz(self, line):
        x, y = self.get_val(line[1]), self.get_val(line[2])
        if x != 0:
            self.ip += y
        else:
            self.ip += 1

    def tgl(self, line):
        """
        [DONE] For one-argument instructions, inc becomes dec, and all other one-argument instructions become inc.
        [DONE] For two-argument instructions, jnz becomes cpy, and all other two-instructions become jnz.
        [DONE] The arguments of a toggled instruction are not affected.
        [DONE] If an attempt is made to toggle an instruction outside the program, nothing happens.
        [DONE] If toggling produces an invalid instruction (like cpy 1 2) and an attempt is later made to execute that instruction, skip it instead.
        [DONE] If tgl toggles itself (for example, if a is 0, tgl a would target itself and become inc a), the resulting instruction is not executed until the next time it is reached.
        """
        x = self.get_val(line[1])
        if self.ip + x > len(self.mem)-1:
            self.ip += 1
            return
        else:
            op = self.mem[self.ip + x][0]
            if op == 'inc':
                self.mem[self.ip + x][0] = 'dec'
            elif op in ('dec', 'tgl'):
                self.mem[self.ip + x][0] = 'inc'
            elif op == 'jnz':
                self.mem[self.ip + x][0] = 'cpy'
            elif op == 'cpy':
                self.mem[self.ip + x][0] = 'jnz'
            self.ip += 1
            return

    def out(self, line):
        x = self.get_val(line[1])
        if len(self.outs) < 8:
            self.outs.append(x)
            self.ip += 1

        else:
            if self.outs == [0,1,0,1,0,1,0,1]:
                exit()
            else:
                self.halt = True
                self.ip += 1


    # EXECUTE PROGRAM
    def run(self, hack=False):
        self.parse_input()
        #print(self.mem)

        while self.ip <= len(self.mem)-1:
            if self.halt: break     # HALT SISTEM

            line = self.mem[self.ip]

            if self.ip == 4 and hack:   # for part 2
                self.regs['a'] = self.regs['b'] * self.regs['d']
                self.regs['c'] = 0
                self.regs['d'] = 0
                self.ip = 10
                continue

            if self.is_valid(line, line[0]):
                self.opcode[line[0]](line)

        print('fine', self.regs)