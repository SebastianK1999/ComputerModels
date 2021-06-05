import sys
import numpy as np
import matplotlib.pyplot as plt
from numpy.lib import median

def printCount(dictionary, index):
    try:
        print("index",index,"=",dictionary[index])
    except:
        print("index",index,"has no values")


def gauss(data, passLines=False):
    mean = sum([ k*v for k, v in data.items()])/sum(data.values())
    mse = sum([v*(k - mean)**2 for k, v in data.items()])/sum(data.values())
    rmse = np.sqrt(mse)
    mx = max([ v for k, v in data.items()])
    med = np.median([ k*v for k, v in data.items()])
    xMedian = np.median(tuple(data.keys()))


    #ret = [ (mx * np.exp( -((x - xMedian)**2) / (2*mse) )) / (rmse*np.sqrt(2*np.pi)) for x in data.keys()]
    ret = [ (mx * np.exp( -(((x - xMedian))**2)/(2*mse)  )) for x in data.keys()]
    if not passLines:
        print("the chid is around",3*rmse)
        plt.plot([3*rmse,3*rmse], [0,sum(data.values())/10], "g-o")
        plt.plot([-3*rmse,-3*rmse], [0,sum(data.values())/10], "g-o", label="3 sigma")
    return ret

def gaussCircle2D(dataX, dataY):
    meanX = sum([ k*v for k, v in dataX.items()])/sum(dataX.values())
    mseX = sum([v*(k - meanX)**2 for k, v in dataX.items()])/sum(dataX.values())
    rmseX = np.sqrt(mseX)

    meanY = sum([ k*v for k, v in dataY.items()])/sum(dataY.values())
    mseY = sum([v*(k - meanY)**2 for k, v in dataY.items()])/sum(dataY.values())
    rmseY = np.sqrt(mseY)

    plt.plot(dataX.keys(), gauss(dataX, passLines=True), "aqua", label="normal dist. X")
    plt.plot(gauss(dataY, passLines=True), dataY.keys(), "cyan", label="normal dist. Y")

    print("the chid is around |X|",3*rmseX)
    print("the chid is around |Y|",3*rmseY)
    theta = np.linspace(-np.pi, np.pi, 200)
    plt.plot(np.sin(theta)*3*rmseX, np.cos(theta)*3*rmseY, "g-", label="3 sigma")
    #plt.plot([3*rmse,3*rmse], [0,sum(dataX.values())/10], "g-o")
    #plt.plot([-3*rmse,-3*rmse], [0,sum(dataX.values())/10], "g-o")


if(sys.argv[1] == "1"):
    x = np.loadtxt('walks/endOfWalks_1D.txt', unpack=True)
    plt.scatter(x, range(0,len(x)), marker="x")
    
    valCount = dict()
    for pos in x:
        if pos in valCount:
            valCount[pos] += 10
        else:
            valCount[pos] = 0
    valCount = {k: v for k, v in sorted(valCount.items(), key=lambda item: item[0])}
    
    printCount(valCount,1)
    printCount(valCount,30)

    plt.plot(valCount.keys(), gauss(valCount), "cyan", label="normal dist.")
    plt.plot(valCount.keys(), valCount.values(), "r-", label="dist.")
    plt.title("1D random walk ends")
    plt.xlabel("X")
    plt.ylabel("child")
    """
        #1D
        bradziej prawdopodobne jest to że dziecko będzie blisko miejsca gdzie się zgubiło
        patrząc na przykłady z 1 krokiem i 30
        to większe prawdopodobieństwo jest że będzie w odległości 1 niż 30 
        jednak wykres rozkładu w 30 krokach jeszcze nie jest na samym dole i 
        prawdopodobieństwo że tam znajdzie się dziecko jest dalej wyskokie  
  
        odległością za jaką można uznać że dziecko nie przekroczy
        jest "3*sigma" gdzie sigma to odchylenie standardowe 
        końcowych pozycji dzieci. 3*sigma daje nam prawdopodobieństwo równe 99.7%
        że dziecko znajdzie się w tej odległości. oczywiście ta odległość
        nie zapewnia nam że dziecko nie może być już dalej, ale daje nam dużą przewagę 
        w znaleźienu dziecka niż mieli byśmy przeszukiwać caly zakres 1000 kroków. 
        Co też jest jednak możliwe żeby dziecko szło cały czas prosto.
        jednak fakt że jest zagubione i nie wie gdzie isć sprawia że 
        w pewien sosób krąży wokół miejsca startu.
        Im dłużej chodzi jednak tym dalej może się oddalić    

        Wartość graniczna to 94.8 kroków
    """


if(sys.argv[1] == "2"):
    x, y = np.loadtxt('walks/endOfWalks_2D.txt', unpack=True)
    plt.scatter(x, y, marker="x")

    valCountX = dict()
    valCountY = dict()
    populationScale = max(x)/(len(x)/50)
    for pos in x:
        if pos in valCountX:
            valCountX[pos] += populationScale
        else:
            valCountX[pos] = 0

    for pos in y:
        if pos in valCountY:
            valCountY[pos] += populationScale
        else:
            valCountY[pos] = 0

    valCountX = {k: v for k, v in sorted(valCountX.items(), key=lambda item: item[0])}
    valCountY = {k: v for k, v in sorted(valCountY.items(), key=lambda item: item[0])}
    gaussCircle2D(valCountX, valCountY)
    plt.plot(valCountX.keys(), valCountX.values(), "crimson", label="dist. X")
    plt.plot(valCountY.values(), valCountY.keys(), "deeppink", label="dist. Y")
    plt.axis('equal')
    plt.title("2D random walk ends")
    plt.xlabel("X")
    plt.ylabel("Y")
    """
        #2D
        jak w przypadku 1D, prawdopodobnie dziecko też nie oddali się
        dalej niż na pewną odległość. Wiadć wyraźny promień,
        w którym dziecko może się znaleźć.

        w tej analiźie zbadałem osobno przemieszczenie x i y
        następnie wyniki obu wykorzystałem do narysowania elipesy
        w której polu dziecko może się znaleźć

        wartośc graniczna dla X i Y wynosi 65.4 z małą różnicą
        po liczbach dzieiętnych. Mimo że statystycznie dziecko
        wykonuje połowę ruchów w tyko jednym kieruku to wartość
        graniczna nie jest o połowe mniejsza a wynosi około 2/3 

        porównałem tą wartość dla 1D 500 kroków, tam odchyleniem granicznym było 66.7
        zależność ta wydaje mi się być związana z zadaniem 6 na tej liście

    """


plt.legend()    
plt.show()