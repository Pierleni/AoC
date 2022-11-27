from turtle import ycor

tmp_x = []
tmp_y = []
file = open("input/d17.txt", 'r').read();

def find_range(cont):
    tmp = []
    data = cont[2:].split("..")
    for d in data: tmp.append(int(d))
    return tmp


for line in file.split('\n'):
    coor1, coor2 = line.split(", ")
    for c in (coor1, coor2):
        if c[0] == 'x': tmp_x += find_range(c)
        else: tmp_y += find_range(c)

minX, maxX = min(tmp_x), max(tmp_x)
minY, maxY = min(tmp_y), max(tmp_y)
xrange = maxX - minX
yrange = maxY - minY

print(minX, maxX, minY, maxY)


# create surface
surface = []
for y in range((maxY - minY) + 3):
    surface.append([])
    for x in range((maxX - minX) + 3):
        surface[-1].append('.')


for line in file.splitlines():
    coor1, coor2 = line.split(", ")

    if coor1[0] == 'x':
        xcorStart = abs((maxX - int(coor1[2:])) - xrange)
        xcorEnd   = xcorStart + 1
    if coor1[0] == 'y':
        ycorStart = abs((maxY - int(coor1[2:])) - yrange)
        ycorEnd = ycorStart + 1
 
    if coor2[0] == 'x':
        data = coor2[2:].split("..")
        xcorStart = abs((maxX - int(data[0]) - xrange))
        xcorEnd = abs(maxX - int(data[1]) - xrange) + 1
    if coor2[0] == 'y':
        data = coor2[2:].split("..")
        ycorStart = abs((maxY - int(data[0]) - yrange))
        ycorEnd = abs(maxY - int(data[1]) - yrange) + 1
    

    for y in range(ycorStart, ycorEnd):
        for x in range(xcorStart, xcorEnd):
            surface[y][x] = '#'

    # for r in surface:
    #     print(*r)
    # input()


for r in surface:
    print(*r)