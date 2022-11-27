data = open("../input/04.txt", 'r').read()
data = data.replace('\n', ' ').replace('\n\n', '  ')


def checkPassport(diz):
    byr = diz["byr"]
    iyr = diz["iyr"]
    eyr = diz["eyr"]
    hgt = diz["hgt"]
    hcl = diz["hcl"]
    ecl = diz["ecl"]
    pid = diz["pid"]

    # Birth IssueYear ExiprationYear
    if int(byr) not in range(1920, 2003): return False
    if int(iyr) not in range(2010, 2021): return False
    if int(eyr) not in range(2020, 2031): return False

    # Height
    if hgt[-2:] not in ["cm", "in"]: return False
    if hgt[-2:] == "cm" and int(hgt[:-2]) not in range(150, 194): return False
    if hgt[-2:] == "in" and int(hgt[:-2]) not in range(59, 77): return False

    # Hair Color
    if hcl[0] != '#': return False
    if hcl[0] == '#':
        if len(hcl[1:]) != 6: return False
        for x in hcl[1:]:
            if x not in ("0123456789abcdef"):
                return False
    # eyeColor
    if ecl not in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]:
        return False

    # Passport ID
    if len(pid) != 9: return False
    if not pid.isdigit(): return False

    return True


def validation(diz, part):
    if len(diz) == 8:
        if part == 1:
            return True
        elif checkPassport(diz):
            return True

    elif len(diz) == 7:
        if "cid" not in diz:
            if part == 1: return True
            elif checkPassport(diz):
                return True
    return False

def solve(part):
    valid = 0
    for passport in data.split('  '):
        diz = dict()
        for field in passport.split():
            k, v = field.split(':')
            diz[k] = v
        # Check Passport
        if validation(diz, part):
            valid += 1
    return valid

print(f"Part 1: {solve(1)}")
print(f"Part 2: {solve(2)}")
