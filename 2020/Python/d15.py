data = [0,12,6,13,20,1,17]

last = {}
for i in range(1, len(data) + 1):
    last[data[i-1]] = i


turn = len(data) - 1
while turn <= 2018:
    if data[turn] not in data[:-1]:     # check ignoring last element
        data.append(0)                  # add 0 if new
        last[data[turn]] = turn + 1     # update dictionary position numbers
    else:
        if data[turn] == data[turn-1]:
            data.append(1)
        else:
            for k, v in last.items():
                if k == data[turn]:
                    index = v
                    break
            data.append(turn+1 - index)

        last[data[turn]] = turn + 1

    turn += 1
print(f"Part 1: {data[-1]}")

#        P A R T   T W O        #

data = [0,12,6,13,20,1,17]
turn = 1
ult = {}
penul = {}

# seed the tables
for i in range(len(data)):
    ult[data[i]] = turn
    penul[data[i]] = 0
    turn += 1

target = data[-1]
while turn <= 30000000:
    if penul[target] == 0:  # first time spoken
        target = 0
        penul[target] = ult[target]
        ult[target] = turn
    else:
        num = ult[target] - penul[target]
        target = num
        if target not in ult.keys():
            penul[target] = 0
            ult[target] = turn
        else:
            penul[target] = ult[target]
            ult[target] = turn
    turn += 1
print(f"Part 2: {target}")