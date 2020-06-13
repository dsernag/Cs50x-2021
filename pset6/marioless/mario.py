while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break

for i in range(h):
    for j in range(h):
        print("#" if i+j >= h -1 else " ", end="")
    print()
    
