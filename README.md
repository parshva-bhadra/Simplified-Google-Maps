***
## ROUTING
***
Routing is the project that we, **_Group-29_** have worked upon for our DSA mini-project.
***
### IDEALOGY
***
We try to make a program that helps users to find the safest and shortest time consuming path from one place(a node) in the city to other place(another node) in the city(graph).<br />
We made a graph(as a representation of city) with roads as edges and their weights as length(length of road), cars(number of cars) and devised a simple formula to calculate time taken to move through a road in relation with the number of cars on the road.<br />
We use Dijkstra's Algorithm for finding the shortest path, twice in the safest path, shortest time.<br />
So total 4 times in worst case scenario, where we call Dijkstra's once if there's no shortest path and again for next shortest path.<br />
We have also taken the time data from user for the last 5 days and stored in a Adjacency list.<br />
Safest path was found using time taken data for the previous 5 days of the week.<br />
Assumption in safest path algo:- If the data shows variation of more than 25% then we remove that edge between those 2 vertices else we use the average time for that particular edge.<br />
if we run the program and the time comes > 123456 then we run Dijkstra's algorithm again but this time we use average time from the last 5 days as given by user.<br />
If still we get answer greater than 123456 that means there is no path between those 2 vertices.<br />
***
### COMPILATION AND RUNNING
***
for running main code-
```gcc mainmenu.c graph.c time.c priority_queue.c``` 
for seeing graph in python- 
```python3.8 Adj_graph.py``` 
and enter those 5 float number manually or by using redirector operator
for seeing our report click on analysis.txt
***
### GROUP MEMBERS
***
|Serial no|Roll number  | NAME           | 
|-----    |------       |------          |
|   1     |2020100001   |Parshva Bhadra  | 
|   2     |2020101052   |Aditya Malhotra |  
|   3     |2020102052   |Karnati Jahnavi |
|   4     |2020112012   |Anubhav Pal     |
|   5     |2020115008   |Aaryan Sharma   |
