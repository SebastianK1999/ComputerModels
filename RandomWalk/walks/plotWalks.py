import sys
import numpy as np
import matplotlib.pyplot as plt

"""
    dzieći są nie przewidywalne
    można się ich bać
"""

if(sys.argv[1] == "1"):
    for i in range(int(sys.argv[2])):
        x = np.loadtxt('walks/1D/walk(%s).txt'%(i), unpack=True)
        plt.plot(*x)
    plt.title("1D random walk")
    plt.xlabel("time")
    plt.ylabel("X")
        
elif(sys.argv[1] == "2"):
    for i in range(int(sys.argv[2])):
        x, y = np.loadtxt('walks/2D/walk(%s).txt'%(i), unpack=True)
        plt.plot(x, y)
    plt.title("2D random walk")
    plt.xlabel("X")
    plt.ylabel("Y")

plt.legend()    
plt.show()