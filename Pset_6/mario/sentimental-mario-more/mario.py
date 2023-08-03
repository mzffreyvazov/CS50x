def build_pyramid(height):
    for i in range(1, height + 1):
        spaces = " " * (height - i)
        blocks = "#" * i
        print(spaces + blocks + "  " + blocks)


if __name__ == "__main__":
    while True:
        try:
            height = int(input("Enter the height of the pyramid: "))
            if height <= 0:
                print("Height must be a positive integer.")
            else:
                break
        except ValueError:
            print("Invalid input. Please enter a positive integer.")

    build_pyramid(height)
