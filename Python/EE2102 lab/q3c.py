import string
import matplotlib.pyplot as plt
#dictionaries to store probabilities
probs = {}

#read probabilities database file
def readfile():
  #open database
  database = open("database.txt", "r")
  
  for line in database:
    if len(line.split()) != 2: # not interested in this line
      continue

    (key, val) = line.split() # get key and value pair
    probs[key] = float(val)

readfile()

pmf = []
names = []
totalpmf = 0

for each in (string.ascii_lowercase):
  temp = 2 ** probs[each]
  pmf.append(temp)
  names.append(each)
  totalpmf += temp

txtstr = "+".join(names) + " = " + str(totalpmf)
plt.bar(names, pmf)
plt.suptitle("PMF\n" + txtstr)
plt.show()
