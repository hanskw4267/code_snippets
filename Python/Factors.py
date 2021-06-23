x = 48
factors = []
for y in range(2, x):
    print("checking if y = {}, is a factor of {}" .format(y, x))
    if x % y == 0:
        factors.append(y)
        print("{} is a factor of {}\n" .format(y, x))
    else:
        print("{} is not a factor of {}\n" .format(y, x))
print("the factors of {} are {}\n" .format(x, factors))
print("numbers checked are {}" .format(range(2,x)))