import matplotlib.pyplot as plt
import csv
import numpy as np
from scipy.interpolate import make_interp_spline, BSpline

def plot_graph(type):

    for i in range (4):
        x=[]
        y=[]

        if(i == 0):
            file = "./CSV/FIFO_"+type+".csv"
        elif(i == 1):
            file = "./CSV/LRU_"+type+".csv"
        elif(i == 2):
            file = "./CSV/LRU_APPROX_"+type+".csv"
        elif(i == 3):
            file = "./CSV/RANDOM_"+type+".csv" 

        with open(file, 'r') as csvfile:
            plots= csv.reader(csvfile, delimiter=',')
            for row in plots:
                x.append(float(row[0]))
                y.append(float(row[1]))
        
        x = np.array(x)
        y = np.array(y)

        x_new = np.linspace(x.min(), x.max(), 1000) 
        spl = make_interp_spline(x, y, k=3)
        y_smooth = spl(x_new)

        if(i == 0):
            plt.plot(x_new,y_smooth, color="orange", label="FIFO", linewidth=2)
        elif(i == 1):
            plt.plot(x_new,y_smooth, color="yellow", label="LRU", linewidth=2)
        elif(i == 2):
            plt.plot(x_new,y_smooth, color="green", label="LRU APPROX", linewidth=2)
        elif(i == 3):
            plt.plot(x_new,y_smooth, color="blue", label="RANDOM", linewidth=2)
    
    plt.title(type)

    plt.xlabel('Cache Size')
    plt.ylabel('Hit Rate(%)')
    plt.legend(loc='best')

    
    plt.savefig(type, dpi=450)
    plt.close()


plot_graph("LOCAL")
plot_graph("LOOP")
plot_graph("RAND")