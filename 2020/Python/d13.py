data = open('../input/13.txt', 'r').read()
arrival = int(data.split('\n')[0])
busses = [int(x) for x in data.split('\n')[1].split(',') if x != 'x']
firstBus = []

def calcolate(id):
    result, n = 0, 1
    while result < arrival:
        result = id * n
        n += 1
    return ((result - arrival), id)

for bus in busses:
    firstBus.append(calcolate(bus))

firstBus = sorted(firstBus)[0]
print(f"Part 1: {firstBus[0] * firstBus[1]}")

# P A R T - 2

t, step = 0, 1
busses = data.split('\n')[1].split(',')
p2 = [(int(i), j) for j, i in enumerate(busses) if i != 'x']

for bus_id, mins in p2:
    # check to see if bus is departing at current time
    while (t + mins) % bus_id != 0:
        t += step
    # increase step multiple to find next min for next bus
    step *= bus_id

print(f'Part 2: {t}')

