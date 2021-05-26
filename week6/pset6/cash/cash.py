from cs50 import get_float

while True:
    amount = get_float("Change owed: ")
    if amount > 0:
        break
    
plata = round(amount * 100)
monedas = 0
remainder = plata

while(plata > 0):
    if plata >= 25:
        plata -= 25
        monedas += 1
    elif plata >= 10:
        plata -= 10
        monedas += 1
    elif plata >= 5:
        plata -= 5
        monedas += 1
    else:
        plata -= 1
        monedas += 1
print(monedas)