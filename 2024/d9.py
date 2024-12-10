import time
from collections import defaultdict, Counter, deque

start = time.time()
data = open("./input/d9.txt",'r').read()

ans = 0
posId = 1
unpack = ['0'] * int(data[0])

# for i in range(1,len(data)-1,2):
#     space,file = data[i:i+2]
#     unpack = unpack + ['.'] * int(space) + [str(posId)] * int(file)
#     posId += 1

# while ('.' in unpack):
#     last_pos = len(unpack)-1
#     first_space = unpack.index('.')
#     while unpack[last_pos] == '.':
#         last_pos -= 1
#     last_char = unpack[last_pos]
#     unpack = unpack[:first_space] + [last_char] + unpack[first_space+1:last_pos]

# for i in range(len(unpack)):
#     ans += int(unpack[i]) * i
# print(ans) 

#Part2

A = deque([])
SPACES = deque([])
DISK = []
ans2 = 0
posId = 0
file_name = 0

for i, c in enumerate(data):
    if i % 2 == 0:
        A.append((posId,int(c),file_name)) # pos, size, name
        for k in range(int(c)):
            DISK.append(file_name)
            posId += 1
        file_name += 1
    else:
        SPACES.append((posId,int(c)))  # pos, size
        for i in range(int(c)):
            DISK.append(None)
            posId += 1

for (pos, sz, file_name) in reversed(A):
    for space_id, (space_pos, space_sz) in enumerate(SPACES):
        if pos > space_pos and sz <= space_sz:
            for i in range(sz):
                DISK[pos + i] = None
                DISK[space_pos + i] = file_name
            SPACES[space_id] = (space_pos+sz, space_sz-sz)
            break

for i,c in enumerate(DISK):
    if c is not None:
        ans2 += i*c
print(ans2)