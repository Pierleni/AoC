data = open("../input/12.txt", 'r').read()
facing = 'E'
vertical = 0
horizontal = 0
directions = {'N': 'north'}


def turn(facing, value):
    direct = ['N', 'E', 'S', 'W']
    return direct[(direct.index(facing) + value) % len(direct)]


def move(dir, value, vertical, horizontal):
    if dir == 'N':
        vertical += value
    elif dir == 'S':
        vertical -= value
    elif dir == 'E':
        horizontal += value
    elif dir == 'W':
        horizontal -= value

    return vertical, horizontal


for line in data.split('\n'):
    dir, value = line[0], int(line[1:])

    if dir not in ['L', 'R', 'F']:
        vertical, horizontal = move(dir, value, vertical, horizontal)

    else:
        if dir == 'F':
            vertical, horizontal = move(facing, value, vertical, horizontal)
        elif dir == 'R':
            value = value // 90
            facing = turn(facing, value)
        elif dir == 'L':
            value = value // 90
            facing = turn(facing, (value * -1))

print(f"Part 1: {abs(vertical) + abs(horizontal)}")



###################################
#          P A R T  T W O         #
###################################


def wp_change(x_wp,y_wp,direction,degrees):
    x_wp_new = int()
    y_wp_new = int()
    if direction == "L":
        if degrees == 90:
            x_wp_new = y_wp * -1
            y_wp_new = x_wp
        elif degrees == 180:
            x_wp_new = x_wp * -1
            y_wp_new = y_wp * -1
        elif degrees == 270:
            x_wp_new = y_wp
            y_wp_new = x_wp * -1
    elif direction == "R":
        if degrees == 90:
            x_wp_new = y_wp
            y_wp_new = x_wp * -1
        elif degrees == 180:
            x_wp_new = x_wp * -1
            y_wp_new = y_wp * -1
        elif degrees == 270:
            x_wp_new = y_wp * -1
            y_wp_new = x_wp
    return x_wp_new, y_wp_new


def main():
    x_wp = 10
    y_wp = 1
    x_ferry = 0
    y_ferry = 0
    for instruction in data.split('\n'):
        if instruction[0] == 'N':
            y_wp += int(instruction[1:])
        elif instruction[0] == 'S':
            y_wp -= int(instruction[1:])
        elif instruction[0] == 'E':
            x_wp += int(instruction[1:])
        elif instruction[0] == 'W':
            x_wp -= int(instruction[1:])
        elif instruction[0] == 'F':
            x_ferry += int(instruction[1:]) * x_wp
            y_ferry += int(instruction[1:]) * y_wp
        elif instruction[0] == 'R' or 'L':
            x_wp, y_wp = wp_change(x_wp,y_wp,instruction[0],int(instruction[1:]))
    return abs(x_ferry) + abs(y_ferry)


print('Part 2: {}'.format(main()))
