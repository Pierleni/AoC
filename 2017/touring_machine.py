
class T_Machine():
    def __init__(self, steps):
        self.state = 'A'
        self.tape = [0]
        self.cursor = 0
        self.steps = steps

        self.states = {'A': self.A_State,
                       'B': self.B_State,
                       'C': self.C_State,
                       'D': self.D_State,
                       'E': self.E_State,
                       'F': self.F_State,}


    def move(self, dir):
        if dir == 'right':
            if self.cursor == len(self.tape) - 1:
                self.tape.append(0)
            self.cursor += 1
        else:
            if self.cursor == 0:
                self.tape.insert(0, 0)
            else: self.cursor -= 1
        return self.cursor


    def A_State(self):
        if not self.tape[self.cursor]:
            self.tape[self.cursor] = 1
            self.cursor = self.move('right')
            self.state = 'B'
        else:
            self.tape[self.cursor] = 0
            self.cursor = self.move('left')
            self.state = 'C'


    def B_State(self):
        if not self.tape[self.cursor]:
            self.tape[self.cursor] = 1
            self.cursor = self.move('left')
            self.state = 'A'
        else:
            self.cursor = self.move('right')
            self.state = 'C'


    def C_State(self):
        if not self.tape[self.cursor]:
            self.tape[self.cursor] = 1
            self.cursor = self.move('right')
            self.state = 'A'
        else:
            self.tape[self.cursor] = 0
            self.cursor = self.move('left')
            self.state = 'D'


    def D_State(self):
        if not self.tape[self.cursor]:
            self.tape[self.cursor] = 1
            self.cursor = self.move('left')
            self.state = 'E'
        else:
            self.cursor = self.move('left')
            self.state = 'C'


    def E_State(self):
        if not self.tape[self.cursor]:
            self.tape[self.cursor] = 1
            self.cursor = self.move('right')
            self.state = 'F'
        else:
            self.cursor = self.move('right')
            self.state = 'A'


    def F_State(self):
        if not self.tape[self.cursor]:
            self.tape[self.cursor] = 1
            self.cursor = self.move('right')
            self.state = 'A'
        else:
            self.cursor = self.move('right')
            self.state = 'E'


    def run(self):
        while self.steps > 0:
            # print(self.steps, \
            #       self.state, \
            #       self.tape, \
            #       'cursor', \
            #       self.cursor)
            self.states[self.state]()   # Switch operator
            self.steps -= 1
            #input()                     # pause

        print(f"\nChecksum: {sum(self.tape)}")