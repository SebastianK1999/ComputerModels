import sys
import numpy as np
import matplotlib.pyplot as plt

# usage - <program name> <file name>

"""
"""


plants, preys, predators = np.loadtxt(sys.argv[1], unpack=True)

plt.plot(range(len(plants)), plants, "g-", label="plants")
plt.plot(range(len(preys)), preys, "b-", label="preys")
plt.plot(range(len(predators)), predators, "r-", label="predators")
#plt.plot(t, t**(1.75), "b-", label="N**(1.74)")
plt.title("enciroment simulation")
plt.xlabel("time")
plt.ylabel("count")



#plt.xscale("log")
#plt.yscale("log")



plt.legend()    
plt.show()