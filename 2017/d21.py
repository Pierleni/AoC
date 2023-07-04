import sys
sys.path.append("../")

artBook = dict()

matrice = [
        ['.','#','.'],
        ['.','.','#'],
        ['#','#','#']]


def show_matrix(matrix):
    for m in matrix:
        print(*m)
    print()


def flip(matrix):
    return [m[::-1] for m in matrix]


def r90(image):
    transcribe = [[' ' for _ in range(len(image[0]))]for _ in range(len(image))]
    for x in range(len(image[0])):
        for y in range(len(image)):
            transcribe[y][x] = image[x][y]
    return flip(transcribe)


def count(image):
    result = 0
    for row in image:
        for c in row:
            if c == '#':
                result += 1
    return result


def make_extension(tmp):
    tmp_rev = flip(tmp)
    for target in [tmp,r90(tmp),
                    r90(r90(tmp)),
                    r90(r90(r90(tmp))),
                    tmp_rev,
                    r90(tmp_rev),
                    r90(r90(tmp_rev)),
                    r90(r90(r90(tmp_rev)))]:
        line = ""
        for j in range(len(target)):
            for i in range(len(target)):
                line += target[j][i]
        for k, value in artBook.items():
            if (line == k):
                return value



def splitta_in2(N, image):
    row = 0
    matrix = []
    for y in range(0, N, 2):
        tmp = [[' ',' '],[' ',' ']]
        matrix.append([])
        matrix.append([])
        matrix.append([])
        for x in range(0, N, 2):
            tmp[0][0]= image[y][x]
            tmp[0][1]= image[y][x+1]
            tmp[1][0]= image[y+1][x]
            tmp[1][1]= image[y+1][x+1]

            extension = make_extension(tmp)

            for yy in range(3):
                matrix[yy + row] += extension[yy]
        
        row += 3
    
    return matrix


def splitta_in3(N, image):
    row = 0
    matrix = []
    for y in range(0, N, 3):
        tmp = [[' ',' ',' '],[' ',' ',' '],[' ',' ',' ']]
        matrix.append([])
        matrix.append([])
        matrix.append([])
        matrix.append([])
        for x in range(0, N, 3):
            tmp[0][0] = image[y][x]
            tmp[0][1] = image[y][x+1]
            tmp[0][2] = image[y][x+2]
            tmp[1][0] = image[y+1][x]
            tmp[1][1] = image[y+1][x+1]
            tmp[1][2] = image[y+1][x+2]
            tmp[2][0] = image[y+2][x]
            tmp[2][1] = image[y+2][x+1]
            tmp[2][2] = image[y+2][x+2]

            extension = make_extension(tmp)

            for yy in range(4):
                matrix[yy + row] += extension[yy]
        
        row += 4
    
    return matrix
                
            

def solve(matrice, time):
    for _ in range(time):
        
        N = len(matrice)
        if (N % 2 == 0):
            new_matrix = splitta_in2(N, matrice)
        elif (N % 3 == 0):
            new_matrix = splitta_in3(N, matrice)
                        
        show_matrix(new_matrix)
        matrice = new_matrix
    
    print(count(matrice))



with open("input/d21.txt", 'r') as file:
    for line in file.read().split('\n'):
        l1, l2 = line.split(" => ")
        l1 = l1.replace('/','')
        pices = l2.split('/')
        artBook[l1] = pices

solve(matrice, 5)
#solve(matrice, 18)