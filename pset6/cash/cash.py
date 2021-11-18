from cs50 import get_float
"""Take a float input and return the fewest numbet of coins needed to make change
EX: If 0.51 is needed the result would be 3. 2 quarters (0.25) and one penny (0.01)"""

# promt user for positive float
while True:
    change = get_float("Change owed: ")
    if change > 0.0:
        break

# Keep track of coins
coins_due = 0

# Change change to int
change = change * 100

if change >= 25:
    quarters = int(change / 25)
    change = change - (quarters * 25)
    coins_due += quarters

if change >= 10:
    dimes = int(change / 10)
    print(dimes)
    change = change - (dimes * 10)
    coins_due += dimes
    print(change)
if change >= 5:
    nickels = int(change / 5)
    change = change - (nickels * 5)
    coins_due += nickels

if change > 0:
    pennies = int(change / 1)
    change = change - (pennies * 1)
    coins_due += pennies

print(coins_due)
