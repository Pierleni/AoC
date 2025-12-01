#!/usr/bin/python3
from collections import defaultdict

data = open("./input/d11.txt",'r').read()
print(data)
blink = 25
stones = [n for n in data.split()]

for b in range(blink):
    final = []
    for i in range(len(stones)):
        stone = stones[i]
        if stone == '0': final.append('1')
        elif len(stone) % 2 == 1: final.append(str(int(stone) * 2024))
        elif len(stone) % 2 == 0:
            f, s = stone[:len(stone)//2], stone[len(stone)//2:]
            final.append(f)
            final.append('0' if int(s) == 0 else str(int(s)))
    stones = final
print(len(stones))

memory = defaultdict(int)

stones = [n for n in data.split()]
for n in stones:
    memory[n] += 1
print(memory)

for _ in range(75):
	new_memory = defaultdict(int)
	for stone, quantity in memory.items():
		if stone == '0': new_memory['1'] += quantity
		elif  len(stone) % 2 == 0:
			f, s = stone[:len(stone)//2], stone[len(stone)//2:]
			ss = '0' if int(s) == 0 else str(int(s)) 
			new_memory[ss] += quantity
			new_memory[f] += quantity
		elif len(stone) % 2 == 1:
			new_num = str(int(stone) * 2024)
			new_memory[new_num] += quantity
	memory = new_memory

sum = 0
for k, v in new_memory.items():
	sum += v
print(sum)