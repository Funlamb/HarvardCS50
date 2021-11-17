"""Create mario pyramids"""

while True:
    height = int (get_int("Height: "))
    if height <= 8 and height > 0:
        break

space = height - 1
brick = 1

for i in range(height):
    print(" " * space, end="")
    print("#" * brick)
    space -= 1
    brick += 1