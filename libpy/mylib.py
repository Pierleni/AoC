def reverseList(lista):
    return lista[::-1]


def LRShift(lista, n) -> list:
    """Positive n: shift list to the LEFT
    Negative n: shift list to the RIGHT"""
    k = n % len(lista)
    return lista[k:] + lista[:k]


def rotate_row(row, val, matrix):
    chunk = LRShift(matrix[row], val)
    for x in range(len(matrix[row])):
        matrix[row][x] = chunk[x]


def rotate_column(col, val, matrix):
    chunk = []
    for y in range(len(matrix)):
        chunk.append(matrix[y][col])
    chunk = LRShift(chunk, -val)
    for y in range(len(matrix)):
        matrix[y][col] = chunk[y]


def validate_coord(y, x, matrix):
    return (0 <= y < len(matrix)) & (0 <= x < len(matrix[0]))


def validate_coord_AvoidValue(y, x, matrix, condition_to_avoid):
    return (
        (0 <= y < len(matrix))
        & (0 <= x < len(matrix[0]))
        & (matrix[y][x] != condition_to_avoid)
    )


def validate_coord_WithValue(y, x, matrix, condition_to_check):
    return (
        (0 <= y < len(matrix))
        & (0 <= x < len(matrix[0]))
        & (matrix[y][x] == condition_to_check)
    )


def validate_coord_new(y, x, matrix, predicate=None):
    valid = matrix[y][x] if predicate is None else predicate(matrix[y][x])

    return (0 <= y < len(matrix)) and (0 <= x < len(matrix[0])) and valid


def checkNeighb4(y, x, matrix, condition, checkCondition=False) -> list:
    """
    Se vuoi evitare un valore (condition) tra i vicini lascia checkCondition to False
    Se vuoi cercare un determinato valore tra i vicini imposta checkCondition to True
    """
    validated = []
    for (j, i) in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
        yy = y + j
        xx = x + i

        if validate_coord_new(
            yy,
            xx,
            matrix,
            lambda v: v == condition if checkCondition else v != condition,
        ):
            validated.append((yy, xx))

    return validated


NEIGHBORS_4 = [(1, 0), (-1, 0), (0, 1), (0, -1)]


def checkNeighb_any(y, x, matrix, neighbors, predicate) -> list:
    """
    Se vuoi evitare un valore (condition) tra i vicini lascia checkCondition to False
    Se vuoi cercare un determinato valore tra i vicini imposta checkCondition to True
    """
    validated = []
    for (j, i) in neighbors:
        yy = y + j
        xx = x + i

        if validate_coord_new(yy, xx, matrix, predicate):
            validated.append((yy, xx))

    return validated


def bfs(newMatrix, originalMaze, start, target, condition) -> list:
    queue = [start]
    visited = [start]
    while (len(queue) > 0) & (target not in queue):
        coord = queue.pop(0)
        y, x = coord[0], coord[1]
        newCoord = checkNeighb_any(
            y, x, originalMaze, NEIGHBORS_4, lambda v: v != condition
        )

        for (a, b) in newCoord:
            if (a, b) not in visited:
                queue.append((a, b))
                visited.append((a, b))
                newMatrix[a][b] = newMatrix[y][x] + 1

    return newMatrix


def buildShortPath(y, x, matrix) -> list:
    currentValue = matrix[y][x]
    finalPath = []
    a, b = y, x
    while currentValue != 1:
        newCoord = checkNeighb4(a, b, matrix, currentValue - 1, True)
        couple = newCoord.pop(0)
        a, b = couple[0], couple[1]
        currentValue = matrix[a][b]
        finalPath.append((a, b))

    return finalPath
