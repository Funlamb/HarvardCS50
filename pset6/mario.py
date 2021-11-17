"""Create mario pyramids"""

height = int (input("Height: "))

space = height - 1
brick = 1

for i in range(height):
    print(" " * space, end="")
    print("#" * brick)
    space -= 1
    brick += 1