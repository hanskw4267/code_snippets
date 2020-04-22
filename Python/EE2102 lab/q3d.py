import string
import math
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

print("      {0}  {1}\n------------------------" .format("Marginal", "Unigram"))
for each in (string.ascii_lowercase):
  temp = 0
  for each2 in (string.ascii_lowercase):
    temp += 2 ** probs[each+each2]
  print("p({2}) | {0:.3f}  |  {1:.3f}\n------------------------".format(math.log2(temp), probs[each], each))