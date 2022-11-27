"""
If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
Otherwise, the seat's state does not change.

Part 2:
Vedi il primo sedile disponibile e cambia direzione di osservazione. Se 'L' = 0 / se '#' count++
Also, people seem to be more tolerant than you expected:
it now takes five or more visible occupied seats
for an occupied seat to become empty (rather than four or more from the previous rules).
The other rules still apply:
empty seats that see no occupied seats become occupied, seats matching no rule don't change,
and floor never changes.
"""

DATA = open("../input/11.txt", 'r').read()
matrix = []
for line in DATA.split('\n'):
    matrix.append([])
    for l in line:
        matrix[-1].append(l)


def checkSeat(y, x):
    return 1 if 0 <= y < len(matrix) and 0 <= x < len(matrix[0]) and matrix[y][x] == '#' else 0


def eightDirection(y, x):
    count = 0
    for j, i in [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]:
        count += checkSeat(y + j, x + i)
    return count


def conta(yy, xx):
    return 1 if matrix[yy][xx] == '#' else 0


def firstChair(y, x):
    countSeats = 0
    # UP
    _y = y - 1
    while _y >= 0:
        if matrix[_y][x] == '.':
            _y -= 1
            continue
        else:
            countSeats += conta(_y, x)
            break

    # DOWN
    _y = y + 1
    while _y < len(matrix):
        if matrix[_y][x] == '.':
            _y += 1
            continue
        else:
            countSeats += conta(_y, x)
            break

    # LEFT
    _x = x - 1
    while _x >= 0:
        if matrix[y][_x] == '.':
            _x -= 1
            continue
        else:
            countSeats += conta(y, _x)
            break

    # RIGHT
    _x = x + 1
    while _x < len(matrix[0]):
        if matrix[y][_x] == '.':
            _x += 1
            continue
        else:
            countSeats += conta(y, _x)
            break

    # UPLEFT
    _y, _x = y - 1, x - 1
    while _y >= 0 and _x >= 0:
        if matrix[_y][_x] == '.':
            _y -= 1
            _x -= 1
            continue
        else:
            countSeats += conta(_y, _x)
            break

    # UPRIGHT
    _y, _x = y - 1, x + 1
    while _y >= 0 and _x < len(matrix[0]):
        if matrix[_y][_x] == '.':
            _y -= 1
            _x += 1
            continue
        else:
            countSeats += conta(_y, _x)
            break

    # DOWNLEFT
    _y, _x = y + 1, x - 1
    while _y < len(matrix) and _x >= 0:
        if matrix[_y][_x] == '.':
            _y += 1
            _x -= 1
            continue
        else:
            countSeats += conta(_y, _x)
            break

    # DOWNRIGHT
    _y, _x = y + 1, x + 1
    while _y < len(matrix) and _x < len(matrix[0]):
        if matrix[_y][_x] == '.':
            _y += 1
            _x += 1
            continue
        else:
            countSeats += conta(_y, _x)
            break

    return countSeats


def solve(part=1):
    seat, newSeat = 0, None
    round = 0
    while seat != newSeat:
        newSeat = seat
        empty, occupied = [], []
        for y in range(len(matrix)):
            for x in range(len(matrix[0])):

                if matrix[y][x] == 'L':
                    if part == 1:
                        count = eightDirection(y, x)
                    else:
                        count = firstChair(y, x)
                    if not count:
                        occupied.append((y, x))

                elif matrix[y][x] == '#':
                    if part == 1:
                        count = eightDirection(y, x)
                        if count >= 4:
                            empty.append((y, x))
                    else:
                        count = firstChair(y, x)
                        if count > 4:
                            empty.append((y, x))

        # Rebulid matrix
        for yy, xx in empty:
            matrix[yy][xx] = 'L'
        for yy, xx in occupied:
            matrix[yy][xx] = '#'

        seat = 0
        for r in matrix:
            seat += sum(1 if x == '#' else 0 for x in r)
        round += 1

    print(f"Part {part}: After {round} round there are {newSeat} seats occupied.")


solve()

matrix = []
for line in DATA.split('\n'):
    matrix.append([])
    for l in line:
        matrix[-1].append(l)

solve(2)
