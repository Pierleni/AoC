import numpy as np

cell = '''.#.
..#
###'''

cells = {}
with open('cell.txt', 'r') as f:  # add '\n' at the bottom file
    line = [line[:-1] for line in f]
    for cel in line:
        start, to = cel.split(' => ')
        cells[start.replace('/', '')] = [[l for l in riga] for riga in to.split('/')]

matrix = [[l for l in line] for line in cell.split('\n')]


def flip(matrix):
    return [row[::-1] for row in matrix]


def upside_down(matrix):
    return matrix[::-1]


def rotate(matrix):
    temp, new_list = list(zip(*matrix[::-1])), []
    for el in temp:
        el = list(el);
        new_list.append(el)
    return new_list

#
def permutation(matrix):
    new_matrix, copy = [], matrix[:]

    for _ in range(4):
        st1, st2, st3 = '', '', ''
        rot = rotate(copy)
        cazzo = []

        n1 = [''.join(rot[x]) for x in range(len(rot))]
        n2 = [''.join(flip(rot)[x]) for x in range(len(rot))]
        n3 = [''.join(upside_down(rot)[x]) for x in range(len(rot))]

        for e in n1: st1 += e
        for e in n2: st2 += e
        for e in n3: st3 += e

        cazzo.append(st1)
        cazzo.append(st2)
        cazzo.append(st3)

        for c in cazzo:
            if c in cells:
                new_matrix += cells[c]


        copy = rot

    return new_matrix


def blockshaped(matrix, nrows, ncols):
    """
    Return an array of shape (n, nrows, ncols) where
    n * nrows * ncols = arr.size

    If arr is a 2D array, the returned array should look like n subblocks with
    each subblock preserving the "physical" layout of arr.
    """
    print(matrix.shape)
    h, w = matrix.shape
    return (matrix.reshape(h//nrows, nrows, -1, ncols)
               .swapaxes(1,2)
               .reshape(-1, nrows, ncols))


for iter in range(2):
    perm = []
    new_grid = []
    l = 0
    if len(matrix) % 2 == 0:
        perm, k = [], []
        for y in range(0, len(matrix), 2):
            new_lines = [[],[],[],[]]
            for x in range(0, len(matrix), 2):
                k += [matrix[y][x:x+2], matrix[y+1][x:x+2]]
                print('k',k)
                perm = permutation(k)
                print('perm',perm)


    elif len(matrix) % 3 == 0:
        perm = []
        new_grid = []
        for y in range(0, len(matrix), 3):
            new_lines = [[],[],[],[]]
            for x in range(0, len(matrix), 3):
                k = [matrix[y][x:x + 3], matrix[y + 1][x:x + 3], matrix[y + 2][x:x + 3]]
                perm = permutation(k)

            for i, l in enumerate(perm):
                print('i',i,'l',l)
                new_lines[i].extend(list(l))
        new_grid.extend(l for l in new_lines)
        print(new_grid)
        matrix = new_grid









# import numpy as np
# from collections import Counter
#
#
# def expand(pre, post):
#     rules = []
#
#     for k in [0, 1, 2, 3]:
#         rot = np.rot90(pre, k=k)
#         rules.append((rot.flatten(), post))
#         rules.append((np.fliplr(rot).flatten(), post))
#         rules.append((np.flipud(rot).flatten(), post))
#
#     return rules
#
#
# def match(incell, rules):
#     for pre, post in rules:
#         if np.allclose(incell.flatten(), pre):
#             return post
#     assert False
#
#
# def iterate(grid):
#     size = len(grid)
#     if size % 2 == 0:
#         steps = size // 2
#         new_grid = np.zeros((3*steps, 3*steps))
#         for row in range(steps):
#             for col in range(steps):
#                 incell = grid[2*row:2*row + 2, 2*col:2*col + 2].copy()
#                 outcell = match(incell, rules2)
#                 new_grid[3*row:3*row + 3, 3*col:3*col + 3] = outcell.copy()
#     elif size % 3 == 0:
#         steps = size // 3
#         new_grid = np.zeros((4*steps, 4*steps))
#         for row in range(steps):
#             for col in range(steps):
#                 incell = grid[3*row:3*row + 3, 3*col:3*col + 3].copy()
#                 outcell = match(incell, rules3)
#                 new_grid[4*row:4*row + 4, 4*col:4*col + 4] = outcell.copy()
#     else:
#         assert False
#     return new_grid
#
#
# def calc_block_map_3_iters(block_string):
#     block = np.array([int(c) for c in block_string]).reshape((3, 3))
#
#     grid = iterate(block)
#     grid = iterate(grid)
#     grid = iterate(grid)
#
#     counts = Counter()
#     for row in range(3):
#         for col in range(3):
#             to_block = grid[3*row:3*row+3, 3*col:3*col+3]
#             to_block = ''.join(str(int(x)) for x in to_block.flatten())
#             counts[to_block] += 1
#
#     return counts
#
#
# def fast_count(init_block, steps):
#     if steps % 3 != 0:
#         assert False
#     steps //= 3
#
#     block_counts = Counter()
#     block_counts[init_block] += 1
#     maps = {}
#
#     for step in range(steps):
#         new_block_counts = Counter()
#
#         for block, count in block_counts.items():
#             if block not in maps:
#                 maps[block] = calc_block_map_3_iters(block)
#             for to_block, to_count in maps[block].items():
#                 new_block_counts[to_block] += count * to_count
#
#         block_counts = new_block_counts
#
#     total_ones = 0
#     for block, count in block_counts.items():
#         total_ones += block.count("1") * count
#
#     return total_ones
#
#
# rules2 = []
# rules3 = []
# with open("cell.txt", 'r') as f:
#     for line in f.readlines():
#         pre, post = line.strip().split(" => ")
#         pre = pre.replace("/", "")
#         post = post.replace("/", "")
#         pre = np.array([1 if c == "#" else 0 for c in pre])
#         post = np.array([1 if c == "#" else 0 for c in post])
#
#         if len(pre) == 4:
#             rules2 += expand(pre.reshape((2, 2)), post.reshape((3, 3)))
#         elif len(pre) == 9:
#             rules3 += expand(pre.reshape((3, 3)), post.reshape((4, 4)))
#         else:
#             assert False
#
# init_block = "010001111"
# print(fast_count(init_block, 12))