import sys
import re

input = sys.stdin.readline


def calculate_to_rxcy(coordinate):
    column = 0
    row = ''

    for char in coordinate:
        if char.isdigit():
            row += char
        else:
            column = column * 26 + (ord(char) - ord('A') + 1)

    return f'R{row}C{column}'

def convert_to_excel_column(column_number):
    column = ''
    while column_number > 0:
        column_number -= 1
        column = chr(column_number % 26 + ord('A')) + column
        column_number //= 26
    
    return column
def calculate_to_excel(coordinate):
    row = ''
    column = ''
    column_number = 0
    i = 0

    while i < len(coordinate):
        if(coordinate[i] == 'R'):
            i += 1
            while i < len(coordinate) and coordinate[i].isdigit():
                row += coordinate[i]
                i += 1
        elif(coordinate[i] == 'C'):
            i += 1
            column_number = int(coordinate[i:])
            break
    return f'{convert_to_excel_column(column_number)}{row}'


n = int(input())

list_of_coordinates = [input().strip() for _ in range(n)]

for coordinate in list_of_coordinates:
    if re.match(r"^R\d+C\d+$", coordinate):
        print(calculate_to_excel(coordinate))
    else:
        print(calculate_to_rxcy(coordinate))