import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

time_of_first_sample = 912
average_sampling_period = 214

data = np.loadtxt('c:\data.csv', delimiter=',')

voltage = data[:,0] #read in the first column of array data
current = data[:,1] #read in the second column

x = np.arange(0, voltage.size*average_sampling_period, average_sampling_period) + time_of_first_sample
# first x value will be at the offset, then increases by average_delay up
# to the largest time (size of voltage * delay)

fig, ax = plt.subplots()
line, = ax.plot([], [], 'k-')  # black, solid line
ax.margins(0.05)

def init():
    line.set_data(x[:2],voltage[:2])
    return line,

def animate(i):
    win = 50 # about a 10 second window
    imin = min(max(0, i - win), x.size - win)
    xdata = x[imin:i]
    ydata = current[imin:i]
    line.set_data(xdata, ydata)
    ax.relim()
    ax.autoscale()
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init, interval=average_sampling_period)

plt.show()
