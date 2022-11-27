import re, os


def somma(a, b):
    return a + b


def diff(a, b):
    return a - b


def mul(a, b):
    return a * b


def div(a, b):
    return a // b


def pow(a, b):
    return a ** b


def resolve(line):
    result = []
    operators = {'+': somma, '-': diff, '*': mul, '/': div, ':': div, '^': pow}

    for n in line:
        if n in operators:
            b = result.pop()
            a = result.pop()
            parziale = operators[n](a, b)
            result.append(parziale)  # print(result, line)
        else:
            result.append(int(n))
    #print(result)
    return result[-1]

def adjust(line):  # for '*'
    """
    Funzionale al parsing
    Crea una lista vuota per inserire ogni singolo
    elemento presente nella lista originale 'line'
    Poi:
    '(' controlli l'ultimo valore della nuova lista
    ')' controlli il valore corrente +1 di line
    """
    esp = []
    for i in range(len(line)):
        el = line[i]

        if el in ('(', ')') and 0 < i < len(line) - 1:
            if el == '(' and esp[-1] not in ('+', '*', '/', '-', '^', '(', ')', ':'):
                esp += ['*'] + [el]
            elif el == ')' and line[i + 1] not in ('+', '*', '/', '-', '^', '(', ')', ':'):
                esp += [el] + ['*']
            else:
                esp += [el]
        else:
            esp += [el]
    #print(*esp)
    return esp


def parsing(line):
    """
    Shunting-yard algorithm
    https://en.wikipedia.org/wiki/Shunting-yard_algorithm
    """
    stack, rpn = [], []
    regex = r'\d+|[()+/*-:^]'
    line = re.findall(regex, line)
    line = adjust(line)
    operators = ('+', '-', '^', '*', '/', ':')
    pemdas = {'-': 1, '+': 1, '/': 2, ':': 2, '*': 2, '^': 3, '(': 0, ')': 0}

    while len(line) > 0:
        token = line.pop(0)

        if token == '(':
            stack.append(token)

        elif token == ')':
            while stack[-1] != '(':
                rpn.append(stack.pop())
            stack.pop()

        elif token not in operators:
            rpn.append(token)

        elif token in operators:
            while stack:
                if pemdas[token] <= pemdas[stack[-1]]:
                    rpn.append(stack.pop())
                    continue
                break
            stack.append(token)

    while stack:
        rpn.append(stack.pop())

    #print(' '.join(rpn), stack)
    return rpn

# q = parsing(q)
# resolve(q)