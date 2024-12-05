from cs50 import get_int

while True:
    num = get_int("Height: ")
    if 0 < num < 9:
        break

for i in range(num):
    print(" " * (num - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
