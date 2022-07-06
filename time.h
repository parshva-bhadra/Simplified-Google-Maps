#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DONTCARE 0

// these functions stores the previous
// five time values from previous 5 inputs

// the input taken should be like
// feed us yhe previous 5 days data
// for each edge

// the user will give five situations for
// each edge. If he wants to give same
// data as privious day then he should have
// the option as well

typedef struct timeNode timeNode;
typedef struct timeHistoryTable timeHistoryTable;

struct timeHistoryTable
{
    int no_of_vertices;
    timeNode **tpointer;
};

struct timeNode
{
    int vertexid;
    double time[5];
    double avgtime;
    timeNode *timeNext;
};

timeHistoryTable *createEmptyTimeHistoryTable(int N);
timeNode* makeTimeNode(double t1, double t2, double t3, double t4, double t5, int v);
int isEdge(PtrAdjList G, int u, int v);
int timeDataAlreadyExists(timeHistoryTable* T,int u,int v);
void addTimeNode(PtrAdjList G, timeHistoryTable* T, int u, double t1, double t2, double t3, double t4, double t5, int v); // u to v
void printTimeHistoryTable(timeHistoryTable* T);
void deleteMemoryOfTable(timeHistoryTable *T);
void SafeAlgorithmStart(timeHistoryTable* T,PtrAdjList G,int source,int destination);

// in main.c file it would look something like
// enter data for this edge for previous days:
// 5 times scanf in a while loop(loop traverses through edges)
// take time from each entry and then use this functions 
// to store the data