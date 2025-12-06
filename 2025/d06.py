part1 = 0
matrix = []
with open("./input/d06.txt", 'r') as f:
        data = f.read().splitlines()
        for line in data:
                matrix.append(line.split())
        for x in range(len(matrix[0])):
                opr = matrix[len(matrix)-1][x]
                parz = int(matrix[0][x])
                for y in range(1, len(matrix)-1):
                        if (opr == '+'):
                                parz += int(matrix[y][x])
                        else:
                                parz *= int(matrix[y][x])
                part1 += parz
        print(part1)

part2 = 0
matrix = []
op_pos = []
with open("./input/d06.txt", 'r') as f:
        data = f.read().splitlines()
        ll = len(data)-1
        for i in range(len(data[0])):
                if (data[ll][i] != ' '):
                        op_pos.append(i)
        op_pos.append(len(data[0])+1)

        for i in range(len(op_pos)-2, -1, -1):
                start = op_pos[i]
                end = op_pos[i+1]-2
                numbs = []
                for x in range(end, start-1, -1):
                        st_num = ""
                        for y in range(ll):
                                st_num += data[y][x] if data[y][x] != ' ' else ''
                        numbs.append(int(st_num))
                opr = data[ll][start]
                parz = numbs[0]
                for k in range(1, len(numbs)):
                        if (opr == '+'):
                                parz += numbs[k]
                        else:
                                parz *= numbs[k]
                part2 += parz
        print(part2)