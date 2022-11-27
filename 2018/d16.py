import collections

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
        self.registers = [0] * 4
        self.opcodes = dict()

    
    def resetRegisters(self):
        self.registers = [0] * 4

    
    ## Addiction
    def addi(self, before, A, B, C):
        """addi (add immediate) 
        stores into register C the result of adding register A and value B."""
        self.registers = before
        self.registers[C] = self.registers[A] + B

    
    def addr(self, before, A, B, C):
        """addr (add register) 
        stores into register C the result of adding register A and register B."""
        self.registers = before
        self.registers[C] = self.registers[A] + self.registers[B]


    ## Multiplication
    def muli(self, before, A, B, C):
        """muli (multiply immediate) 
        stores into register C the result of multiplying register A and value B."""
        self.registers = before
        self.registers[C] = self.registers[A] * B

    
    def mulr(self, before, A, B, C):
        """mulr (multiply register) 
        stores into register C the result of multiplying register A and register B."""
        self.registers = before
        self.registers[C] = self.registers[A] * self.registers[B]

    
    ## Bitwise AND
    def bani(self, before, A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise AND of register A and value B."""
        self.registers = before
        self.registers[C] = self.registers[A] & B

    def banr(self, before, A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise AND of register A and register B."""
        self.registers = before
        self.registers[C] = self.registers[A] & self.registers[B]

    
    ## Bitwise OR
    def bori(self, before, A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise OR of register A and value B."""
        self.registers = before
        self.registers[C] = self.registers[A] | B
    
    def borr(self, before, A, B, C):
        """bani (bitwise AND immediate) 
        stores into register C the result of the bitwise OR of register A and register B."""
        self.registers = before
        self.registers[C] = self.registers[A] | self.registers[B]

    
    ## Assigment
    def seti(self, before, A, B, C):
        """seti (set immediate) 
        stores value A into register C. (Input B is ignored.)"""
        self.registers = before
        self.registers[C] = A

    
    def setr(self, before, A, B, C):
        """setr (set register) 
        copies the contents of register A into register C. (Input B is ignored.)"""
        self.registers = before
        self.registers[C] = self.registers[A]


    ## Greather-then Testing
    def gtir(self, before, A, B, C):
        """gtir (greater-than immediate/register) 
        sets register C to 1 if value A is greater than register B. 
        Otherwise, register C is set to 0."""
        self.registers = before
        if A > self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0

    
    def gtri(self, before, A, B, C):
        """gtri (greater-than register/immediate) 
        sets register C to 1 if register A is greater than value B. 
        Otherwise, register C is set to 0."""
        self.registers = before
        if self.registers[A] > B: self.registers[C] = 1
        else: self.registers[C] = 0


    def gtrr(self, before, A, B, C):
        """gtrr (greater-than register/register) 
        sets register C to 1 if register A is greater than register B. 
        Otherwise, register C is set to 0."""
        self.registers = before
        if self.registers[A] > self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0


    ## Equality Testing
    def eqir(self, before, A, B, C):
        """eqir (equal immediate/register) 
        sets register C to 1 if value A is equal to register B. 
        Otherwise, register C is set to 0."""
        self.registers = before
        if A == self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0

    
    def eqri(self, before, A, B, C):
        """eqri (equal register/immediate) 
        sets register C to 1 if register A is equal to value B. 
        Otherwise, register C is set to 0."""
        self.registers = before
        if self.registers[A] == B: self.registers[C] = 1
        else: self.registers[C] = 0


    def eqrr(self, before, A, B, C):
        """eqrr (equal register/register) 
        sets register C to 1 if register A is equal to register B. 
        Otherwise, register C is set to 0."""
        self.registers = before
        if self.registers[A] == self.registers[B]: self.registers[C] = 1
        else: self.registers[C] = 0


    ## Self Run
    

dv = Device()
result1 = 0

data = open('input\d16.txt', 'r').read()
part1, part2 = data.split("\n\n\n\n")

combinations = collections.defaultdict(set)

for instr in part1.split("\n\n"):
    bef, op, aft = instr.split("\n")
    before = eval(bef[8:])
    after = eval(aft[8:])
    op, a, b, c = [int(n) for n in op.split()]
    
    count = 0
    for operation in dv.operators:
        operation(list(before), a, b, c)
        if dv.registers == list(after):
            count += 1

            # collect information for part 2
            combinations[operation].add(op)     # NB not operation.__name__ but the function itself

    if count >= 3: 
        result1 += 1

print(f"Part 1: {result1}")                   # 547


# Part 2
all_operations = 0
while all_operations < len(dv.operators):
    
    for instr, listOfCombinations in combinations.items():
        if len(listOfCombinations) == 1:        # if just one element left
            found = listOfCombinations.pop()    # take it
            dv.opcodes[found] = instr           # and put in dv.opcodes dict
            all_operations += 1

            del combinations[instr]             # erase that empty instr

            for k, v in combinations.items():   
                if found in v:                  # check and erase if that number is
                    v.remove(found)             # presents in others number list (to reduce them)   
            break

dv.resetRegisters()                             # clean registers
for line in part2.split('\n'):
    op, a, b, c = [int(x) for x in line.split()]
    dv.opcodes[op](list(dv.registers), a,b,c)   # for every op, it's now execute
                                                # the corrispondent self.function(befor, a, b, c)
    #print(op, dv.opcodes[op].__name__, a,b,c, dv.registers); input()                                            
print(f"Part 2: {dv.registers[0]}")             # 582