import random
import sys

if len(sys.argv) != 2:
    sys.exit("Need to have at least 1 argument")

maximal_number = int(sys.argv[1])
number = random.randint(0, maximal_number)

while True:
    i = int(input("Guess the number ..."))
    if i < number:
        print("Too small ...")
    elif i > number:
        print("Too large ...")
    else:
        print("Correct")
        break
