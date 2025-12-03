part1 = 0
with open("./input/d03.txt", 'r') as f: 
        lines = f.read().splitlines()
        for line in lines:
                l_index = line.index(max([x for x in line[:-1]]))
                r_index = line.index(max([x for x in line[l_index+1:]]))
                numb = str(line[l_index]) + str(line[r_index])
                part1 += int(numb)
        print(f"Part 1: {part1}")

part2 = 0
with open("./input/d03.txt", 'r') as f: 
        lines = f.read().splitlines()
        for line in lines:
                k = 12
                stack = []
                drop = len(line) - k

                for n in line:
                        while drop > 0 and stack and stack[-1] < n:
                                stack.pop()
                                drop -= 1
                        stack.append(n)
                part2 += int(''.join(stack[:k]))
        print(f"Part 2: {part2}")