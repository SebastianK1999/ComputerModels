import sys
import numpy as np
import matplotlib.pyplot as plt

"""
    współczynnik dyfuzji rośnie gdy dziesko może przebyć większy dystans w krótszym czasie
"""





x, x2, srx2 = np.loadtxt('walks/shift_%sD.txt'%(sys.argv[1]), unpack=True)
x_diagonal, x2_diagonal, srx2_diagonal = np.loadtxt('walks/shift_%sD_diagonal.txt'%(sys.argv[1]), unpack=True)
plt.title("%sD diffusion"%(sys.argv[1]))
plt.xlabel("X")
plt.ylabel("Y")
plt.plot(range(len(x)), x2, label="x**2")
plt.plot(range(len(x)), x2_diagonal, label="x**2  diagonal")
print(type(x2), type(x2[0]))
print("%sD %s directions diffusion ="%(sys.argv[1], 2 * int(sys.argv[1]))   , sum( [x2[i]/i for i in range(1,len(x2))] ) / len(x2) / (2*int(sys.argv[1])), 1 /(2*int(sys.argv[1])))
print("%sD %s directions diffusion ="%(sys.argv[1], 3**int(sys.argv[1]) - 1), sum( [ x2_diagonal[i]/i for i in range(1,len(x2))] ) / len(x2) / (2*int(sys.argv[1])), (1+np.sqrt(2))/int(sys.argv[1]) / (2*int(sys.argv[1])))
plt.legend()    
plt.show()

plt.title("%sD diffusion"%(sys.argv[1]))
plt.xlabel("X")
plt.ylabel("Y")
plt.plot(range(len(x)), srx2, label="sqrt(x**2)")
plt.plot(range(len(x)), x,  label="pitagoras")
plt.plot(range(len(x)), srx2_diagonal, label="sqrt(x**2) diagonal")
plt.plot(range(len(x)), x_diagonal,  label="pitagoras diagonal")

plt.legend()    
plt.show()