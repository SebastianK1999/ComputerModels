import sys
import numpy as np
import matplotlib.pyplot as plt

"""
    prawdopodobieśtwo że dziecko wróci na swoje miejsce zmienia się z czsem spaceru,
    gdyż diecko ma więcej czasu by się oddalić.
    charakterystyka wykresu przypomina hiperbolę (nie uwzględniając dziur)
    jest to wynik tego że w każdym kolejnym ruch wybieramy 1 z 2*D sąsiadów
    każde oddalenie sie zmniejsza prawdopodobieństwo że dzicko wróci na swoje miejsce, 
    jednak dzicko po znacznym oddalenu dalej ma szansę wrócić na piejsce 

    jak już wcześniej wpomniałem wybieramy 1 z 2*D sąsiadów,
    także przy większej ilości wymiarów prawdopodobieśtwo że,
    dziecko wybierze odpowiedniego sąsiada maleje,
    więc w raz z tym prawdopodobieństwo powrotu na miejsce.
    dziecko ma poprostu więdzy wybór gdzie iść więc może się zgumić na więcej sposobów
"""

x = np.loadtxt('walks/backTostartCount_%sD.txt'%(sys.argv[1]), unpack=True)
l = len(x)
s = sum(x)

#plt.scatter(range(l), x)

prob_ver = 0
if prob_ver == 0:
    prob = [xx / 100000  for xx in x] # per step
elif prob_ver == 1:
    prob = [xx / s for xx in x] # trough walk

plt.plot(range(l), prob, "r-")
plt.title("%sD random walk"%(sys.argv[1]))
plt.xlabel("time")
plt.ylabel("X")

plt.xscale("log")
plt.yscale("log")



plt.legend()    
plt.show()