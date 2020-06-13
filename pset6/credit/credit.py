from cs50 import get_int
import re

def main():
    number = get_int("Number: ")
    if validity(number) and check_sum(number) == True:
        type_card(number)

######################
def validity(number):
    if number == int and number > 0 or len(str(number)) == 13 or len(str(number)) == 16 or len(str(number)) == 15:
        return True
    else:
        print("INVALID")
#######################
def check_sum(number):
    number_list = [int(d) for d in str(number)]
    number_invert = []

    #Rango para leer el numero de atras hacia adelante
    rango_inverso = range(len(number_list)-1, -1, -1)

    for j in rango_inverso:
        number_invert.append(number_list[j])

    #Rango para realizar el checksum de los pares
    rango_par = range(1, len(number_list), 2)
    step1 = []

    for i in rango_par:
        step1.append(number_invert[i] * 2)

    #Rango para el step 1
    rango_step1 = range(0, len(step1),1)
    step1_len= len(step1)
    step11 = []
    sum1 = 0
    for i in rango_step1:
        step11.append(sum([int(j) for j in str(step1[i])]))
    sum1 = (sum(step11))

    #Rango para los impares
    rango_impar = range(0, len(number_list), 2)
    step2 = []
    sum2 = 0
    for i in rango_impar:
        step2.append(number_invert[i])
    sum2 = sum(step2)

    suma = sum1+sum2
    if suma % 10 == 0:
        return True
    else:
        print("INVALID")
#######################
def type_card(number):
    num_str = str(number)
    if re.search("^34", num_str) or re.search("^37", num_str):
        print("AMEX")
    elif re.search("^51", num_str) or re.search("^52", num_str) or re.search("^53", num_str) or re.search("^54", num_str) or re.search("^55", num_str):
        print("MASTERCARD")
    elif re.search("^4", num_str):
        print("VISA")
    else:
        print("INVALID")

main()
