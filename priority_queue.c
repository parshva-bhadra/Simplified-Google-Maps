#include<stdio.h>
#include<stdlib.h>

#include"priority_queue.h"

ptr_Minheap       create_empty_heap(int total_elements)
{
    ptr_Minheap p;
    p = (ptr_Minheap)malloc(sizeof(Minheap));
    p->size = 0;
    p->total_elements = total_elements;
    p->Array = (ptr_node_for_heap)malloc(total_elements * sizeof(vertex_dis_for_heap));
    p->position = (int *)malloc(total_elements * sizeof(int));
    return p;
}

void              swap_array_elems(ptr_Minheap p, int i, int j)
{
    int vertex1 = p->Array[i].vertex - 1;
    int vertex2 = p->Array[j].vertex - 1;
    p->position[vertex1] = j;
    p->position[vertex2] = i;
    int temp_vertex;
    double temp_dis;
    temp_vertex = p->Array[i].vertex;
    temp_dis = p->Array[i].weight;
    p->Array[i] = p->Array[j];
    p->Array[j].vertex = temp_vertex;
    p->Array[j].weight = temp_dis;
}


void              DownMinheapify(ptr_Minheap p, int i)
{
    // Utility function for Minheapify
    int n = p->size;
    // Establish heap property first at a[i]
    int w = i * 2 + 1; // First descendant of i (0-based indexing)
    while (w < n)
    {
        if (w + 1 < n)
            if (p->Array[w + 1].weight < p->Array[w].weight)
                w++;
        if (p->Array[i].weight <= p->Array[w].weight)
            return;
        swap_array_elems(p, i, w);
        i = w;         // we swapped with this node ; subtree below it may need fixing
        w = i * 2 + 1; // Get first descendant of 'i' and repeat loop procedure
    }
}


void              MinHeapify(ptr_Minheap p)
{
    int n = (p->size) / 2;
    for (int i = n - 1; i >= 0; i--)
    {
        DownMinheapify(p, i);
    }
}


ptr_node_for_heap ExtractMin(ptr_Minheap p)
{
    if (p->size > 0)
    {
        ptr_node_for_heap n;
        n=(ptr_node_for_heap)malloc(sizeof(vertex_dis_for_heap));
        n->vertex = p->Array[0].vertex;
        n->weight= p->Array[0].weight;
        p->size = p->size - 1;
        swap_array_elems(p,0,p->size);
        DownMinheapify(p,0);
        return n;
    }
    else{
        return NULL;
    }
}


void              DecreaseKey(ptr_Minheap p,int vertex,double new_weight)
{
    int i= p->position[vertex-1];
    p->Array[i].weight=new_weight;
    while (i>0 && p->Array[i].weight < p->Array[(i - 1) / 2].weight)
    {
        swap_array_elems(p,i,(i-1)/2);
        i = (i - 1) / 2;
    }
}


void              print_heap(ptr_Minheap p)
{
    for (int i = 0; i < p->size; i++)
    {
        printf("vertex = %d   and   edge weight = %0.2f\n", p->Array[i].vertex, p->Array[i].weight);
    }
}

void DeleteHeap(ptr_Minheap pq)
{
    free(pq->Array);
    free(pq->position);
    free(pq);
    return;
}

void Push(Ptr_S S,int x)
{
    my_stack T = (my_stack)malloc(sizeof(List));
    T->x = x;
    T->next =(*S);
    (*S) = T;
}

void Pop(Ptr_S S)
{
    my_stack prev;
    if (*S != NULL)
    {
        prev=(*S);
        *S=(*S)->next;
        free(prev);
    }
    else
    {
        printf("The stack is empty\n");
    }
}
void DisplayStack(my_stack S)
{
    while (S != NULL)
    {
        printf("%d ", S->x);
        S = S->next;
    }
    printf("\n");
}
void DeleteStack(Ptr_S S)
{
    while((*S)!=NULL)
    {
        Pop(S);
    }
}