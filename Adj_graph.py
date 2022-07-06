import matplotlib.pyplot as py
import numpy as np

x=[]
for i in range(0,5):
  element=float(input())
  x.append(element)
y=['Day 1','Day 2','Day 3','Day 4','Day 5']
py.plot(y,x)
py.title('Tme taken to do from source to destination in last 5 days')
py.ylabel('Time in minutes')
py.xlabel('Days ')
py.show()
py.savefig('graph_image.png')