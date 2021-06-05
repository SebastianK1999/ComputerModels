import sys
import numpy as np
import plotly.express as px

if(sys.argv[1] == "1"):
    time, x,= np.loadtxt('walks/1D/walk(%s).txt'%(sys.argv[2]), unpack=True)
    fig = px.scatter(x=time, y=x, color=time)

elif(sys.argv[1] == "2"):
    x, y = np.loadtxt('walks/2D/walk(%s).txt'%(sys.argv[2]), unpack=True)
    fig = px.scatter(x=x, y=y, color=range(len(x)))

elif(sys.argv[1] == "3"):
    x, y, z = np.loadtxt('walks/3D/walk(%s).txt'%(sys.argv[2]), unpack=True)
    fig = px.scatter_3d(x=x, y=y, z=z, color=range(len(x)))

fig.write_html("wylkresy i inne/5/%sD/plot%s.html"%(sys.argv[1], sys.argv[2]))
fig.show()
