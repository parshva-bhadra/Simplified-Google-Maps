#ifndef __PQUEUE_H
#define __PQUEUE_H

// Both priority and stacks
typedef struct node List;
typedef struct node* my_stack;
typedef my_stack* Ptr_S;
struct node{
    int x;
    struct node* next;
};
void Push(Ptr_S S,int x);
void Pop(Ptr_S S);
void DeleteStack(Ptr_S S);
void DisplayStack(my_stack S);

typedef struct vertex_dis_for_heap *ptr_node_for_heap;
typedef struct vertex_dis_for_heap vertex_dis_for_heap;
typedef struct Minheap *ptr_Minheap;
typedef struct Minheap Minheap;

// We generally pass Vertex number and length of that vertex
// So vertex_dis_for_heap acts as a node for heap whose contents are vertex and length
// Here i am taking length to be double 
// Since both length and time are in double things won't change
// Naming them as weight

struct vertex_dis_for_heap
{
    int vertex;
    double weight;
};
struct Minheap
{
    int total_elements;
    int size;
    // denotes the current size
    ptr_node_for_heap Array;
    // Array of node this array is basically our heap
    int *position;
    // To do decrease key operation efficiently
};

/*
Some info about Minheap
    total elements is equal to the capacity of the heap 
        in our case it will be equal to number of vertices
    Size=number of nodes currently in the heap
        since heap is an array and we can't delete/free element 
        we swap it with last element(wrt size) and decrease size by 1
    Array it is array of nodes which is basically our heap
    position it is an array of integers which will give position of vertex in heap
        for ex at some moment Array{(1,3),(3,5),(2,4)} is looking like this
        so pos[3]=1 (Indexing of array starts at 0)
            Array[1].vertex=3
            Array[1].weight=5
*/

// Functins
ptr_Minheap       create_empty_heap(int total_elements);
// To create an empty heap
// Inital elements can be added directly so no need of function for that
void              DownMinheapify(ptr_Minheap p, int i);
// To fix 1 set of elements log(n)
void              MinHeapify(ptr_Minheap p);
// To form a MinHeap
ptr_node_for_heap ExtractMin(ptr_Minheap p);
// Return the Minimum node(on the basis of weight) and remove that from the heap
void              DecreaseKey(ptr_Minheap p,int vertex,double new_weight);
// To decrese the value in the heap and correct the heap
void              print_heap(ptr_Minheap p);
// Utility function to print the heap
void              DeleteHeap(ptr_Minheap pq);
#endif
