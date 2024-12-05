from cs50 import get_float

money = 0
change = 0

while True:
    money = get_float("Change: ")
    if money > 0:
        break

while money >= 0.25:
    money = round(money - 0.25, 2)
    change += 1

while money >= 0.1:
    money = round(money - 0.1, 2)
    change += 1

while money >= 0.05:
    money = round(money - 0.05, 2)
    change += 1

while money >= 0.01:
    money = round(money - 0.01, 2)
    change += 1

print(change)
