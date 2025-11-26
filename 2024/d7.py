from itertools import product, permutations

def add(a, b):
    return a + b

def mul(a, b):
    return a * b

# for part 2
def isValid(n, l):
    if (len(l) == 1):
        return n == l[0]
    if isValid(n, [l[0] + l[1]] + l[2:]):
        return True
    if isValid(n, [l[0] * l[1]] + l[2:]):
        return True
    if isValid(n, [int(str(l[0])+str(l[1]))] + l[2:]):
        return True
    return False

ans1 = 0
ans2 = 0
operands = ['+','*']
with open("2024/input/d7.txt",'r') as f:
    lines = f.read().splitlines()
    for line in lines:
        result, numbers = line.split(':')
        result = int(result)
        numbers = [int(x) for x in numbers.split()]
        
        rep = len(numbers)-1
        combs = list(product(operands, repeat=rep))
        for comb in combs:
            stack = [op for op in comb]

            res = int(numbers[0])

            for i in range(1, len(numbers)):
                op = stack.pop(0)
                res = add(res,numbers[i]) if op == '+' else mul(res,numbers[i])
            if res == result:
                ans1 += result
                break

        # part 2
        if isValid(result, numbers):
            ans2 += result

print(ans1)
print(ans2)
