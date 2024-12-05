from cs50 import get_string


def main():
    text = get_string("Text: ")
    index = get_index(text)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def get_index(text):
    letter = 0
    word = 0
    sent = 0
    sents = [".", "!", "?"]

    for char in text:
        if char.isalpha():
            letter += 1
        elif char == " ":
            word += 1
        elif char in sents:
            sent += 1

    word += 1

    l = letter / word * 100
    s = sent / word * 100
    return round(0.0588 * l - 0.296 * s - 15.8)


if __name__ == "__main__":
    main()
