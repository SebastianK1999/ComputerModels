import sys
import numpy as np
import matplotlib.pyplot as plt

# usage - <program name> <file name>

"""
"""


s, i, r = np.loadtxt(sys.argv[1], unpack=True)

plt.plot(range(len(s)), s, "b-", label="sus")
plt.plot(range(len(s)), i, "r-", label="inf")
plt.plot(range(len(s)), r, "g-", label="rec")
#plt.plot(t, t**(1.75), "b-", label="N**(1.74)")
plt.title("population " + sys.argv[1])
plt.xlabel("time")
plt.ylabel("count")



#plt.xscale("log")
#plt.yscale("log")



plt.legend()    
plt.show()