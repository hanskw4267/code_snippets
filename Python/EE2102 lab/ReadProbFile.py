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
    probs[key] = float(val) # is bigram

readfile()

#accessing the probabilities
print("The probability of a is %f" %probs['a'])
print("The probability of zf is %f" %probs['zf'])