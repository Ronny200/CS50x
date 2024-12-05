from cs50 import get_string


def main():

    while True:
        num = get_string("Number: ")
        if num.isdigit():
            break

    length = len(num)
    head = num[0] + num[1]
    card_visa = ["4"]
    card_amex = ["34", "37"]
    card_master = ["51", "52", "53", "54", "55"]

    if (length == 13 or length == 16) and head[0] in card_visa and check(num):
        print("VISA")
    elif length == 15 and (head in card_amex and check(num)):
        print("AMEX")
    elif length == 16 and (head in card_master and check(num)):
        print("MASTERCARD")
    else:
        print("INVALID")


def check(num):
    sum = 0
    even = False

    for _ in reversed(num):
        dig = int(_)
        if even:
            mul = dig * 2
            sum += mul - 9 if mul > 9 else mul
        else:
            sum += dig
        even = not even

    return sum % 10 == 0

# def check(num):
#     sum = 0
#     count = 1
#     number = int(num)
#     while number > 0:
#         mod = number % 10
#         number //= 10
#         if count % 2 == 0:
#             sum += mod * 2 - 9 if mod * 2 > 9 else mod * 2
#         else:
#             sum += mod
#         count += 1
#     return sum % 10 == 0


if __name__ == "__main__":
    main()
