import monorail

INPUT = '''cpy a d
cpy 11 c
cpy 231 b
inc d
dec b
jnz b -2
dec c
jnz c -5
cpy d a
jnz 0 0
cpy a b
cpy 0 a
cpy 2 c
jnz b 2
jnz 1 6
dec b
dec c
jnz c -4
inc a
jnz 1 -7
cpy 2 b
jnz c 2
jnz 1 4
dec b
dec c
jnz 1 -4
jnz 0 0
out b
jnz a -19
jnz 1 -21'''


x = 0
while True:
    print(x)
    bunny = monorail.monorail(INPUT)
    bunny.regs['a'] = x
    bunny.run()
    x += 1

# solution 189
