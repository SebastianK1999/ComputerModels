import sys
import numpy as np
import matplotlib.pyplot as plt

"""
    patrząc na implementację rand jestem w szoku że to w ogóle działa
    widać tam fakt ze jest to tak naprawdę pewien ciąg,
    gdzie poprzedni seed mnożony jest przez pewną stałą i dodawanna inna stała
    następnie by wygenerować liczbę seed jest przesuwany 16 bitów w prawo
    i nakładana jest maska 0x7fff (== 32767 == RAND_MAX)
    w ten sposób wycinamy "przypadkowe" bity i liczba nie powinna być
    bezpośrodnio związana z seedem

    mt19937 jest bardziej zaawansownym i dokładnym generatorem
    co widać na wykresach, wszystkie liczby były mniej więcej tyle samo razy wygenerowane
    gdzie w przypadku rand() niektóre są losowanie rzadziej niż pozostałe

    mt19937 Merser Twister - algorytm działa na posdtawie liczby pierwszej mersena równej 2^19937 - 1
    liczba ta jest okresem po jakim liczy zaczną się powtażać. jest to ogramna liczba i została udowodnina za prawdziwą
    generator jest szybki i poprawia przwidywalnośc genartora rand()

    często jako seed genaratora używa się geanartaora random_device ten genartor ma być "prawdziwie przypadkowy"
    niestety działa wolno a garator mt jest szybszy i nie daje znacznie gorszych wyników.
    z tego co mi wiodomo, jeszcze nie udowodnino matematycznie aby geneartor random_device był deterministyczny
    jednak z powodu wolnego działania i braku seeda nie zawsze można go wykożystywać

"""

i,c_rand,mt_rand = np.loadtxt("randData.txt", unpack=True)
plt.scatter(i,c_rand, label="rand()")
plt.scatter(i,mt_rand, label="std::mt19937")

plt.title("random generator comparasion")
plt.xlabel("Number")
plt.ylabel("Occurence count")
plt.legend()    
plt.show()