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

enthropy = 0
equalenthropy = 0
eachprob = float(1/26)
for each in string.ascii_lowercase:
  enthropy += 2**probs[each] * probs[each]
  equalenthropy +=  eachprob * math.log2(eachprob)
print("Entropy (bits required) = {0:.0f}" .format(-enthropy))
print("Entropy (bits required) if all equal = {0:.0f}" .format(-equalenthropy))
