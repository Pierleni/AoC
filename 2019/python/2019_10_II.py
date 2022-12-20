"""
https://0xdf.gitlab.io/adventofcode2019/10
"""

INPUT = '''.###.###.###.#####.#
#####.##.###..###..#
.#...####.###.######
######.###.####.####
#####..###..########
#.##.###########.#.#
##.###.######..#.#.#
.#.##.###.#.####.###
##..#.#.##.#########
###.#######.###..##.
###.###.##.##..####.
.##.####.##########.
#######.##.###.#####
#####.##..####.#####
##.#.#####.##.#.#..#
###########.#######.
#.##..#####.#####..#
#####..#####.###.###
####.#.############.
####.#.#.##########.'''

# import math
# from collections import defaultdict
#
# def dist(a1,a2):  #manhattan distance
#     return math.sqrt(pow(a1[0] - a2[0], 2) + pow(a1[1] - a2[1], 2))
#
# def can_see(x, y):
#     if x == y:
#         return False
#     for z in asteroids:
#         if x == z or y == z:
#             continue
#         if ((dist(x,y) + dist(y,z)) - dist(x,z)) < 0.0001:
#             return False
#     return True
#
# lines = [line for line in INPUT.split('\n')]
#
# asteroids = []
# for x in range(len(lines)):
#     for y in range(len(lines[x])):
#         if lines[x][y] == '#':
#             asteroids.append((x,y))
#
# base = (16,8)
#
# angles = defaultdict(list)
# for ast in asteroids:
#     if ast == base:
#         continue
#     angle = (math.degrees(math.atan2(ast[1] - base[1], ast[0] - base[0])) + 90) % 360
#     angles[angle].append((dist(ast, base), ast))
#
# for angle in angles:
#     angles[angle] = sorted(angles[angle], reverse=True)
#
# i = 0
# for angle in sorted(angles):
#     boom = angles[angle].pop()
#     i += 1
#     if i == 200:
#         max_value = boom[1]
#
# print(max_value)
# print((max_value[1]*100 + max_value[0]))

"""Figure out the best asteroid to look at other asteroids.  And then BLAST THEM!"""

from dataclasses import dataclass
from math import gcd
from typing import List, Set


@dataclass(frozen=True)
class Point:
    """An X, Y coordinate on a grid"""
    x: int
    y: int


def parse(text: str) -> Set[Point]:
    """Expects a 2D grid of characters.  '#' denote asteroids.

    Note: Here, Y+ is down.
    """
    asteroids = set()
    rows = text.splitlines()
    for y, row in enumerate(rows):
        for x, cell in enumerate(row):
            if cell == "#":
                asteroids.add(Point(x, y))

    return asteroids


def find_best(asteroids: Set[Point]) -> (Point, int):
    """Finds the asteroid that can see the most other asteroids.

    Returns that asteroid and how many others it can see.
    """
    scores = [(a, count_visible(a, asteroids)) for a in asteroids]
    return max(scores, key=lambda x: x[1])


def count_visible(base: Point, asteroids: Set[Point]) -> int:
    """Counts how many asteroids are in line of sight."""
    return sum(1 for asteroid in asteroids if can_see(base, asteroid, asteroids))


def can_see(a: Point, b: Point, asteroids: Set[Point]) -> bool:
    """Determines whether or not an asteroid can see another in an asteroid field."""

    # Asteroids can't see themselves.
    if a == b:
        return False

    dx = b.x - a.x
    dy = b.y - a.y

    divisor = gcd(dy, dx)

    if divisor != 0:
        # Line isn't vertical or horizontal.  Get basic slope.
        dx //= divisor
        dy //= divisor
    else:
        # Line is vertical or horizontal.  Divisor becomes simply
        # the magnitude of the non-zero component.
        divisor = max(dx, dy)

    # Step over every cell on the line between a and b and see if
    # it's an asteroid.  If any of them are, then b can't be seen from a.
    for step in range(1, divisor):
        if Point(a.x + step*dx, a.y + step*dy) in asteroids:
            return False

    return True


@dataclass(order=True)
class LaserPriority:
    """A helper class for prioritizing which asteroids get blasted first.

    Quadrant assumes X+ is right and Y+ is up, with base at the origin.
    Slope uses Y/X, but gets multiplied by -1 so that Laser Priorities
    get sorted based on quadrant and then slope in descending order.
    """
    quadrant: int
    slope: float


def laser_priority_sort_key(asteroid: Point) -> LaserPriority:
    """Prioritize asteroids based on how they clock around the origin.

    Starting at Y+ (up) and going CW.
    This function assumes all asteroids being compared are visible.
    """
    result = LaserPriority(0, 0)

    # Simulate vertical slope as ">> size of grid"
    # because ~~~InFiNiTy Is HaRd FoR cOmPuTeRs~~~
    if asteroid.x == 0:
        result.slope = 1000
    else:
        result.slope = asteroid.y / asteroid.x

    result.slope *= -1  # Flip so sort goes largest to smallest

    if asteroid.x >= 0 and asteroid.y > 0:
        result.quadrant = 1
    elif asteroid.x > 0 and asteroid.y <= 0:
        result.quadrant = 2
    elif asteroid.x <= 0 and asteroid.y < 0:
        result.quadrant = 3
    else:
        result.quadrant = 4

    return result


def create_laser_plan(base: Point, asteroids: Set[Point]) -> List[Point]:
    """Specify the order in which asteroids get BLASTED, assuming we start
    at 12 o'clock and go CW, blasting only one asteroid at a time for a
    particular clocking before moving on.
    """
    asteroids = asteroids - {base}

    # Convert everything so that Y+ is up and base is at 0, 0
    relative_asteroids = {Point(a.x - base.x, -(a.y - base.y))
                          for a in asteroids}

    plan = []
    # Blast asteroids in rounds, removing the ones that get blasted
    # after every cycle
    while relative_asteroids:
        visible = {a for a in relative_asteroids if can_see(
            Point(0, 0), a, relative_asteroids)}
        plan += sorted(visible, key=laser_priority_sort_key)
        relative_asteroids -= visible

    # Unconvert back to global coordinates with Y+ down
    plan = [Point(base.x + a.x, base.y - a.y) for a in plan]
    return plan


if __name__ == "__main__":


    asteroids = parse(INPUT)
    best, score = find_best(asteroids)
    print(f"Best is {best} with {score} visible.")

    plan = create_laser_plan(best, asteroids)
    answer = plan[199]  # O-based counting!!!

    print(f"Lucky number 200 is {answer}.")
    print(f"Magic number is {answer.x * 100 + answer.y}.")
