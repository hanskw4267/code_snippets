from itertools import permutations 

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
perm = permutations(["k", "a", "t", "e"]) 
probofperms = []

# Obtain permutation probabilities and insert into array
for i in list(perm):
  permprob = probs[i[0]]
  for j in range (1,4):
    permprob += probs[i[j-1] + i[j]]
  probofperms.append([permprob, "".join(i)])
  print("The probability of %s is %f" %(i, permprob))

#sort and print
probofperms.sort()
for each in probofperms:
  print(each[1],each[0])

