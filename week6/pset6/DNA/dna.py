import sys
import csv

# Verificar los datos de entrada:

if len(sys.argv) != 3:
    sys.exit("Debes especificar un database y una secuencia")

# Lectura de la base de datos:

csv_database = open(sys.argv[1], 'r')

# Crear una lista para sacar los str
strs = []

# Crear un diccionario para sacar las personas:

people = {}

# Correr el for que permitira obtener la lista y el diccionario:

for i, row in enumerate(csv_database):
    if i == 0:
        strs = [st for st in row.strip().split(',')][1:]

    else:
        current_row = row.strip().split(',')
        people[current_row[0]] = [int(x) for x in current_row[1:]]

# Leer la secuencia de DNA:

dna_sequence = open(sys.argv[2], 'r').read()

# Se debe correr un for mediante alguna "ventana" que contabilice la cantidad de strs
# Hay que tener un contador de los strs:
count_str = []
for st in strs:
    # Empieza en la posición 0 de la secuencia
    i = 0
    max_str = 0
    curr_max = 0

    # Ahora algo que recorra la secuencia:

    while i < len(dna_sequence):
        window = dna_sequence[i: i + len(st)]
        if window == st:
            curr_max += 1
            max_str = max(max_str, curr_max)
            i += len(st)
        else:
            curr_max = 0
            i += 1
    # Finalmente añadir las cuentas de cada str a el contador:
    count_str.append(max_str)

# Iterar sobre el diccionario para encontrar a quién pertenece la cuenta:

for name, data in people.items():
    if data == count_str:
        print(name)
        exit(0)
print("No Match")