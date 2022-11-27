data = open("./input/d7.txt", "r").read()

data = data.replace("[", " ").replace("]", " ")
result = []

def checkPal(line):
    i=0
    while (i < len(line)-2):
        a = line[i:i+2]
        b = line[i+2:i+4]
        if (a == b[::-1]): print(a, b[::-1]); return True
        i += 1
    return False


def oneChar(line):
    chars = set(line)
    if len(chars) > 1: return False
    return True


for line in data.splitlines():
    first, second, third = line.split()
    print(first, second, third)
    if (oneChar(first) or oneChar(second) or oneChar(third)): continue
    if (checkPal(second)): continue
    if (checkPal(first) or checkPal(third)):
        result.append(line)

print(len(result))