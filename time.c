#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "time.h"

// this function stores the previous
// five time values from previous 5 inputs

timeHistoryTable *createEmptyTimeHistoryTable(int N)
{
    if (N <= 0)
    {
        return NULL;
    }

    timeHistoryTable *T = (timeHistoryTable *)malloc(sizeof(timeHistoryTable));
    assert(T != NULL);

    T->no_of_vertices = N;
    T->tpointer = (timeNode **)malloc(N * sizeof(timeNode *));
    assert(T->tpointer != NULL);

    for (int i = 0; i < N; i++)
    {
        T->tpointer[i] = (timeNode *)malloc(sizeof(timeNode));
        assert(T->tpointer[i] != NULL);

        T->tpointer[i]->vertexid = i + 1;
        T->tpointer[i]->avgtime = DONTCARE;

        for (int j = 0; j < 5; j++)
            T->tpointer[i]->time[j] = DONTCARE;
        T->tpointer[i]->timeNext = NULL;
    }

    return T;
}

timeNode *makeTimeNode(double t1, double t2, double t3, double t4, double t5, int v)
{
    timeNode *tn = (timeNode *)malloc(sizeof(timeNode));
    assert(tn != NULL);

    tn->vertexid = v;
    tn->time[0] = t1;
    tn->time[1] = t2;
    tn->time[2] = t3;
    tn->time[3] = t4;
    tn->time[4] = t5;

    tn->avgtime = 0;
    for (int i = 0; i < 5; i++)
    {
        tn->avgtime = tn->avgtime + tn->time[i];
    }
    tn->avgtime = tn->avgtime / 5;

    tn->timeNext = NULL;

    return tn;
}

//a function to check if there is an edge from u to v
int isEdge(PtrAdjList G, int u, int v)
{
    PtrNode temp = G->vertex[u - 1].Next;

    while (temp != NULL && temp->vertexid != v)
    {
        temp = temp->Next;
    }

    if (temp == NULL)
        return 0;
    else
        return 1;
}

// function to prevent duplicates/multiple datas between two nodes
int timeDataAlreadyExists(timeHistoryTable *T, int u, int v)
{
    timeNode *temp = T->tpointer[u - 1]->timeNext;

    while (temp != NULL && temp->vertexid != v)
    {
        temp = temp->timeNext;
    }

    if (temp == NULL)
        return 0;
    else
        return 1;
}

//from u to v
void addTimeNode(PtrAdjList G, timeHistoryTable *T, int u, double t1, double t2, double t3, double t4, double t5, int v)
{

    if (isEdge(G, u, v) == 1)
    {
        timeNode *tn = makeTimeNode(t1, t2, t3, t4, t5, v);

        if (timeDataAlreadyExists(T, u, v) == 1)
        {
            printf("\nError: A time history data already exists from u to v\n");
            return;
        }
        else
        {
            tn->timeNext = T->tpointer[u - 1]->timeNext;
            T->tpointer[u - 1]->timeNext = tn;
        }
    }
    else
    {
        printf("\nError: There is no edge from u to v\n");
    }
    return;
}

// function to print the time history table
void printTimeHistoryTable(timeHistoryTable *T)
{
    if (T == NULL)
    {
        printf("\nError: time history table does not exist\n");
        return;
    }
    for (int i = 0; i < T->no_of_vertices; i++)
    {
        timeNode *temp = T->tpointer[i]->timeNext;
        printf("%d", i + 1);
        while (temp != NULL)
        {
            printf("==> %d ; %.2f,%.2f,%.2f,%.2f,%.2f,%.2f", temp->vertexid, temp->time[0], temp->time[1], temp->time[2], temp->time[3], temp->time[4], temp->avgtime);
            temp = temp->timeNext;
        }
        printf("==> NULL\n");
    }
    return;
}

void deleteMemoryOfTable(timeHistoryTable *T)
{
    timeNode* temp_curr,*temp_next;
    
    for(int i=0; i < T->no_of_vertices; i++)
    {
        temp_curr = T->tpointer[i];
        
        while (temp_curr != NULL)
        {
            temp_next = temp_curr->timeNext;
            free(temp_curr);
            temp_curr = temp_next;
        }
    }
    free(T->tpointer);
    free(T);
}