def merge_ranges(ranges):
        ranges.sort()
        merged = []

        for start, end in ranges:
                if not merged:
                        merged.append([start, end])
                else:
                        last_start, last_end = merged[-1]
                        if start <= last_end + 1:
                                merged[-1][1] = max(last_end, end)
                        else: merged.append([start, end])
        return merged


part1 = 0
part2 = 0
all_ranges = []
ids_ranges = set()
with open("./input/d05.txt", 'r') as f:
        ranges, ingredients = f.read().split("\n\n")
        for rang in ranges.split("\n"):
                a, b = rang.split("-")
                all_ranges.append((int(a), int(b)))
        for ing in ingredients.split("\n"):
                id = int(ing)
                for start, end in all_ranges:
                        if start <= id <= end:
                                part1 += 1
                                break
        print(part1)

        merged = merge_ranges(all_ranges)
        for start, end in merged:
                part2 += (end + 1) - start
        print(part2)