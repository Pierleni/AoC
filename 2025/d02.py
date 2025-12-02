import re

exp = [r"^(?!0)(\d+)\1$", r"^(?!0)(\d+)\1+$"]
for i in range(len(exp)):
    invalids = []
    with open("./input/d02.txt", 'r') as f:
        ids = f.read().split(",")
        for id in ids:
            start, end = id.split("-")
            while (int(start) <= int(end)):
                invalid = re.search(exp[i], start)
                if (invalid): invalids.append(int(invalid.group()))
                start = str(int(start) + 1)
        print(f"Part {i + 1}: {sum(invalids)}")