import os
import sys
import glob
import numpy as np
import matplotlib.pyplot as plt

# usage - <program name> <directory name>

"""
    gdy już raz zarażone osoby nie mogą się zarazić ponownie, R to liczba brakująca S do ilosći całej populacji.
    I to pochodna R

    gedy ozdrowiłe komórki mogą zachorować jeszcze raz zachorowania i ozdrowienia oscyluja w okół jakijś stabilnej wartości

    na wyniki pływają takrze czas życia i gęstość, jak i elementy przypadkowe.
    z tego powodu wyniki te nie są dokładne, gdyżą samo prawdopodobieństo zarażenia ma za mały wpływ na symulację by przy jednej dało się zobaczyć ogólne zachowania

    jednak da sie zauważyć parę ciekawych zjawisk, tak jak ogniska, możliwość wygaśnięcia epidemi samej z siebie, jak dystans ma wpływ na rozprzestrzenianie się

    moje wykresy przypominają te tóre znlazłem w literaturze
"""

data = {}

os.chdir(sys.argv[1])
for file in glob.glob("*.txt"):
    s, i, r = np.loadtxt(file, unpack=True)
    data[file] = {"s":s, "i":i, "r":r}

for file, sir in data.items():
    s = sir["s"]
    plt.plot(range(len(s)), s, label=file)
    plt.title("susceptible")
    plt.xlabel("time")
    plt.ylabel("count")

#plt.xscale("log")
#plt.yscale("log")
plt.legend()    
plt.show()

for file, sir in data.items():
    i = sir["i"]
    plt.plot(range(len(i)), i, label=file)
    plt.title("infected")
    plt.xlabel("time")
    plt.ylabel("count")

#plt.xscale("log")
#plt.yscale("log")
plt.legend()    
plt.show()

for file, sir in data.items():
    r = sir["r"]
    plt.plot(range(len(r)), r, label=file)
    plt.title("recovered")
    plt.xlabel("time")
    plt.ylabel("count")

#plt.xscale("log")
#plt.yscale("log")
plt.legend()    
plt.show()




