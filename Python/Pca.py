from numpy import array
from numpy import mean
from numpy import cov
from numpy.linalg import eig
import pandas as pd

A = array([[1, 9], [3, 4], [5, 6]])
print(A)
M = mean(A.T, axis = 1)
print("M")
print(M)
C = A -M
print("C")
print(C)
V = cov(C.T)
print("V")
print(V)
values, vectors = eig(V)
print("Vectors")
print(vectors)
print("Values")
print(values)
P = vectors.T.dot(C.T)
print("P.T")
print(P.T)
print(P.plot())