from cs50 import get_float

while True:
    amount = get_float("Change owed: ")
    if amount > 0:
        break
    
plata = round(amount*100)
remainder = plata
deno = [25,10,1]
monedas = []


for i in range(0,3,1):
    monedas.insert(i, remainder//deno[i])
    remainder -= deno[i] * monedas[i]
    
print(monedas)
