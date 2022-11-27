import itertools

data = open('../input/14.txt', 'r').read().splitlines()
mem = dict()


def showResoult(mem):
    count = 0
    for k, v in mem.items():
        count += v
    return count


def maskeration(string, mask):
    binary = list(string)
    for k, v in mask.items():
        binary[k] = v
    return ''.join(binary)


def new_maskeration(string, mask, numberOfX):
    binary = list(string)
    for k, v in mask.items():
        binary[k] = v

    all_possible_addresses = []
    new_binary = binary.copy()
    combination = itertools.product(['0', '1'], repeat=numberOfX)
    for comb in combination:
        x = 0
        for i in range(len(binary)):
            if binary[i] == 'X':
                new_binary[i] = comb[x]
                x += 1
        all_possible_addresses.append(int(''.join(new_binary), 2))
    return all_possible_addresses

#####################################
#           V. - 1 . 0              #
#####################################

for line in data:
    # Parsing
    if line[:3] == 'mas':
        mask = dict()
        decode = list(line[7:])
        numberOfX = decode.count('X')
        for i in range(len(decode)):
            if decode[i] != 'X':
                mask[i] = decode[i]
        continue  # break and start over with mem address
    else:
        ip, value = int(line.split('] = ')[0][4:]), int(line.split('] = ')[1])

    # Convert value to bin and put it in mem[ip]
    value = bin(value)[2:].zfill(36)
    binary = maskeration(value, mask)
    mem[ip] = int(binary, 2)

print(f"Part 1: {showResoult(mem)}")  # 15018100062885

#####################################
#           V. - 2 . 0              #
#####################################

mem = dict()
for line in data:
    if line[:3] == 'mas':
        mask = dict()
        decode = list(line[7:])
        numberOfX = decode.count('X')
        for i in range(len(decode)):
            if decode[i] != '0':
                mask[i] = decode[i]
        continue  # break
    else:
        ip, value = int(line.split('] = ')[0][4:]), int(line.split('] = ')[1])

    ip_binary = bin(ip)[2:].zfill(36)
    addresses = new_maskeration(ip_binary, mask, numberOfX)  # retrun a list of integer
    for ip in addresses:
        mem[ip] = value

print(f"Part 2: {showResoult(mem)}")  # 5724245857696
