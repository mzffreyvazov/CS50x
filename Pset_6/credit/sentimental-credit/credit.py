def isValid(number):
    if not number.isdigit():
        return False

    total = 0
    is_even = len(number) % 2 == 0

    for i in range(len(number)):
        digit = int(number[i])

        if is_even:
            if i % 2 == 0:
                to_add = digit * 2
                total += to_add if to_add < 10 else to_add - 9
            else:
                total += digit
        else:
            if i % 2 != 0:
                to_add = digit * 2
                total += to_add if to_add < 10 else to_add - 9
            else:
                total += digit

    return total % 10 == 0


def card_type(number):
    amex = [34, 37]
    master = [51, 52, 53, 54, 55]
    visa = [4]

    if any(number.startswith(str(prefix)) for prefix in amex) and len(number) == 15:
        return "AMEX"
    elif any(number.startswith(str(prefix)) for prefix in master) and len(number) == 16:
        return "MASTERCARD"
    elif any(number.startswith(str(prefix)) for prefix in visa) and len(number) in [13, 16]:
        return "VISA"
    else:
        return "INVALID"


if __name__ == "__main__":
    number = input("Number: ")
    if isValid(number):
        print(card_type(number))
        print(isValid(number))
    else:
        print("INVALID")