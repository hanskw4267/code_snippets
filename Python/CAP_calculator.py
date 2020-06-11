"""
Cumulative CAP calculator.

Calculates your cumulative CAP by reading grades from a text file.

Create a text file with 2 columns of numbers x, y where
x is the Module Credits and
y is the letter grade of the module (non-casesensitive)
Example:
4 a+
2 B-
"""

filepath = "./inputs/results.txt" # change this path to point to your txt file

conversion = {
  "A+" : 5,
  "A" : 5,
  "A-" : 4.5,
  "B+" : 4,
  "B" : 3.5,
  "B-" : 3,
  "C+" : 2.5,
  "C" : 2,
  "D+" : 1.5,
  "D" : 1,
  "F" : 0,
}

results = open(filepath, "r")

grades = {}

sum_mc = 0
sum_cap = 0

for i in results:
  mc, grade = i.split()
  mc = int(mc)
  grade = conversion[grade.upper()]
  sum_cap = sum_cap + (grade * mc)
  sum_mc = sum_mc + mc

print("Total CAP: {}  Total MCs: {}" .format(sum_cap, sum_mc))
print("Cumulative CAP: {:0.2f}" .format(sum_cap/sum_mc))
