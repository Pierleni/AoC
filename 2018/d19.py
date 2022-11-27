import collections
import time

class Device:

    def __init__(self):
        self.operators = [
            self.addi, self.addr,
            self.muli, self.mulr,
            self.bani, self.banr, 
            self.bori, self.borr,
            self.seti, self.setr,
            self.gtir, self.gtri, self.gtrr,
            self.eqir, self.eqri, self.eqrr
        ]
        self.registers = [0] * 6
        self.opstr = ["addi", "addr",
            "muli", "mulr",
            "bani", "banr", 
            "bori", "borr",
            "seti", "setr",
            "gtir", "gtri", "gtrr",
            "eqir", "eqri", "eqrr"]
        self.instructions = list()
        self.ip = 0

        self.opcodes = {x : y for (x, y) in zip(self.opstr, self.operators)}

    
    def resetRegisters(self):
        self.registers = [0] * 6

    
    ## Addiction
    def addi(self,A, B, C):
        """addi (add immediate) 
        stores into register C the result of adding register A and value B."""
        self.registers[C] = self.registers[A] + B

    
    def addr(self,A, B, C):
        """addr (add register) 
        stores into register C the result of adding register A and register B."""
        self.registers[C] = self.registers[A] + self.registers[B]


    ## Multiplication
    def muli(self,A, B, C):
        """muli (multiply immediate) 
        stores into register C the result of multiplying register A and value B."""
        self.registers[C] = self.registers[A] * B

    
    def mulr(self,A, B, C):
        """mulr (multiply register) 
        stores into register C the result of multiplying register A and register B."""
        self.registers[C] = self.registers[A] * self.registers[B]

    
    ## Bitwise AND
    def bani(self,A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise AND of register A and value B."""
        self.registers[C] = self.registers[A] & B

    def banr(self,A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise AND of register A and register B."""
        self.registers[C] = self.registers[A] & self.registers[B]

    
    ## Bitwise OR
    def bori(self,A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise OR of register A and value B."""
        self.registers[C] = self.registers[A] | B
    
    def borr(self,A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise OR of register A and register B."""
        self.registers[C] = self.registers[A] | self.registers[B]

    
    ## Assigment
    def seti(self,A, B, C):
        """seti (set immediate) 
        stores value A into register C. (Input B is ignored.)"""
        self.registers[C] = A

    
    def setr(self,A, B, C):
        """setr (set register) 
        copies the contents of register A into register C. (Input B is ignored.)"""
        self.registers[C] = self.registers[A]


    ## Greather-then Testing
    def gtir(self,A, B, C):
        """gtir (greater-than immediate/register) 
        sets register C to 1 if value A is greater than register B. 
        Otherwise, register C is set to 0."""
        if A > self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0

    
    def gtri(self,A, B, C):
        """gtri (greater-than register/immediate) 
        sets register C to 1 if register A is greater than value B. 
        Otherwise, register C is set to 0."""
        if self.registers[A] > B: self.registers[C] = 1
        else: self.registers[C] = 0


    def gtrr(self,A, B, C):
        """gtrr (greater-than register/register) 
        sets register C to 1 if register A is greater than register B. 
        Otherwise, register C is set to 0."""
        if self.registers[A] > self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0


    ## Equality Testing
    def eqir(self,A, B, C):
        """eqir (equal immediate/register) 
        sets register C to 1 if value A is equal to register B. 
        Otherwise, register C is set to 0."""
        if A == self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0

    
    def eqri(self,A, B, C):
        """eqri (equal register/immediate) 
        sets register C to 1 if register A is equal to value B. 
        Otherwise, register C is set to 0."""
        if self.registers[A] == B: self.registers[C] = 1
        else: self.registers[C] = 0


    def eqrr(self, A, B, C):
        """eqrr (equal register/register) 
        sets register C to 1 if register A is equal to register B. 
        Otherwise, register C is set to 0."""
        if self.registers[A] == self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0

    def Run(self):
        while self.registers[self.ip] < len(self.instructions):
            o = self.instructions[self.registers[self.ip]]
            op, a, b, c = o.split()[0], int(o.split()[1]), int(o.split()[2]), int(o.split()[3]),
            ##print(self.ip)
            ##print(op, a, b, c)
            self.opcodes[op](a, b, c)
            ##print(f"[{self.registers[0]}, {self.registers[1]}, {self.registers[2]},{self.registers[3]},{self.registers[4]},{self.registers[5]}]")
            self.registers[self.ip] += 1
        print(self.registers[0])

start_time = time.time()
dv = Device()
data = open('input\d19.txt', 'r').read()
content = data.split("\n")
dv.ip = int(content[0].split()[1])
dv.instructions = content[1:]

dv.Run()
print("Time: ", time.time() - start_time)