import string
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

# A Python program to print all  
# permutations using library function 
from itertools import permutations 

readfile()
# Get all permutations of [1, 2, 3] 
perm = permutations(string.ascii_lowercase,3) 
probofperms = []

# Obtain permutation probabilities and insert into array
for i in list(perm):
  permprob = probs[i[0]]
  for j in range (1,3):
    permprob += probs[i[j] + i[j-1]]
  
  probofperms.append([permprob, "".join(i)])
  #print("The probability of %s is %f" %(i, permprob))

#sort and print
print(max(probofperms)[1], max(probofperms)[0])

