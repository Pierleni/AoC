# Part 2
data = open("./input/10.txt").read()
arr = [int(line) for line in data.split('\n')]
arr.sort()
arr.append(arr[-1]+3)

memo = {0: 1}
for r in arr:
  memo[r] = memo.get(r-3,0) \
          + memo.get(r-2,0) \
          + memo.get(r-1,0)
print(memo[arr[-1]])