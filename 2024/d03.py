import re

data = open("2024/input/d3.txt").read()

regex = "(mul[(]\d+,\d+[)]|do[(][)]|don't[(][)])" # (mul[(]\d+,\d+[)])

extract = re.findall(regex, data)

ans = 0
enable = 1
for op in extract:
    if (op == "do()"): enable = 1
    elif (op == "don't()"): enable = 0
    else:
        a, b = op[4:-1].split(',')
        ans += int(a) * int(b) * enable
print(ans)