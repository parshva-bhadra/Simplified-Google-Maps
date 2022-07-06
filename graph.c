#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "priority_queue.h"
#include "time.h"
double CalTime(double length, int cars)
{
    double speed;
    double time;

    if(cars == 0)
    {
        speed = 60;
    }
    else if(cars > 0 && cars <= 80)
    {
        speed = 60 - (0.5)*cars;
    }
    else
    {
        speed = 20;
    }
    time = (length/speed)*60;
    return time;
}

PtrAdjList CreateEmptyGraph(int degree)
{
    // A function to create an empty Adj List
    PtrAdjList G;
    G = (PtrAdjList)malloc(sizeof(AdjList));
    if (G == NULL)
    {
        printf("Memory full\n");
        exit(0);
    }
    G->degree = degree;
    G->vertex = malloc(degree * sizeof(Node));
    if (G->vertex == NULL)
    {
        printf("Memory full\n");
        exit(0);
    }
    // since array starts from 0 but our vertexid starts from 1 so vertexid becomes i+1
    for (int i = 0; i < degree; i++)
    {
        G->vertex[i].vertexid = i + 1;
        G->vertex[i].length = 0;
        G->vertex[i].cars = 0;
        G->vertex[i].time = 0;
        G->vertex[i].Next = NULL;
    }
    return G;
}

void InsertEdge(PtrAdjList G, int vertex1, int vertex2, double length, int cars)
{
    // function to add an edge
    PtrNode temp = G->vertex[vertex1 - 1].Next;
    int checking;
    while (temp != NULL)
    {
        checking = temp->vertexid;
        if (checking == vertex2)
        {
            printf("Edge already exist\n");
            return;
        }
        temp = temp->Next;
    }
    PtrNode add = (PtrNode)malloc(sizeof(Node));
    if (add == NULL)
    {
        printf("Memory full\n");
        exit(0);
    }
    // inserting at the front if it is not present
    // Directed Graph
    add->vertexid = vertex2;
    add->length = length;
    add->cars = cars;
    add->time = CalTime(length, cars);
    add->Next = G->vertex[vertex1 - 1].Next;
    G->vertex[vertex1 - 1].Next = add;
}

void UpdateDis(PtrAdjList G, int vertex1, int vertex2, double new_length)
{
    PtrNode Temp_add = G->vertex[vertex1 - 1].Next;
    while (Temp_add != NULL && Temp_add->vertexid != vertex2)
    {
        Temp_add = Temp_add->Next;
    }
    if (Temp_add == NULL)
    {
        printf("Edge does not exist\n");
    }
    else
    {
        Temp_add->length = new_length;
        Temp_add->time=CalTime(Temp_add->length,Temp_add->cars);
        printf("Successfully updated the length\n");
    }
}

void          UpdateCars(PtrAdjList G,int vertex1,int vertex2,int new_cars)
{
    PtrNode temp = G->vertex[vertex1 - 1].Next;
   
    L1 :

    if (temp != NULL && temp->vertexid != vertex2)
    {
        temp = temp->Next;
        goto L1;
    }

    if(temp==NULL)
    {
        printf("Edge doesn't Exist\n");
    }

    else 
    {
        temp->cars = new_cars;
        temp->time=CalTime(temp->length,temp->cars);
        printf("Sucessfully updated the number of cars\n");
    }
}

void DeleteEdge(PtrAdjList G, int vertex1, int vertex2)
{
    // function to delete an edge

    PtrNode temp = G->vertex[vertex1 - 1].Next;
    PtrNode prev=(&G->vertex[vertex1-1]);
    while ((temp != NULL) && (temp->vertexid!=vertex2))
    {
        prev=temp;
        temp=temp->Next;
    }
    if(temp==NULL)
        printf("Edge does not exist\n");
    else{
        prev->Next=temp->Next;
        free(temp);
        printf("Successfully deleted the edge\n");
    }
}

void PrintList(PtrAdjList G)
{
    // To print the Adj List
    int number = G->degree;
    for (int i = 0; i < number; i++)
    {
        PtrNode temp = G->vertex[i].Next;
        while (temp != NULL)
        {
            printf("vertex 1=%d and vertex 2 = %d\n", i + 1, temp->vertexid);
            printf("Distance between them is: %0.2f and cars present are %d and time taken to cross it is %0.2f \n", temp->length, temp->cars,temp->time);
            temp = temp->Next;
        }
        printf("\n");
    }
}

void Dijkstra_shortest_length(PtrAdjList G, double *distance_source, int *prev, int source)
{
    int *known;
    int n = G->degree;
    ptr_Minheap pq = create_empty_heap(n);
    pq->size = n;
    known = (int *)malloc((n + 1) * sizeof(int));
    known[source] = 0;
    distance_source[source] = 0;
    pq->position[source - 1] = 0;
    pq->Array[source - 1].vertex = source;
    pq->Array[source - 1].weight = 0;
    for (int i = 1; i <= n; i++)
    {
        prev[i]=-1;
        if (i!=source)
        {
            known[i] = 0;
            distance_source[i] = INF;
            pq->Array[i - 1].vertex = i;
            pq->Array[i - 1].weight = INF;
            pq->position[i - 1] = i - 1;
        }
    }
    MinHeapify(pq);
    while (pq->size > 0)
    {
        ptr_node_for_heap heap_node = ExtractMin(pq);
        known[heap_node->vertex] = 1;
        PtrNode temp = G->vertex[heap_node->vertex - 1].Next;
        // for all neighbours of u for whom SP is not known,
        // check if shorter path is available through u.
        while (temp != NULL)
        {
            int v = temp->vertexid;
            if ((!known[v]) && (distance_source[heap_node->vertex] + temp->length < distance_source[v]))
            {
                distance_source[v] = distance_source[heap_node->vertex] + temp->length; // Update dv
                prev[v]=heap_node->vertex;
                DecreaseKey(pq, v, distance_source[v]);
            }
            temp = temp->Next;
        }
        free(heap_node);
    }
    free(known);
    DeleteHeap(pq);
}
void print_shortest_path(int* prev,int source,int destination,Ptr_S Stack)
{
    Push(Stack,destination);
    while(prev[destination]!=source && source!=destination)
    {
        destination=prev[destination];
        Push(Stack,destination);
    }
    Push(Stack,source);
}
void Dijkstra_shortest_time(PtrAdjList G, double *time_source, int *prev, int source)
{
    int *known;
    int n = G->degree;
    ptr_Minheap pq = create_empty_heap(n);
    pq->size = n;
    known = (int *)malloc((n + 1) * sizeof(int));
    known[source] = 0;
    time_source[source] = 0;
    pq->position[source - 1] = 0;
    pq->Array[source - 1].vertex = source;
    pq->Array[source - 1].weight = 0;
    for (int i = 1; i <= n; i++)
    {
        prev[i]=-1;
        if (i!=source)
        {
            known[i] = 0;
            time_source[i] = INF;
            pq->Array[i - 1].vertex = i;
            pq->Array[i - 1].weight = INF;
            pq->position[i - 1] = i - 1;
        }
    }
    MinHeapify(pq);
    while (pq->size > 0)
    {
        ptr_node_for_heap heap_node = ExtractMin(pq);
        known[heap_node->vertex] = 1;
        PtrNode temp = G->vertex[heap_node->vertex - 1].Next;
        // for all neighbours of u for whom SP is not known,
        // check if shorter path is available through u.
        while (temp != NULL)
        {
            int v = temp->vertexid;
            if ((!known[v]) && (time_source[heap_node->vertex] + temp->time < time_source[v]))
            {
                time_source[v] = time_source[heap_node->vertex] + temp->time; // Update dv
                prev[v]=heap_node->vertex;
                DecreaseKey(pq, v, time_source[v]);
            }
            temp = temp->Next;
        }
        free(heap_node);
    }
    free(known);
    DeleteHeap(pq);
}
void print_shortes_time_path(int* prev,int source,int destination,Ptr_S Stack)
{
    Push(Stack,destination);
    while(prev[destination]!=source && source!=destination)
    {
        destination=prev[destination];
        Push(Stack,destination);
    }
    Push(Stack,source);
}
void shortest_distance_choice4(PtrAdjList graph,int source,int destination)
{
    int n=graph->degree;
    double* distance_source;
    int* prev;
    distance_source=(double*)malloc((n+1)*sizeof(double));
    prev=(int*)malloc((n+1)*sizeof(int));
    Dijkstra_shortest_length(graph,distance_source,prev,source);
    if(distance_source[destination]<INF)
    {    
        printf("The shortest distance between %d and %d is %0.2f\n",source,destination,distance_source[destination]);
        my_stack S=NULL;
        print_shortest_path(prev,source,destination,&S);
        printf("The path is \n");
        DisplayStack(S);
        printf("\n");
        DeleteStack(&S);
    }
    else{
        printf("path doesn't exist\n");
        printf("\n");
    }
    free(distance_source);
    free(prev);
}
void shortest_time_choice5(PtrAdjList graph,int source, int destination)
{
    int n=graph->degree;
    double* time_source;
    int* prev;
    time_source=(double*)malloc((n+1)*sizeof(double));
    prev=(int*)malloc((n+1)*sizeof(int));
    Dijkstra_shortest_time(graph,time_source,prev,source);
    if(time_source[destination]<INF)
    {    
        printf("The least time between %d and %d is %0.2f\n",source,destination,time_source[destination]);
        my_stack S=NULL;
        print_shortest_path(prev,source,destination,&S);
        printf("The path is \n");
        DisplayStack(S);
        printf("\n");
        DeleteStack(&S);
    }
    else{
        printf("path doesn't exist\n");
        printf("\n");
    }
    free(time_source);
    free(prev);
}
// safe path begins here
int UpdateTime(PtrAdjList G,int vertex1,int vertex2,double new_time)
{
    PtrNode Temp_add = G->vertex[vertex1 - 1].Next;
    while (Temp_add != NULL && Temp_add->vertexid != vertex2)
    {
        Temp_add = Temp_add->Next;
    }
    if (Temp_add == NULL)
    {
        return 0;
    }
    else
    {
        Temp_add->time=new_time;
        return 1;
    }
}
double absolute_fraction(double a,double b)
{
    if((a-b)>0)
        return (a-b)/a;
    else
        return (b-a)/a;
}
double absolute_difference(double a,double b)
{
    if((a-b)>0)
        return (a-b);
    else
        return (b-a);
}
double TimeAccToFluc(timeNode* storage)
{
    double average=storage->avgtime;
    for(int i=0;i<5;i++)
    {
        double deviation=absolute_fraction(storage->time[i],average)*100;
        double difference=absolute_difference(storage->time[i],average);
        if(deviation>25 && difference>2.5)
        {
            return INF;
        }
    }
    return average;
}
void RevertToNormalcy(PtrAdjList G)
{
    // To print the Adj List
    int number = G->degree;
    for (int i = 0; i < number; i++)
    {
        PtrNode temp = G->vertex[i].Next;
        while (temp != NULL)
        {
            temp->time=CalTime(temp->length,temp->cars);
            temp = temp->Next;
        }
    }
}
void Dijkstra_time_safepath(timeHistoryTable* T,double* time_source,int* prev,int source)
{
    int *known;
    int n = T->no_of_vertices;
    ptr_Minheap pq = create_empty_heap(n);
    pq->size = n;
    known = (int *)malloc((n + 1) * sizeof(int));
    known[source] = 0;
    time_source[source] = 0;
    pq->position[source - 1] = 0;
    pq->Array[source - 1].vertex = source;
    pq->Array[source - 1].weight = 0;
    for (int i = 1; i <= n; i++)
    {
        prev[i]=-1;
        if (i!=source)
        {
            known[i] = 0;
            time_source[i] = INF;
            pq->Array[i - 1].vertex = i;
            pq->Array[i - 1].weight = INF;
            pq->position[i - 1] = i - 1;
        }
    }
    MinHeapify(pq);
    while (pq->size > 0)
    {
        ptr_node_for_heap heap_node = ExtractMin(pq);
        known[heap_node->vertex] = 1;
        timeNode* temp = T->tpointer[heap_node->vertex - 1]->timeNext;
        // for all neighbours of u for whom SP is not known,
        // check if shorter path is available through u.
        while (temp != NULL)
        {
            int v = temp->vertexid;
            if ((!known[v]) && (time_source[heap_node->vertex] + temp->avgtime < time_source[v]))
            {
                time_source[v] = time_source[heap_node->vertex] + temp->avgtime; // Update dv
                prev[v]=heap_node->vertex;
                DecreaseKey(pq, v, time_source[v]);
            }
            temp = temp->timeNext;
        }
        free(heap_node);
    }
    free(known);
    DeleteHeap(pq);
}
void get_data(timeHistoryTable* T,int source, int destination,double* d1,double* d2,double* d3,double* d4,double* d5)
{
    timeNode* temp=T->tpointer[source-1]->timeNext;
    while(temp->vertexid!=destination)
    {
        temp=temp->timeNext;
    }
    (*d1)+=temp->time[0];
    (*d2)+=temp->time[1];
    (*d3)+=temp->time[2];
    (*d4)+=temp->time[3];
    (*d5)+=temp->time[4];
}
void pass_data_AdjList(timeHistoryTable* T,my_stack Stack,double A[])
{
    double d1=0,d2=0,d3=0,d4=0,d5=0;
    int destination=0;
    int source=0;
    if(Stack!=NULL)
    {
        source=Stack->x;
        Stack=Stack->next;
    }
    while(Stack!=NULL)
    {
        destination=Stack->x;
        get_data(T,source,destination,&d1,&d2,&d3,&d4,&d5);
        Stack=Stack->next;
        source=destination;
    }
    A[0]=d1;
    A[1]=d2;
    A[2]=d3;
    A[3]=d4;
    A[4]=d5;
}
void SafeAlgorithmStart(timeHistoryTable* T,PtrAdjList G,int source,int destination)
{
    if(T->no_of_vertices!=G->degree || source==destination)
    {
        printf("There is some data inconsistency \n");
        return;
    }
    else
    {
        int n=T->no_of_vertices;
        for(int i=0;i<n;i++)
        {
            timeNode* temp=T->tpointer[i]->timeNext;
            while(temp!=NULL)
            {
                int y;
                double time_added=TimeAccToFluc(temp);
                y=UpdateTime(G,i+1,temp->vertexid,time_added);
                if(y==0)
                {
                    printf("Data Inconsistency detected\n");
                    return;
                }
                temp=temp->timeNext;
            }
        }
        // The Adjancy List has been updated with the new time
        double* time_source;
        int* prev;
        time_source=(double* )malloc(sizeof(double)*(n+1));
        prev=(int* )malloc(sizeof(double)*(n+1));
        Dijkstra_shortest_time(G,time_source,prev,source);
        if(time_source[destination]>=INF)
        {
            double* avg_time_source;
            int* prev_avg;
            avg_time_source=(double* )malloc(sizeof(double)*(n+1));
            prev_avg=(int* )malloc(sizeof(double)*(n+1));
            printf("There is no safe path for this destination\n");
            Dijkstra_time_safepath(T,avg_time_source,prev_avg,source);
            // something else a new Dijkstra that has to be implemented on T
            // reason for implementing it on T is that it will save us time that we take to Update time
            // which turns on to be greater than n^2
            // worst case n^3
            // The nearest safest path 
            if(avg_time_source[destination]>=INF)
            {
                printf("Actually there is no path between the %d and %d in your city\n",source,destination);
            }
            else{
                my_stack Stack=NULL;
                double A[5];
                printf("The nearest safest path based only on avgerage time is %0.2f\n",avg_time_source[destination]);
                print_shortes_time_path(prev_avg,source,destination,&Stack);
                DisplayStack(Stack);
                pass_data_AdjList(T,Stack,A);
                for(int i=0;i<5;i++)
                {
                    printf("%0.2f ",A[i]);
                }
                printf("\n");
                DeleteStack(&Stack);
            }
            free(avg_time_source);
            free(prev_avg);
        }
        else{
            my_stack S=NULL;
            double A[5];
            printf("minimum total time is %0.2f \n",time_source[destination]);
            print_shortes_time_path(prev,source,destination,&S);
            DisplayStack(S);
            pass_data_AdjList(T,S,A);
            for(int i=0;i<5;i++)
            {
                printf("%0.2f ",A[i]);
            }
            printf("\n");
            DeleteStack(&S);
        }
        free(time_source);
        free(prev);
    }
    RevertToNormalcy(G);
}
void          DeleteList(PtrAdjList G)
{
    int i;
    PtrNode Curr,Next_node;
    for(i=0;i<G->degree;i++)
    {
        Curr = G->vertex[i].Next;
        while (Curr != NULL)
        {
            Next_node = Curr->Next;
            free(Curr);
            Curr = Next_node;
        }
    }
    free(G->vertex);
    free(G);
}
