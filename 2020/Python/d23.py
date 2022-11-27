inp = "389125467"
cups = [int(c) for c in inp]


def delete_cups(index):
    cups_to_delete = []
    for i in range(index,index+3):
        cups_to_delete.append(cups[i%len(cups)])
    return cups_to_delete

def choose_destination(current_cup, deleted_cups):
    cup = current_cup
    while True:
        cup -= 1
        if cup < 1: cup = 9
        if cup not in deleted_cups:
            return cup


index = 0
while index < 3:
    cup = cups[index] 
    deleted_cups = delete_cups(index+1)                             # delete next 3 cups
    destination = choose_destination(cup, deleted_cups)             # find destination
    # re arrange list:
    # temporary delete cups
    #cups = cups[index:] + cups[:index]
    print(f"current cup: {cup}\ndestination: {destination}")
    del cups[(index+1)%len(cups):(index+4)%len(cups)]               # quando elimini le tre coppe,
    index_destination = cups.index(destination)                     # DEVI FAR ROTEARE TUTTA LA LISTA DI 3
    print(cups, index_destination); input()                         # la len() è sempre 9 e troverai così l'esatto indice di destinazione
    for i, n in enumerate(deleted_cups):
        print(i, (i + index_destination) % 9, n)
        cups.insert((i + index_destination + 1) % 9, n)
    

    print(cups, deleted_cups, destination); input()
    index += 1