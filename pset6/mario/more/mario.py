from cs50 import get_int

"""Create mario pyramids"""

# promt user for number between 1 to 8 inclusive
while True:
    height = int(get_int("Height: "))
    if height <= 8 and height > 0:
        break

# print the pyramid
space = height - 1
brick = 1
for i in range(height):
    print(" " * space + "#" * brick + "  " + "#" * brick, end="")
    print()
    space -= 1
    brick += 1